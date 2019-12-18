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
struct symbol {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct property {int type; } ;
struct menu {int flags; struct symbol* sym; struct property* prompt; struct menu* next; struct menu* list; } ;
typedef  enum prop_type { ____Placeholder_prop_type } prop_type ;

/* Variables and functions */
 scalar_t__ FULL_VIEW ; 
 int MENU_ROOT ; 
 int P_MENU ; 
 int P_UNKNOWN ; 
 scalar_t__ SINGLE_VIEW ; 
 scalar_t__ SPLIT_VIEW ; 
 int /*<<< orphan*/  SYMBOL_CHANGED ; 
 struct menu* current ; 
 int /*<<< orphan*/  dbg_print_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_print_ptype (int) ; 
 int /*<<< orphan*/  dbg_print_stype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_row (struct menu*) ; 
 int indent ; 
 int /*<<< orphan*/  menu_get_prompt (struct menu*) ; 
 scalar_t__ menu_is_visible (struct menu*) ; 
 int /*<<< orphan*/  place_node (struct menu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 struct menu rootmenu ; 
 scalar_t__ show_all ; 
 scalar_t__ tree ; 
 scalar_t__ tree1 ; 
 scalar_t__ tree2 ; 
 scalar_t__ view_mode ; 

__attribute__((used)) static void display_tree(struct menu *menu)
{
	struct symbol *sym;
	struct property *prop;
	struct menu *child;
	enum prop_type ptype;

	if (menu == &rootmenu) {
		indent = 1;
		current = &rootmenu;
	}

	for (child = menu->list; child; child = child->next) {
		prop = child->prompt;
		sym = child->sym;
		ptype = prop ? prop->type : P_UNKNOWN;

		if (sym)
			sym->flags &= ~SYMBOL_CHANGED;

		if ((view_mode == SPLIT_VIEW)
		    && !(child->flags & MENU_ROOT) && (tree == tree1))
			continue;

		if ((view_mode == SPLIT_VIEW) && (child->flags & MENU_ROOT)
		    && (tree == tree2))
			continue;

		if (menu_is_visible(child) || show_all)
			place_node(child, fill_row(child));
#ifdef DEBUG
		printf("%*c%s: ", indent, ' ', menu_get_prompt(child));
		printf("%s", child->flags & MENU_ROOT ? "rootmenu | " : "");
		dbg_print_ptype(ptype);
		printf(" | ");
		if (sym) {
			dbg_print_stype(sym->type);
			printf(" | ");
			dbg_print_flags(sym->flags);
			printf("\n");
		} else
			printf("\n");
#endif
		if ((view_mode != FULL_VIEW) && (ptype == P_MENU)
		    && (tree == tree2))
			continue;
/*
                if (((menu != &rootmenu) && !(menu->flags & MENU_ROOT))
		    || (view_mode == FULL_VIEW)
		    || (view_mode == SPLIT_VIEW))*/
		if (((view_mode == SINGLE_VIEW) && (menu->flags & MENU_ROOT))
		    || (view_mode == FULL_VIEW)
		    || (view_mode == SPLIT_VIEW)) {
			indent++;
			display_tree(child);
			indent--;
		}
	}
}