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
 int /*<<< orphan*/ * menu_entries_list ; 
 int /*<<< orphan*/  menu_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void menu_entries_list_deinit(void)
{
   if (menu_entries_list)
      menu_list_free(menu_entries_list);
   menu_entries_list     = NULL;
}