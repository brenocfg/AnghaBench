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
struct android_app {int input_alive; int /*<<< orphan*/  sensorEventQueue; scalar_t__ sensorManager; } ;
typedef  int /*<<< orphan*/  dylib_t ;
struct TYPE_4__ {TYPE_1__* joypad; } ;
typedef  TYPE_2__ android_input_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASensorManager_destroyEventQueue (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  android_keyboard_free () ; 
 int /*<<< orphan*/  dylib_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ g_android ; 
 int /*<<< orphan*/ * libandroid_handle ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void android_input_free_input(void *data)
{
   android_input_t *android = (android_input_t*)data;
   struct android_app *android_app = (struct android_app*)g_android;
   if (!android)
      return;

   if (android_app->sensorManager)
      ASensorManager_destroyEventQueue(android_app->sensorManager,
            android_app->sensorEventQueue);

   if (android->joypad)
      android->joypad->destroy();
   android->joypad = NULL;

   android_app->input_alive = false;

#ifdef HAVE_DYNAMIC
   dylib_close((dylib_t)libandroid_handle);
   libandroid_handle = NULL;
#endif

   android_keyboard_free();
   free(data);
}