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
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * menu_entries_list_settings ; 
 int /*<<< orphan*/  menu_setting_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void menu_entries_settings_deinit(void)
{
   menu_setting_free(menu_entries_list_settings);
   if (menu_entries_list_settings)
      free(menu_entries_list_settings);
   menu_entries_list_settings = NULL;
}