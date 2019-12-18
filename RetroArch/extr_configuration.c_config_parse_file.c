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
typedef  int /*<<< orphan*/  global_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,char const*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  RARCH_PATH_CONFIG ; 
 int /*<<< orphan*/  config_get_ptr () ; 
 int /*<<< orphan*/  config_load_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 char* path_get (int /*<<< orphan*/ ) ; 
 scalar_t__ path_is_empty (int /*<<< orphan*/ ) ; 

void config_parse_file(void *data)
{
   global_t *global = (global_t*)data;
   if (path_is_empty(RARCH_PATH_CONFIG))
   {
      RARCH_LOG("[config] Loading default config.\n");
   }

   {
      const char *config_path = path_get(RARCH_PATH_CONFIG);
      RARCH_LOG("[config] loading config from: %s.\n", config_path);

      if (!config_load_file(global, config_path, config_get_ptr()))
      {
         RARCH_ERR("[config] couldn't find config at path: \"%s\"\n",
               config_path);
      }
   }
}