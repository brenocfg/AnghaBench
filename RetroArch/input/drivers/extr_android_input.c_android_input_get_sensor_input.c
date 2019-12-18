#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {float x; float y; float z; } ;
struct TYPE_4__ {TYPE_1__ accelerometer_state; } ;
typedef  TYPE_2__ android_input_t ;

/* Variables and functions */
#define  RETRO_SENSOR_ACCELEROMETER_X 130 
#define  RETRO_SENSOR_ACCELEROMETER_Y 129 
#define  RETRO_SENSOR_ACCELEROMETER_Z 128 

__attribute__((used)) static float android_input_get_sensor_input(void *data,
      unsigned port,unsigned id)
{
   android_input_t      *android      = (android_input_t*)data;

   switch (id)
   {
      case RETRO_SENSOR_ACCELEROMETER_X:
         return android->accelerometer_state.x;
      case RETRO_SENSOR_ACCELEROMETER_Y:
         return android->accelerometer_state.y;
      case RETRO_SENSOR_ACCELEROMETER_Z:
         return android->accelerometer_state.z;
   }

   return 0;
}