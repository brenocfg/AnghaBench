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
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ content_ctx_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_CTL_UNSET_BLOCK_CONFIG_READ ; 
 int /*<<< orphan*/  RARCH_PATH_CONFIG ; 
 int /*<<< orphan*/  RARCH_PATH_CORE ; 
 int /*<<< orphan*/  config_save_file (char const*) ; 
 int /*<<< orphan*/  path_clear (int /*<<< orphan*/ ) ; 
 char* path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ string_is_equal (char*,char const*) ; 
 int task_push_start_dummy_core (TYPE_1__*) ; 

bool config_replace(bool config_replace_save_on_exit, char *path)
{
   content_ctx_info_t content_info = {0};
   const char *rarch_path_config   = path_get(RARCH_PATH_CONFIG);

   /* If config file to be replaced is the same as the
    * current config file, exit. */
   if (string_is_equal(path, rarch_path_config))
      return false;

   if (config_replace_save_on_exit && !path_is_empty(RARCH_PATH_CONFIG))
      config_save_file(rarch_path_config);

   path_set(RARCH_PATH_CONFIG, path);

   rarch_ctl(RARCH_CTL_UNSET_BLOCK_CONFIG_READ, NULL);

   /* Load core in new config. */
   path_clear(RARCH_PATH_CORE);

   return task_push_start_dummy_core(&content_info);
}