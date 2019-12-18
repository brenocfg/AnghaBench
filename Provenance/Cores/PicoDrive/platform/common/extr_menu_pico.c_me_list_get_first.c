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
typedef  int /*<<< orphan*/  menu_entry ;

/* Variables and functions */
 int /*<<< orphan*/ ** e_menu_table ; 
 int /*<<< orphan*/ * me_list_i ; 
 int /*<<< orphan*/ * me_list_table ; 

menu_entry *me_list_get_first(void)
{
	me_list_table = me_list_i = e_menu_table[0];
	return me_list_i;
}