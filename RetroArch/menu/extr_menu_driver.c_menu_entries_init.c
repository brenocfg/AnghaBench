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
typedef  int /*<<< orphan*/  menu_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_SETTING_CTL_NEW ; 
 int /*<<< orphan*/ * menu_entries_list ; 
 int /*<<< orphan*/  menu_entries_list_deinit () ; 
 int /*<<< orphan*/  menu_entries_list_settings ; 
 int /*<<< orphan*/  menu_entries_settings_deinit () ; 
 scalar_t__ menu_list_new () ; 
 int /*<<< orphan*/  menu_setting_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool menu_entries_init(void)
{
   if (!(menu_entries_list = (menu_list_t*)menu_list_new()))
      goto error;

   menu_setting_ctl(MENU_SETTING_CTL_NEW, &menu_entries_list_settings);

   if (!menu_entries_list_settings)
      goto error;

   return true;

error:
   menu_entries_settings_deinit();
   menu_entries_list_deinit();

   return false;
}