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
struct android_app {scalar_t__ destroyRequested; scalar_t__ reinitRequested; scalar_t__ input_alive; } ;
struct TYPE_5__ {int input_block_timeout; } ;
struct TYPE_6__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  android_input_t ;
struct TYPE_7__ {scalar_t__ valid; } ;

/* Variables and functions */
 int ALooper_pollAll (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  APP_CMD_REINIT_DONE ; 
 int /*<<< orphan*/  CMD_EVENT_REINIT ; 
#define  LOOPER_ID_INPUT 130 
#define  LOOPER_ID_MAIN 129 
#define  LOOPER_ID_USER 128 
 int /*<<< orphan*/  RARCH_CTL_IS_PAUSED ; 
 int /*<<< orphan*/  RARCH_CTL_SET_SHUTDOWN ; 
 size_t RARCH_PAUSE_TOGGLE ; 
 int /*<<< orphan*/  android_app_write_cmd (struct android_app*,int /*<<< orphan*/ ) ; 
 scalar_t__ android_input_key_pressed (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  android_input_poll_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  android_input_poll_main_cmd () ; 
 int /*<<< orphan*/  android_input_poll_memcpy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  android_input_poll_user (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* config_get_ptr () ; 
 scalar_t__ g_android ; 
 TYPE_3__** input_config_binds ; 
 scalar_t__ rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void android_input_poll(void *data)
{
   settings_t *settings = config_get_ptr();
   int ident;
   struct android_app *android_app = (struct android_app*)g_android;
   android_input_t *android        = (android_input_t*)data;

   while ((ident =
            ALooper_pollAll((input_config_binds[0][RARCH_PAUSE_TOGGLE].valid 
               && android_input_key_pressed(android, RARCH_PAUSE_TOGGLE))
               ? -1 : settings->uints.input_block_timeout,
               NULL, NULL, NULL)) >= 0)
   {
      switch (ident)
      {
         case LOOPER_ID_INPUT:
            android_input_poll_input(android);
            break;
         case LOOPER_ID_USER:
            android_input_poll_user(android);
            break;
         case LOOPER_ID_MAIN:
            android_input_poll_main_cmd();
            break;
      }

      if (android_app->destroyRequested != 0)
      {
         rarch_ctl(RARCH_CTL_SET_SHUTDOWN, NULL);
         return;
      }

      if (android_app->reinitRequested != 0)
      {
         if (rarch_ctl(RARCH_CTL_IS_PAUSED, NULL))
            command_event(CMD_EVENT_REINIT, NULL);
         android_app_write_cmd(android_app, APP_CMD_REINIT_DONE);
         return;
      }
   }

   if (android_app->input_alive)
      android_input_poll_memcpy(android);
}