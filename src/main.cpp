#include <Arduino.h>
#include <SPI.h>
#include "data.h"
#include "opcr2.h"
#include <esp_task_wdt.h>

sensorData data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  esp_task_wdt_reset();
  esp_task_wdt_init(8, true);
  esp_task_wdt_add(NULL);

  ssPin_OPC = 39;
  SetSSpin(HIGH);
  pinMode(ssPin_OPC, OUTPUT);
  delay(1000);

  PrintFirmwareVer(Serial);

  SPI.begin();
  esp_task_wdt_reset();
  InitDevice();
  esp_task_wdt_reset();
  PrintDataLabels(Serial);
  esp_task_wdt_reset();

}

void loop() {
  // put your main code here, to run repeatedly:
  esp_task_wdt_reset();
  StartOPC();
  esp_task_wdt_reset();
  delay(1000);
  ReadOPChist();
  esp_task_wdt_reset();
  while(true) {
    delay(1000);
    ReadOPChist();
    Serial.print(millis());
    PrintData(Serial);
    esp_task_wdt_reset();
  }
}

