#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int* sixaxis_handles_count; int /*<<< orphan*/ ** sixaxis_handles; } ;
typedef  TYPE_1__ switch_input_t ;
typedef  enum retro_sensor_action { ____Placeholder_retro_sensor_action } retro_sensor_action ;

/* Variables and functions */
 unsigned int CONTROLLER_HANDHELD ; 
 unsigned int DEFAULT_MAX_PADS ; 
#define  RETRO_SENSOR_ACCELEROMETER_DISABLE 133 
#define  RETRO_SENSOR_ACCELEROMETER_ENABLE 132 
#define  RETRO_SENSOR_GYROSCOPE_DISABLE 131 
#define  RETRO_SENSOR_GYROSCOPE_ENABLE 130 
#define  RETRO_SENSOR_ILLUMINANCE_DISABLE 129 
#define  RETRO_SENSOR_ILLUMINANCE_ENABLE 128 
 int /*<<< orphan*/  TYPE_HANDHELD ; 
 int /*<<< orphan*/  TYPE_JOYCON_PAIR ; 
 int /*<<< orphan*/  TYPE_PROCONTROLLER ; 
 int /*<<< orphan*/  appletIsIlluminanceAvailable (int*) ; 
 int /*<<< orphan*/  hidGetSixAxisSensorHandles (int /*<<< orphan*/ *,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidStartSixAxisSensor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool switch_input_set_sensor_state(void *data, unsigned port,
      enum retro_sensor_action action, unsigned event_rate)
{
#ifdef HAVE_LIBNX
   unsigned i, handles_count;
   bool available;
   switch_input_t *sw = (switch_input_t*) data;

   if(!sw)
      return false;

   switch(action)
   {
      case RETRO_SENSOR_ILLUMINANCE_ENABLE:
         available = false;
         appletIsIlluminanceAvailable(&available);
         return available;

      case RETRO_SENSOR_ILLUMINANCE_DISABLE:
      case RETRO_SENSOR_ACCELEROMETER_DISABLE:
      case RETRO_SENSOR_GYROSCOPE_DISABLE:
         return true;

      case RETRO_SENSOR_ACCELEROMETER_ENABLE:
      case RETRO_SENSOR_GYROSCOPE_ENABLE:
         if(port < DEFAULT_MAX_PADS && sw->sixaxis_handles_count[port] == 0)
         {
            hidGetSixAxisSensorHandles(&sw->sixaxis_handles[port][0], 2, port, TYPE_JOYCON_PAIR);

            hidGetSixAxisSensorHandles(&sw->sixaxis_handles[port][2], 1, port, TYPE_PROCONTROLLER);

            if(port == 0)
            {
               hidGetSixAxisSensorHandles(&sw->sixaxis_handles[port][3], 1, CONTROLLER_HANDHELD, TYPE_HANDHELD);
               handles_count = 4;
            }
            else
            {
               handles_count = 3;
            }

            for(i = 0; i < handles_count; i++) {
               hidStartSixAxisSensor(sw->sixaxis_handles[port][i]);
            }

            sw->sixaxis_handles_count[port] = handles_count;
         }
         return true;
   }
#endif

   return false;
}