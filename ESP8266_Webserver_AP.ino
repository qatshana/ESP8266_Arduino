
#include <ESP8266WiFi.h>


#define LED_PIN 16


WiFiServer server(80);
int ledPin=LED_PIN;

class Person{
  private:
  String name;
  int age;
  public:
  Person();
  Person(int age, String name);
  String getName();
  void setName(String name);
  String toString();
};

Person::Person(){
  this->name="Tom";
  this->age=99;
}

Person::Person(int age, String name){
  this->age=age;
  this->name=name;
}

String Person::getName(){
  return name;
}


void Person::setName(String name){
  this->name=name;
}

String Person::toString(){
  return this->name;
}

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_AP);
  WiFi.softAP("JT_IoT","12345678");
  server.begin();
  Serial.begin(115200);
  IPAddress serverIP=WiFi.softAPIP();
  delay(1000);
  Serial.println();
  Serial.print("Server IP is: ");
  Serial.println(serverIP);

  pinMode(LED_PIN, OUTPUT); //GPIO16 is an OUTPUT pin;
  digitalWrite(LED_PIN, HIGH); //Initial state is ON
/*
  Person person1;
  Person person2(45,"John");
  person1.setName("Alex");
  String nm=person1.getName();
  Serial.println(nm);
  Serial.print("This is second name: ");
  Serial.println(person2.getName());
*/
}

void loop() {
  // put your main code here, to run repeatedly:

  WiFiClient client = server.available();

   if(!client){
    return;
   }
  Serial.println("Someone connected to server");
  //String request1=client.readString();
  String request2=client.readStringUntil('\r');
  Serial.println(request2);
  String s="HTTP/1.1 200 OK\r\n";
  s+="Content-TYPE: text/html\r\n\r\n";
  s+="<!DOCTYPE HTML>\r\n<html>\r\n";
  s+="<head>\r\n";
  s+="<style>\r\n";
s+="</style></head>";

  //s+="<br><input type=\"button\"\r\n";
  String status="ON";
  if(request2.indexOf("OFF")!=-1){
   digitalWrite(LED_PIN,LOW); //Initial state is ON
   status="OFF";  
  }
  else if(request2.indexOf("ON")!=-1){
   digitalWrite(LED_PIN, HIGH); //Initial state is ON   
   status="ON";
  }
  s+="<br><h1>";
  s+=status;
  s+="</h1></html>\n";
  client.flush();
  client.print(s);
  Serial.println(s); 
  delay(5000); 
 

}


