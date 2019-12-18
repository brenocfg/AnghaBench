#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ menu_entry ;

/* Variables and functions */
 int array_size (TYPE_1__**) ; 
 TYPE_1__** e_menu_table ; 
 TYPE_1__* me_list_i ; 
 TYPE_1__* me_list_table ; 

menu_entry *me_list_get_next(void)
{
	int i;

	me_list_i++;
	if (me_list_i->name != NULL)
		return me_list_i;

	for (i = 0; i < array_size(e_menu_table); i++)
		if (me_list_table == e_menu_table[i])
			break;

	if (i + 1 < array_size(e_menu_table))
		me_list_table = me_list_i = e_menu_table[i + 1];
	else
		me_list_table = me_list_i = NULL;

	return me_list_i;
}