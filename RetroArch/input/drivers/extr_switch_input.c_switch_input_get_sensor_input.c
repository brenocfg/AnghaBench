#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float x; float y; float z; } ;
struct TYPE_5__ {float x; float y; float z; } ;
struct TYPE_7__ {TYPE_2__ gyroscope; TYPE_1__ accelerometer; } ;
typedef  TYPE_3__ SixAxisSensorValues ;

/* Variables and functions */
 unsigned int CONTROLLER_P1_AUTO ; 
#define  RETRO_SENSOR_ACCELEROMETER_X 133 
#define  RETRO_SENSOR_ACCELEROMETER_Y 132 
#define  RETRO_SENSOR_ACCELEROMETER_Z 131 
#define  RETRO_SENSOR_GYROSCOPE_X 130 
#define  RETRO_SENSOR_GYROSCOPE_Y 129 
#define  RETRO_SENSOR_GYROSCOPE_Z 128 
 unsigned int RETRO_SENSOR_ILLUMINANCE ; 
 int /*<<< orphan*/  appletGetCurrentIlluminance (float*) ; 
 int /*<<< orphan*/  hidSixAxisSensorValuesRead (TYPE_3__*,unsigned int,int) ; 

__attribute__((used)) static float switch_input_get_sensor_input(void *data,
      unsigned port, unsigned id)
{
#ifdef HAVE_LIBNX
   float f;
   SixAxisSensorValues sixaxis;

   if(id >= RETRO_SENSOR_ACCELEROMETER_X && id <= RETRO_SENSOR_GYROSCOPE_Z)
   {
      hidSixAxisSensorValuesRead(&sixaxis, port == 0 ? CONTROLLER_P1_AUTO : port, 1);

      switch(id)
      {
         case RETRO_SENSOR_ACCELEROMETER_X:
            return sixaxis.accelerometer.x;
         case RETRO_SENSOR_ACCELEROMETER_Y:
            return sixaxis.accelerometer.y;
         case RETRO_SENSOR_ACCELEROMETER_Z:
            return sixaxis.accelerometer.z;
         case RETRO_SENSOR_GYROSCOPE_X:
            return sixaxis.gyroscope.x;
         case RETRO_SENSOR_GYROSCOPE_Y:
            return sixaxis.gyroscope.y;
         case RETRO_SENSOR_GYROSCOPE_Z:
            return sixaxis.gyroscope.z;
      }

   }

   if(id == RETRO_SENSOR_ILLUMINANCE)
   {
      appletGetCurrentIlluminance(&f);
      return f;
   }
#endif

   return 0.0f;
}