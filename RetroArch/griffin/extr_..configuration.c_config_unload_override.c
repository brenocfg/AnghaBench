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

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  RARCH_OVERRIDE_SETTING_SAVE_PATH ; 
 int /*<<< orphan*/  RARCH_OVERRIDE_SETTING_STATE_PATH ; 
 int /*<<< orphan*/  RARCH_PATH_CONFIG ; 
 int /*<<< orphan*/  RARCH_PATH_CONFIG_APPEND ; 
 int /*<<< orphan*/  config_get_ptr () ; 
 int /*<<< orphan*/  config_load_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  global_get_ptr () ; 
 int /*<<< orphan*/  path_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retroarch_override_setting_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  retroarch_override_setting_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool config_unload_override(void)
{
   path_clear(RARCH_PATH_CONFIG_APPEND);

   /* Toggle has_save_path to false so it resets */
   retroarch_override_setting_unset(RARCH_OVERRIDE_SETTING_STATE_PATH, NULL);
   retroarch_override_setting_unset(RARCH_OVERRIDE_SETTING_SAVE_PATH,  NULL);

   if (!config_load_file(global_get_ptr(),
            path_get(RARCH_PATH_CONFIG), config_get_ptr()))
      return false;

   RARCH_LOG("[Overrides] configuration overrides unloaded, original configuration restored.\n");

   /* Reset save paths */
   retroarch_override_setting_set(RARCH_OVERRIDE_SETTING_STATE_PATH, NULL);
   retroarch_override_setting_set(RARCH_OVERRIDE_SETTING_SAVE_PATH, NULL);

   return true;
}