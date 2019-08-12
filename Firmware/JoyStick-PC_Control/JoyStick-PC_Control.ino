#include <Mouse.h>

int horzPin = A1;
int vertPin = A0;
int selPin = 9;

float vertZero;
float horzZero;
float vertValue;
float horzValue;
float vertMove = 0;
float horzMove = 0;

float sensitivity = .2;
int smallMoveSpeed = 5;
float pcSpeed = 5;
float vertMax = 500;
float horzMax = 500;

void setup() {
  Serial.begin(115200);
  pinMode(horzPin, INPUT);
  pinMode(vertPin, INPUT);
  delay(500);
  vertZero = analogRead(vertPin);
  horzZero = analogRead(horzPin);
  delay(500);
}

void loop() {
  vertValue = analogRead(vertPin) - vertZero;
  horzValue = analogRead(horzPin) - horzZero;

  vertMove = pcSpeed * (vertValue / vertMax);
  if (vertMove > sensitivity || vertMove < (sensitivity * -1)) {
    Serial.println("VERT");
    Serial.println(vertMove);
    if (vertMove > 0 && vertMove < 1) {
      delay(smallMoveSpeed);
      Mouse.move(0, 1, 0);
    }
    if (vertMove > -1 && vertMove < 0) {
      delay(smallMoveSpeed);
      Mouse.move(0, -1, 0);
    }
    if (vertMove >= 1 || vertMove <= -1) {
      Mouse.move(0, vertMove, 0);
    }
  }

  horzMove = (pcSpeed * (horzValue / horzMax)) * -1;
  if (horzMove > sensitivity || horzMove < (sensitivity * -1)) {
    Serial.println("HORZ");
    Serial.println(horzMove);
    if (horzMove > 0 && horzMove < 1) {
      delay(smallMoveSpeed);
      Mouse.move(1, 0, 0);
    }
    if (horzMove > -1 && horzMove < 0) {
      delay(smallMoveSpeed);
      Mouse.move(-1, 0, 0);
    }
    if (horzMove >= 1 || horzMove <= -1) {
      Mouse.move(horzMove, 0, 0);
    }
  }
  delay(1);
}
