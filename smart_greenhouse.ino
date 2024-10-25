//Simple Smart Greenhouse


//define pins
//outputs
const int LED            = 2;   //LED on board
const int fan            = 14;  //LED green 
const int sprinkler      = 12;  //LED red
const int co2Valve       = 32;  //LED green
const int irrigation     = 33;  //LED big red 
const int lightGenerator = 25;  //LED big yellow

//input sensors default
int temperature    = 0;      //celsius
int humidity       = 100;    //percent
int co2Level       = 1900;   //ppm

//keeping track of the lightGenerator time 
unsigned long previousTimeLight = millis();
long timeIntervalLight = 1000;
int timer = 0;

//keeping track of the other tasks time 
unsigned long previousTimeOT = millis();
long timeIntervalOT = 20000;

//keeping track of the input changing time (just for getting better output view!)
unsigned long previousTimeIrrigation = millis();
long timeIntervalIrrigation = 1000;
int timer2 = 0;

//input generator (random number)
int inputGenerator(int startRange, int endRange)
{
  srand((unsigned) time(NULL));

  int offset = startRange;
  int range = endRange - (startRange-1);

  int random = offset + (rand() % range);

  return random;
}

void setup() {
  
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  pinMode(fan, OUTPUT);
	pinMode(sprinkler, OUTPUT);
	pinMode(co2Valve, OUTPUT);
  pinMode(irrigation, OUTPUT);
	pinMode(lightGenerator, OUTPUT);

}

void loop() {
  
  //start
  digitalWrite(LED, HIGH);

  unsigned long currentTime = millis();

  //multitasking - Task 1
  //checking lightIntensity
  if(currentTime - previousTimeLight > timeIntervalLight)
  {
    previousTimeLight = currentTime;
    timer = timer + 1;
    if (timer <= 6)
    {
      digitalWrite(lightGenerator, HIGH);
      delay(200);
      digitalWrite(lightGenerator, LOW);
    }
    if (timer > 6)
    {
      digitalWrite(lightGenerator, LOW);
    }
    if (timer == 24)
    {
      timer = 0;
    }
  }

  //multitasking - Task 2
  if(currentTime - previousTimeOT > timeIntervalOT)
  {
    previousTimeOT = currentTime;

    //input sensors
    Serial.println("*******************");
    temperature    = inputGenerator(-10, 50);    //celsius
    Serial.print("temperature: ");
    Serial.println(temperature);

    humidity       = inputGenerator(0, 100);     //percent
    Serial.print("humidity: ");
    Serial.print(humidity); Serial.println("%");

    co2Level       = inputGenerator(400, 2000);  //ppm
    Serial.print("co2Level: ");
    Serial.println(co2Level);

    //temperature = digitalRead(temperature_sensor);
    //checking temperature
    if (temperature > 24)
    {
      digitalWrite(fan, HIGH);
    }
    else if (temperature < 18) 
    {
      digitalWrite(fan, LOW);
    }

    //humidity = digitalRead(humidity_sensor);
    //checking humidity
    if (humidity < 70)
    {
      digitalWrite(sprinkler, HIGH);
    }
    else if (humidity > 90) 
    {
      digitalWrite(sprinkler, LOW);
    }

    //co2Valve = digitalRead(co2Level_sensor);
    //checking co2Level
    if (co2Level < 1000)
    {
      digitalWrite(co2Valve, HIGH);
    }
    else if (co2Level > 1300) 
    {
      digitalWrite(co2Valve, LOW);
    }
  }

  //multitasking - Task 3
  //checking Irrigation
  if(currentTime - previousTimeIrrigation > timeIntervalIrrigation)
  {
    previousTimeIrrigation = currentTime;
    timer2 = timer2 + 1;
    if (timer2 <= 3)
    {
      digitalWrite(irrigation, HIGH);
      delay(200);
      digitalWrite(irrigation, LOW);
    }
    if (timer2 > 3)
    {
      digitalWrite(irrigation, LOW);
    }
    if (timer2 == 12)
    {
      timer2 = 0;
    }
  }  
}