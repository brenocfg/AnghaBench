#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct android_app {int sensor_state_mask; int /*<<< orphan*/  sensorEventQueue; scalar_t__ accelerometerSensor; } ;
struct TYPE_7__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_9__ {TYPE_1__ accelerometer_state; } ;
typedef  TYPE_3__ android_input_t ;
struct TYPE_8__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_10__ {TYPE_2__ acceleration; } ;
typedef  TYPE_4__ ASensorEvent ;

/* Variables and functions */
 scalar_t__ ASensorEventQueue_getEvents (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int RETRO_SENSOR_ACCELEROMETER_ENABLE ; 
 int UINT64_C (int) ; 
 scalar_t__ g_android ; 

__attribute__((used)) static void android_input_poll_user(android_input_t *android)
{
   struct android_app *android_app = (struct android_app*)g_android;

   if ((android_app->sensor_state_mask & (UINT64_C(1) <<
               RETRO_SENSOR_ACCELEROMETER_ENABLE))
         && android_app->accelerometerSensor)
   {
      ASensorEvent event;
      while (ASensorEventQueue_getEvents(android_app->sensorEventQueue, &event, 1) > 0)
      {
         android->accelerometer_state.x = event.acceleration.x;
         android->accelerometer_state.y = event.acceleration.y;
         android->accelerometer_state.z = event.acceleration.z;
      }
   }
}