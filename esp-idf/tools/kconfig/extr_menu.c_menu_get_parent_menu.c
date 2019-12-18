#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct menu {TYPE_1__* prompt; struct menu* parent; } ;
typedef  enum prop_type { ____Placeholder_prop_type } prop_type ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int P_MENU ; 
 struct menu rootmenu ; 

struct menu *menu_get_parent_menu(struct menu *menu)
{
	enum prop_type type;

	for (; menu != &rootmenu; menu = menu->parent) {
		type = menu->prompt ? menu->prompt->type : 0;
		if (type == P_MENU)
			break;
	}
	return menu;
}