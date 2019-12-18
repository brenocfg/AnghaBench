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
struct symbol {int dummy; } ;
struct menu {struct menu* next; int /*<<< orphan*/  lineno; int /*<<< orphan*/  file; int /*<<< orphan*/  parent; struct symbol* sym; } ;

/* Variables and functions */
 struct menu* current_entry ; 
 int /*<<< orphan*/  current_file ; 
 int /*<<< orphan*/  current_menu ; 
 struct menu** last_entry_ptr ; 
 struct menu* malloc (int) ; 
 int /*<<< orphan*/  memset (struct menu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zconf_lineno () ; 

void menu_add_entry(struct symbol *sym)
{
	struct menu *menu;

	menu = malloc(sizeof(*menu));
	memset(menu, 0, sizeof(*menu));
	menu->sym = sym;
	menu->parent = current_menu;
	menu->file = current_file;
	menu->lineno = zconf_lineno();

	*last_entry_ptr = menu;
	last_entry_ptr = &menu->next;
	current_entry = menu;
}