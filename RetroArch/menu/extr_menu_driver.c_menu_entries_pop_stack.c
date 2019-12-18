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
 int /*<<< orphan*/  menu_list_pop_stack (int /*<<< orphan*/ *,size_t,size_t*,int) ; 

void menu_entries_pop_stack(size_t *ptr, size_t idx, bool animate)
{
   menu_list_t *menu_list         = menu_entries_list;
   if (menu_list)
      menu_list_pop_stack(menu_list, idx, ptr, animate);
}