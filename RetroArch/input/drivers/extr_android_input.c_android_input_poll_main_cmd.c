#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct android_app {int reinitRequested; int stateSaved; int activityState; int sensor_state_mask; int unfocused; int destroyRequested; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  accelerometer_event_rate; int /*<<< orphan*/ * accelerometerSensor; int /*<<< orphan*/ * window; TYPE_1__* activity; int /*<<< orphan*/  config; int /*<<< orphan*/ * pendingWindow; int /*<<< orphan*/  looper; int /*<<< orphan*/  inputQueue; int /*<<< orphan*/  pendingInputQueue; int /*<<< orphan*/  msgread; } ;
typedef  int /*<<< orphan*/  jint ;
typedef  int int8_t ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_6__ {int /*<<< orphan*/  doVibrate; TYPE_2__* activity; } ;
struct TYPE_5__ {int /*<<< orphan*/  clazz; } ;
struct TYPE_4__ {int /*<<< orphan*/  assetManager; } ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  AConfiguration_fromAssetManager (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AInputQueue_attachLooper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AInputQueue_detachLooper (int /*<<< orphan*/ ) ; 
#define  APP_CMD_CONFIG_CHANGED 141 
#define  APP_CMD_DESTROY 140 
#define  APP_CMD_GAINED_FOCUS 139 
#define  APP_CMD_INIT_WINDOW 138 
#define  APP_CMD_INPUT_CHANGED 137 
#define  APP_CMD_LOST_FOCUS 136 
#define  APP_CMD_PAUSE 135 
#define  APP_CMD_REINIT_DONE 134 
#define  APP_CMD_RESUME 133 
#define  APP_CMD_SAVE_STATE 132 
#define  APP_CMD_START 131 
#define  APP_CMD_STOP 130 
#define  APP_CMD_TERM_WINDOW 129 
#define  APP_CMD_VIBRATE_KEYPRESS 128 
 int /*<<< orphan*/  CALL_VOID_METHOD_PARAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOOPER_ID_INPUT ; 
 int /*<<< orphan*/  RARCH_CTL_SET_IDLE ; 
 int /*<<< orphan*/  RARCH_CTL_SET_PAUSED ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  RETRO_RUMBLE_STRONG ; 
 int RETRO_SENSOR_ACCELEROMETER_DISABLE ; 
 int RETRO_SENSOR_ACCELEROMETER_ENABLE ; 
 int UINT64_C (int) ; 
 TYPE_3__* g_android ; 
 int /*<<< orphan*/  input_sensor_set_state (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ jni_thread_getenv () ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int*) ; 
 int read (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  scond_broadcast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_driver_set_stub_frame () ; 
 int /*<<< orphan*/  video_driver_unset_stub_frame () ; 

__attribute__((used)) static void android_input_poll_main_cmd(void)
{
   int8_t cmd;
   struct android_app *android_app = (struct android_app*)g_android;

   if (read(android_app->msgread, &cmd, sizeof(cmd)) != sizeof(cmd))
      cmd = -1;

   switch (cmd)
   {
      case APP_CMD_REINIT_DONE:
         slock_lock(android_app->mutex);

         android_app->reinitRequested = 0;

         scond_broadcast(android_app->cond);
         slock_unlock(android_app->mutex);
         break;

      case APP_CMD_INPUT_CHANGED:
         slock_lock(android_app->mutex);

         if (android_app->inputQueue)
            AInputQueue_detachLooper(android_app->inputQueue);

         android_app->inputQueue = android_app->pendingInputQueue;

         if (android_app->inputQueue)
         {
            RARCH_LOG("Attaching input queue to looper");
            AInputQueue_attachLooper(android_app->inputQueue,
                  android_app->looper, LOOPER_ID_INPUT, NULL,
                  NULL);
         }

         scond_broadcast(android_app->cond);
         slock_unlock(android_app->mutex);

         break;

      case APP_CMD_INIT_WINDOW:
         slock_lock(android_app->mutex);
         android_app->window = android_app->pendingWindow;
         android_app->reinitRequested = 1;
         scond_broadcast(android_app->cond);
         slock_unlock(android_app->mutex);

         break;

      case APP_CMD_SAVE_STATE:
         slock_lock(android_app->mutex);
         android_app->stateSaved = 1;
         scond_broadcast(android_app->cond);
         slock_unlock(android_app->mutex);
         break;

      case APP_CMD_RESUME:
      case APP_CMD_START:
      case APP_CMD_PAUSE:
      case APP_CMD_STOP:
         slock_lock(android_app->mutex);
         android_app->activityState = cmd;
         scond_broadcast(android_app->cond);
         slock_unlock(android_app->mutex);
         break;

      case APP_CMD_CONFIG_CHANGED:
         AConfiguration_fromAssetManager(android_app->config,
               android_app->activity->assetManager);
         break;
      case APP_CMD_TERM_WINDOW:
         slock_lock(android_app->mutex);

         /* The window is being hidden or closed, clean it up. */
         /* terminate display/EGL context here */

         android_app->window = NULL;
         scond_broadcast(android_app->cond);
         slock_unlock(android_app->mutex);
         break;

      case APP_CMD_GAINED_FOCUS:
         {
            bool boolean = false;

            rarch_ctl(RARCH_CTL_SET_PAUSED, &boolean);
            rarch_ctl(RARCH_CTL_SET_IDLE,   &boolean);
            video_driver_unset_stub_frame();

            if ((android_app->sensor_state_mask
                     & (UINT64_C(1) << RETRO_SENSOR_ACCELEROMETER_ENABLE))
                  && android_app->accelerometerSensor == NULL)
               input_sensor_set_state(0,
                     RETRO_SENSOR_ACCELEROMETER_ENABLE,
                     android_app->accelerometer_event_rate);
         }
         slock_lock(android_app->mutex);
         android_app->unfocused = false;
         scond_broadcast(android_app->cond);
         slock_unlock(android_app->mutex);
         break;
      case APP_CMD_LOST_FOCUS:
         {
            bool boolean = true;

            rarch_ctl(RARCH_CTL_SET_PAUSED, &boolean);
            rarch_ctl(RARCH_CTL_SET_IDLE,   &boolean);
            video_driver_set_stub_frame();

            /* Avoid draining battery while app is not being used. */
            if ((android_app->sensor_state_mask
                     & (UINT64_C(1) << RETRO_SENSOR_ACCELEROMETER_ENABLE))
                  && android_app->accelerometerSensor != NULL
                  )
               input_sensor_set_state(0,
                     RETRO_SENSOR_ACCELEROMETER_DISABLE,
                     android_app->accelerometer_event_rate);
         }
         slock_lock(android_app->mutex);
         android_app->unfocused = true;
         scond_broadcast(android_app->cond);
         slock_unlock(android_app->mutex);
         break;

      case APP_CMD_DESTROY:
         RARCH_LOG("APP_CMD_DESTROY\n");
         android_app->destroyRequested = 1;
         break;
      case APP_CMD_VIBRATE_KEYPRESS:
      {
         JNIEnv *env = (JNIEnv*)jni_thread_getenv();

         if (env && g_android && g_android->doVibrate)
         {
            CALL_VOID_METHOD_PARAM(env, g_android->activity->clazz,
                  g_android->doVibrate, (jint)-1, (jint)RETRO_RUMBLE_STRONG, (jint)255, (jint)1);
         }
         break;
      }
   }
}