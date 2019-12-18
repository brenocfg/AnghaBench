#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  path_cheat_database; } ;
struct TYPE_5__ {TYPE_1__ paths; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  cheat_manager_save (char const*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  menu_input_dialog_end () ; 
 char* menu_input_dialog_get_label_buffer () ; 
 int /*<<< orphan*/ * menu_setting_find (char const*) ; 
 int /*<<< orphan*/  menu_setting_generic (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setting_set_with_string_representation (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 

__attribute__((used)) static void menu_input_st_string_cb_cheat_file_save_as(
      void *userdata, const char *str)
{
   if (str && *str)
   {
      rarch_setting_t *setting = NULL;
      settings_t *settings     = config_get_ptr();
      const char        *label = menu_input_dialog_get_label_buffer();

      if (!string_is_empty(label))
         setting = menu_setting_find(label);

      if (setting)
      {
         setting_set_with_string_representation(setting, str);
         menu_setting_generic(setting, false);
      }
      else if (!string_is_empty(label))
         cheat_manager_save(str, settings->paths.path_cheat_database,false);
   }

   menu_input_dialog_end();
}