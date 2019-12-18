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
struct android_app {int /*<<< orphan*/  looper; int /*<<< orphan*/  sensorManager; int /*<<< orphan*/  sensorEventQueue; int /*<<< orphan*/  accelerometerSensor; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASENSOR_TYPE_ACCELEROMETER ; 
 int /*<<< orphan*/  ASensorManager_createEventQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASensorManager_getDefaultSensor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASensorManager_getInstance () ; 
 int /*<<< orphan*/  LOOPER_ID_USER ; 

__attribute__((used)) static void android_input_enable_sensor_manager(struct android_app *android_app)
{
   android_app->sensorManager = ASensorManager_getInstance();
   android_app->accelerometerSensor =
      ASensorManager_getDefaultSensor(android_app->sensorManager,
         ASENSOR_TYPE_ACCELEROMETER);
   android_app->sensorEventQueue =
      ASensorManager_createEventQueue(android_app->sensorManager,
         android_app->looper, LOOPER_ID_USER, NULL, NULL);
}