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
 int /*<<< orphan*/ * menu_entries_list ; 
 int /*<<< orphan*/  menu_list_flush_stack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,unsigned int) ; 

void menu_entries_flush_stack(const char *needle, unsigned final_type)
{
   menu_list_t *menu_list         = menu_entries_list;
   if (menu_list)
      menu_list_flush_stack(menu_list, 0, needle, final_type);
}