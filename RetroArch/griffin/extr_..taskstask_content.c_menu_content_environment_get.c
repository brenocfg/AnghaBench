#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rarch_main_wrap {int touched; int /*<<< orphan*/ * libretro_path; int /*<<< orphan*/ * content_path; int /*<<< orphan*/ * state_path; int /*<<< orphan*/ * sram_path; int /*<<< orphan*/ * config_path; int /*<<< orphan*/  verbose; int /*<<< orphan*/  no_content; } ;
struct TYPE_3__ {int /*<<< orphan*/  load_no_content; } ;
typedef  TYPE_1__ rarch_system_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_DIR_SAVEFILE ; 
 int /*<<< orphan*/  RARCH_DIR_SAVESTATE ; 
 int /*<<< orphan*/  RARCH_OVERRIDE_SETTING_LIBRETRO ; 
 int /*<<< orphan*/  RARCH_OVERRIDE_SETTING_VERBOSITY ; 
 int /*<<< orphan*/  RARCH_PATH_CONFIG ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  RARCH_PATH_CORE ; 
 void* dir_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retroarch_override_setting_is_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* runloop_get_system_info () ; 
 scalar_t__ string_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbosity_is_enabled () ; 

__attribute__((used)) static void menu_content_environment_get(int *argc, char *argv[],
      void *args, void *params_data)
{
   struct rarch_main_wrap *wrap_args = (struct rarch_main_wrap*)params_data;
   rarch_system_info_t *sys_info     = runloop_get_system_info();

   if (!wrap_args)
      return;

   wrap_args->no_content       = sys_info->load_no_content;

   if (!retroarch_override_setting_is_set(RARCH_OVERRIDE_SETTING_VERBOSITY, NULL))
      wrap_args->verbose       = verbosity_is_enabled();

   wrap_args->touched          = true;
   wrap_args->config_path      = NULL;
   wrap_args->sram_path        = NULL;
   wrap_args->state_path       = NULL;
   wrap_args->content_path     = NULL;

   if (!path_is_empty(RARCH_PATH_CONFIG))
      wrap_args->config_path   = path_get(RARCH_PATH_CONFIG);
   if (!dir_is_empty(RARCH_DIR_SAVEFILE))
      wrap_args->sram_path     = dir_get(RARCH_DIR_SAVEFILE);
   if (!dir_is_empty(RARCH_DIR_SAVESTATE))
      wrap_args->state_path    = dir_get(RARCH_DIR_SAVESTATE);
   if (!path_is_empty(RARCH_PATH_CONTENT))
      wrap_args->content_path  = path_get(RARCH_PATH_CONTENT);
   if (!retroarch_override_setting_is_set(RARCH_OVERRIDE_SETTING_LIBRETRO, NULL))
      wrap_args->libretro_path = string_is_empty(path_get(RARCH_PATH_CORE)) ? NULL :
         path_get(RARCH_PATH_CORE);

}