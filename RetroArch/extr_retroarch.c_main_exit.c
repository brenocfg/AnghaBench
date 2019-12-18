#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ config_save_on_exit; } ;
struct TYPE_6__ {int /*<<< orphan*/  video_driver; } ;
struct TYPE_8__ {TYPE_2__ bools; TYPE_1__ arrays; } ;
typedef  TYPE_3__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_LOG_FILE_DEINIT ; 
 int /*<<< orphan*/  CMD_EVENT_MENU_SAVE_CURRENT_CONFIG ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  DRIVERS_CMD_ALL ; 
 int /*<<< orphan*/  RARCH_CTL_DATA_DEINIT ; 
 int /*<<< orphan*/  RARCH_CTL_MAIN_DEINIT ; 
 int /*<<< orphan*/  RARCH_CTL_STATE_FREE ; 
 int /*<<< orphan*/  RARCH_DRIVER_CTL_DEINIT ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RARCH_MENU_CTL_UNSET_OWN_DRIVER ; 
 int /*<<< orphan*/  RARCH_PATH_CORE ; 
 scalar_t__* cached_video_driver ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* configuration_settings ; 
 int /*<<< orphan*/  driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  frontend_driver_deinit (void*) ; 
 int /*<<< orphan*/  frontend_driver_exitspawn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frontend_driver_free () ; 
 int /*<<< orphan*/  frontend_driver_shutdown (int) ; 
 int /*<<< orphan*/  global_free () ; 
 int has_set_username ; 
 int /*<<< orphan*/  logger_shutdown () ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_get_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_get_realsize (int /*<<< orphan*/ ) ; 
 int rarch_block_config_read ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rarch_error_on_init ; 
 int rarch_is_inited ; 
 int /*<<< orphan*/  rarch_perf_log () ; 
 int /*<<< orphan*/  retroarch_msg_queue_deinit () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ui_companion_driver_deinit () ; 
 int /*<<< orphan*/  ui_companion_driver_free () ; 

void main_exit(void *args)
{
   settings_t *settings = configuration_settings;
   
   if (cached_video_driver[0])
   {
      strcpy(settings->arrays.video_driver, cached_video_driver);
      cached_video_driver[0] = 0;
      RARCH_LOG("[Video]: Restored video driver to \"%s\".\n", settings->arrays.video_driver);
   }

   if (settings->bools.config_save_on_exit)
      command_event(CMD_EVENT_MENU_SAVE_CURRENT_CONFIG, NULL);

#ifdef HAVE_MENU
   /* Do not want menu context to live any more. */
   menu_driver_ctl(RARCH_MENU_CTL_UNSET_OWN_DRIVER, NULL);
#endif
   rarch_ctl(RARCH_CTL_MAIN_DEINIT, NULL);

   rarch_perf_log();

#if defined(HAVE_LOGGER) && !defined(ANDROID)
   logger_shutdown();
#endif

   frontend_driver_deinit(args);
   frontend_driver_exitspawn(
         path_get_ptr(RARCH_PATH_CORE),
         path_get_realsize(RARCH_PATH_CORE));

   has_set_username        = false;
   rarch_is_inited         = false;
   rarch_error_on_init     = false;
   rarch_block_config_read = false;

   retroarch_msg_queue_deinit();
   driver_uninit(DRIVERS_CMD_ALL);
   command_event(CMD_EVENT_LOG_FILE_DEINIT, NULL);

   rarch_ctl(RARCH_CTL_STATE_FREE,  NULL);
   global_free();
   rarch_ctl(RARCH_CTL_DATA_DEINIT, NULL);

   if (configuration_settings)
      free(configuration_settings);
   configuration_settings = NULL;

   ui_companion_driver_deinit();

   frontend_driver_shutdown(false);

   driver_ctl(RARCH_DRIVER_CTL_DEINIT, NULL);
   ui_companion_driver_free();
   frontend_driver_free();

#if defined(_WIN32) && !defined(_XBOX) && !defined(__WINRT__)
   CoUninitialize();
#endif
}