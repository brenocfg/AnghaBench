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
 int /*<<< orphan*/  GTK_PANED (int /*<<< orphan*/ ) ; 
 int MENU_ROOT ; 
 scalar_t__ OPT_ALL ; 
 scalar_t__ OPT_NORMAL ; 
 scalar_t__ OPT_PROMPT ; 
 int P_MENU ; 
 int P_UNKNOWN ; 
 scalar_t__ SINGLE_VIEW ; 
 scalar_t__ SPLIT_VIEW ; 
 int /*<<< orphan*/  SYMBOL_CHANGED ; 
 struct menu* current ; 
 char* dbg_sym_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_row (struct menu*) ; 
 int /*<<< orphan*/  gtk_paned_set_position (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpaned ; 
 int indent ; 
 scalar_t__ menu_get_prompt (struct menu*) ; 
 scalar_t__ menu_has_prompt (struct menu*) ; 
 scalar_t__ menu_is_visible (struct menu*) ; 
 scalar_t__ opt_mode ; 
 int /*<<< orphan*/  place_node (struct menu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* prop_get_type_name (int) ; 
 struct menu rootmenu ; 
 char* sym_type_name (int /*<<< orphan*/ ) ; 
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

		if ((opt_mode == OPT_NORMAL && menu_is_visible(child)) ||
		    (opt_mode == OPT_PROMPT && menu_has_prompt(child)) ||
		    (opt_mode == OPT_ALL    && menu_get_prompt(child)))
			place_node(child, fill_row(child));
#ifdef DEBUG
		printf("%*c%s: ", indent, ' ', menu_get_prompt(child));
		printf("%s", child->flags & MENU_ROOT ? "rootmenu | " : "");
		printf("%s", prop_get_type_name(ptype));
		printf(" | ");
		if (sym) {
			printf("%s", sym_type_name(sym->type));
			printf(" | ");
			printf("%s", dbg_sym_flags(sym->flags));
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

		/* Change paned position if the view is not in 'split mode' */
		if (view_mode == SINGLE_VIEW || view_mode == FULL_VIEW) {
			gtk_paned_set_position(GTK_PANED(hpaned), 0);
		}

		if (((view_mode == SINGLE_VIEW) && (menu->flags & MENU_ROOT))
		    || (view_mode == FULL_VIEW)
		    || (view_mode == SPLIT_VIEW)) {
			indent++;
			display_tree(child);
			indent--;
		}
	}
}