#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct android_app {int /*<<< orphan*/  sensor_state_mask; int /*<<< orphan*/  accelerometerSensor; int /*<<< orphan*/  sensorEventQueue; } ;
typedef  enum retro_sensor_action { ____Placeholder_retro_sensor_action } retro_sensor_action ;

/* Variables and functions */
 int /*<<< orphan*/  ASensorEventQueue_disableSensor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASensorEventQueue_enableSensor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASensorEventQueue_setEventRate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  BIT64_CLEAR (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  BIT64_SET (int /*<<< orphan*/ ,int const) ; 
#define  RETRO_SENSOR_ACCELEROMETER_DISABLE 129 
#define  RETRO_SENSOR_ACCELEROMETER_ENABLE 128 
 int /*<<< orphan*/  android_input_enable_sensor_manager (struct android_app*) ; 
 scalar_t__ g_android ; 

__attribute__((used)) static bool android_input_set_sensor_state(void *data, unsigned port,
      enum retro_sensor_action action, unsigned event_rate)
{
   struct android_app *android_app = (struct android_app*)g_android;

   if (event_rate == 0)
      event_rate = 60;

   switch (action)
   {
      case RETRO_SENSOR_ACCELEROMETER_ENABLE:
         if (!android_app->accelerometerSensor)
            android_input_enable_sensor_manager(android_app);

         if (android_app->accelerometerSensor)
            ASensorEventQueue_enableSensor(android_app->sensorEventQueue,
                  android_app->accelerometerSensor);

         /* Events per second (in microseconds). */
         if (android_app->accelerometerSensor)
            ASensorEventQueue_setEventRate(android_app->sensorEventQueue,
                  android_app->accelerometerSensor, (1000L / event_rate)
                  * 1000);

         BIT64_CLEAR(android_app->sensor_state_mask, RETRO_SENSOR_ACCELEROMETER_DISABLE);
         BIT64_SET(android_app->sensor_state_mask, RETRO_SENSOR_ACCELEROMETER_ENABLE);
         return true;

      case RETRO_SENSOR_ACCELEROMETER_DISABLE:
         if (android_app->accelerometerSensor)
            ASensorEventQueue_disableSensor(android_app->sensorEventQueue,
                  android_app->accelerometerSensor);

         BIT64_CLEAR(android_app->sensor_state_mask, RETRO_SENSOR_ACCELEROMETER_ENABLE);
         BIT64_SET(android_app->sensor_state_mask, RETRO_SENSOR_ACCELEROMETER_DISABLE);
         return true;
      default:
         return false;
   }

   return false;
}