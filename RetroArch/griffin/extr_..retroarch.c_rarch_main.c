#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  settings_t ;
struct TYPE_7__ {int argc; char** argv; int /*<<< orphan*/  environ_get; void* args; } ;
typedef  TYPE_2__ content_ctx_info_t ;
struct TYPE_9__ {int /*<<< orphan*/  info; } ;
struct TYPE_8__ {TYPE_1__* application; } ;
struct TYPE_6__ {int exiting; int /*<<< orphan*/  (* quit ) () ;int /*<<< orphan*/  (* process_events ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_HISTORY_DEINIT ; 
 int /*<<< orphan*/  CORE_TYPE_PLAIN ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRIVERS_CMD_ALL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_POINTER ; 
 scalar_t__ MAX_USERS ; 
 int /*<<< orphan*/  RARCH_CTL_STATE_FREE ; 
 int /*<<< orphan*/  RARCH_DRIVER_CTL_DEINIT ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RETRO_DEVICE_JOYPAD ; 
 int audio_driver_active ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * configuration_settings ; 
 int /*<<< orphan*/  driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frontend_driver_environment_get_ptr () ; 
 int /*<<< orphan*/  frontend_driver_init_first (void*) ; 
 scalar_t__ frontend_driver_is_inited () ; 
 int /*<<< orphan*/  global_free () ; 
 int /*<<< orphan*/  input_config_set_device (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libretro_free_system_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_exit (void*) ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rarch_favorites_deinit () ; 
 scalar_t__ rarch_is_inited ; 
 int /*<<< orphan*/  rarch_tls ; 
 int /*<<< orphan*/  retroarch_msg_queue_init () ; 
 int runloop_iterate () ; 
 TYPE_5__ runloop_system ; 
 int /*<<< orphan*/  sthread_tls_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sthread_tls_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  task_push_load_content_from_cli (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_queue_check () ; 
 int /*<<< orphan*/  ui_companion_driver_init_first () ; 
 TYPE_3__ ui_companion_qt ; 
 int video_driver_active ; 

int rarch_main(int argc, char *argv[], void *data)
{
#if defined(_WIN32) && !defined(_XBOX) && !defined(__WINRT__)
   if (FAILED(CoInitialize(NULL)))
   {
      RARCH_ERR("FATAL: Failed to initialize the COM interface\n");
      return 1;
   }
#endif

   libretro_free_system_info(&runloop_system.info);
   command_event(CMD_EVENT_HISTORY_DEINIT, NULL);
   rarch_favorites_deinit();

   configuration_settings = (settings_t*)calloc(1, sizeof(settings_t));

   driver_ctl(RARCH_DRIVER_CTL_DEINIT,  NULL);
   rarch_ctl(RARCH_CTL_STATE_FREE,  NULL);
   global_free();

   frontend_driver_init_first(data);

   if (rarch_is_inited)
      driver_uninit(DRIVERS_CMD_ALL);

#ifdef HAVE_THREAD_STORAGE
   sthread_tls_create(&rarch_tls);
   sthread_tls_set(&rarch_tls, MAGIC_POINTER);
#endif
   video_driver_active = true;
   audio_driver_active = true;
   {
      uint8_t i;
      for (i = 0; i < MAX_USERS; i++)
         input_config_set_device(i, RETRO_DEVICE_JOYPAD);
   }
   retroarch_msg_queue_init();

   if (frontend_driver_is_inited())
   {
      content_ctx_info_t info;

      info.argc            = argc;
      info.argv            = argv;
      info.args            = data;
      info.environ_get     = frontend_driver_environment_get_ptr();

      if (!task_push_load_content_from_cli(
               NULL,
               NULL,
               &info,
               CORE_TYPE_PLAIN,
               NULL,
               NULL))
         return 1;
   }

   ui_companion_driver_init_first();

#if !defined(HAVE_MAIN) || defined(HAVE_QT)
   do
   {
      int ret;
      bool app_exit     = false;
#ifdef HAVE_QT
      ui_companion_qt.application->process_events();
#endif
      ret = runloop_iterate();

      task_queue_check();

#ifdef HAVE_QT
      app_exit = ui_companion_qt.application->exiting;
#endif

      if (ret == -1 || app_exit)
      {
#ifdef HAVE_QT
         ui_companion_qt.application->quit();
#endif
         break;
      }
   }while(1);

   main_exit(data);
#endif

   return 0;
}