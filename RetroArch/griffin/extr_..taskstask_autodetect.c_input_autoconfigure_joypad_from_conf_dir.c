#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct string_list {size_t size; TYPE_1__* elems; } ;
typedef  int /*<<< orphan*/  retro_task_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  config_file_t ;
typedef  int /*<<< orphan*/  best_path ;
struct TYPE_7__ {char* autoconfig_directory; } ;
typedef  TYPE_2__ autoconfig_params_t ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPLICATION_SPECIAL_DIRECTORY_AUTOCONFIG ; 
 int /*<<< orphan*/  DIR_LIST_AUTOCONFIG ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  config_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * config_file_new_from_path_to_string (int /*<<< orphan*/ ) ; 
 struct string_list* dir_list_new_special (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fill_pathname_application_special (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_autoconfigure_joypad_add (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int input_autoconfigure_joypad_try_from_conf (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool input_autoconfigure_joypad_from_conf_dir(
      autoconfig_params_t *params, retro_task_t *task)
{
   size_t i;
   char path[PATH_MAX_LENGTH];
   char best_path[PATH_MAX_LENGTH];
   int ret                    = 0;
   int index                  = -1;
   int current_best           = 0;
   config_file_t *best_conf   = NULL;
   struct string_list *list   = NULL;

   best_path[0]               = '\0';
   path[0]                    = '\0';

   fill_pathname_application_special(path, sizeof(path),
         APPLICATION_SPECIAL_DIRECTORY_AUTOCONFIG);

   list = dir_list_new_special(path, DIR_LIST_AUTOCONFIG, "cfg");

   if (!list || !list->size)
   {
      if (list)
      {
         string_list_free(list);
         list = NULL;
      }
      if (!string_is_empty(params->autoconfig_directory))
         list = dir_list_new_special(params->autoconfig_directory,
               DIR_LIST_AUTOCONFIG, "cfg");
   }

   if (!list)
   {
      RARCH_LOG("[Autoconf]: No profiles found.\n");
      return false;
   }

   RARCH_LOG("[Autoconf]: %d profiles found.\n", (int)list->size);

   for (i = 0; i < list->size; i++)
   {
      int res;
      config_file_t *conf = config_file_new_from_path_to_string(list->elems[i].data);
      
      if (!conf)
         continue;

      res  = input_autoconfigure_joypad_try_from_conf(conf, params);

      if (res >= current_best)
      {
         index        = (int)i;
         current_best = res;
         if (best_conf)
            config_file_free(best_conf);
         strlcpy(best_path, list->elems[i].data, sizeof(best_path));
         best_conf    = NULL;
         best_conf    = conf;
      }
      else
         config_file_free(conf);
   }

   if (index >= 0 && current_best > 0 && best_conf)
   {
      RARCH_LOG("[Autoconf]: selected configuration: %s\n", best_path);
      input_autoconfigure_joypad_add(best_conf, params, task);
      ret = 1;
   }

   if (best_conf)
      config_file_free(best_conf);

   string_list_free(list);

   if (ret == 0)
      return false;
   return true;
}