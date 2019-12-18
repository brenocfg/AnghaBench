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
 int /*<<< orphan*/ * menu_setting_find (char const*) ; 
 int menu_setting_generic (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setting_set_with_string_representation (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int set_path_generic(const char *label, const char *action_path)
{
   rarch_setting_t *setting = menu_setting_find(label);

   if (setting)
   {
      setting_set_with_string_representation(
            setting, action_path);
      return menu_setting_generic(setting, false);
   }

   return 0;
}