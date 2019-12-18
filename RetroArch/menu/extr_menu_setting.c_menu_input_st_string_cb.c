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
typedef  int /*<<< orphan*/  rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  menu_input_dialog_end () ; 
 char* menu_input_dialog_get_label_setting_buffer () ; 
 int /*<<< orphan*/ * menu_setting_find (char const*) ; 
 int /*<<< orphan*/  menu_setting_generic (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setting_set_with_string_representation (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 

__attribute__((used)) static void menu_input_st_string_cb(void *userdata, const char *str)
{
   if (str && *str)
   {
      rarch_setting_t *setting = NULL;
      const char        *label = menu_input_dialog_get_label_setting_buffer();

      if (!string_is_empty(label))
         setting = menu_setting_find(label);

      if (setting)
      {
         setting_set_with_string_representation(setting, str);
         menu_setting_generic(setting, false);
      }
   }

   menu_input_dialog_end();
}