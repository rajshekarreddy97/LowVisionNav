#include <Servo.h>

#define SOUND_VELOCITY 0.034     //define sound velocity in cm/uS

Servo myservo;  // create servo object to control a servo

const int trigPin = 2;
const int echoPin = 16;
const int speaker = 12;

long duration;
float distanceCm;
int pos = 0;   // Servo position


void setup() 
{
  Serial.begin(115200); // Starts the serial communication
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  myservo.attach(13); // attaches the servo on GI13 to the servo object

  pinMode(speaker, OUTPUT);
}

void loop() 
{
  for (pos = 0; pos <= 180; pos += 5) // goes from 0 degrees to 180 degrees in steps of 5 degrees
  { 
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    RotateAndCapture();
  }
  
  for (pos = 180; pos >= 0; pos -= 5)  // goes from 180 degrees to 0 degrees
  { 
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    RotateAndCapture();
  }
}

void RotateAndCapture()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  if (distanceCm < 30)  // Threshold distance
  {
    myservo.detach(); // Stop rotating
    int audioDelay = distanceCm * 3;    // Match beeping frequency to the distance of the obstacle;
    delay(audioDelay); 
    tone(speaker,1047); // tone(pin,frequency)
    delay(100);
    noTone(speaker);
  }
  else
  {
    myservo.attach(13);
    noTone(speaker);
  }
}
