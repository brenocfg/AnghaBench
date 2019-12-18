#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* expr; } ;
struct symbol {scalar_t__ type; int flags; TYPE_3__ rev_dep; struct property* prop; } ;
struct TYPE_8__ {struct expr* expr; } ;
struct property {scalar_t__ type; TYPE_4__ visible; int /*<<< orphan*/  text; struct expr* expr; struct menu* menu; struct property* next; } ;
struct menu {struct property* prompt; struct menu* list; struct menu* next; struct menu* parent; struct symbol* sym; struct expr* dep; } ;
struct TYPE_6__ {struct symbol* sym; } ;
struct TYPE_5__ {struct expr* expr; } ;
struct expr {TYPE_2__ right; TYPE_1__ left; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_EQUAL ; 
 int /*<<< orphan*/  E_LIST ; 
 int /*<<< orphan*/  E_UNEQUAL ; 
 int /*<<< orphan*/  P_CHOICE ; 
 scalar_t__ P_DEFAULT ; 
 scalar_t__ P_PROMPT ; 
 scalar_t__ P_SELECT ; 
 int SYMBOL_CHOICEVAL ; 
 int SYMBOL_WARNED ; 
 scalar_t__ S_TRISTATE ; 
 scalar_t__ S_UNKNOWN ; 
 struct menu* current_entry ; 
 void* expr_alloc_and (struct expr*,struct expr*) ; 
 struct expr* expr_alloc_comp (int /*<<< orphan*/ ,struct symbol*,int /*<<< orphan*/ *) ; 
 struct expr* expr_alloc_one (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* expr_alloc_or (void*,void*) ; 
 struct expr* expr_alloc_symbol (struct symbol*) ; 
 int /*<<< orphan*/  expr_contains_symbol (struct expr*,struct symbol*) ; 
 struct expr* expr_copy (struct expr*) ; 
 scalar_t__ expr_depends_symbol (struct expr*,struct symbol*) ; 
 struct expr* expr_eliminate_dups (struct expr*) ; 
 int /*<<< orphan*/  expr_eliminate_eq (struct expr**,struct expr**) ; 
 int /*<<< orphan*/  expr_free (struct expr*) ; 
 int /*<<< orphan*/  expr_is_yes (struct expr*) ; 
 struct expr* expr_trans_bool (struct expr*) ; 
 struct expr* expr_trans_compare (struct expr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct expr* expr_transform (struct expr*) ; 
 int /*<<< orphan*/  menu_add_symbol (int /*<<< orphan*/ ,struct symbol*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_set_type (scalar_t__) ; 
 int /*<<< orphan*/  menu_warn (struct menu*,char*) ; 
 struct symbol* prop_get_symbol (struct property*) ; 
 int /*<<< orphan*/  prop_warn (struct property*,char*) ; 
 int /*<<< orphan*/  sym_check_prop (struct symbol*) ; 
 struct property* sym_get_choice_prop (struct symbol*) ; 
 scalar_t__ sym_is_choice (struct symbol*) ; 
 int /*<<< orphan*/  sym_is_choice_value (struct symbol*) ; 
 int /*<<< orphan*/  sym_is_optional (struct symbol*) ; 
 struct symbol symbol_mod ; 
 int /*<<< orphan*/  symbol_no ; 
 int /*<<< orphan*/  symbol_yes ; 

void menu_finalize(struct menu *parent)
{
	struct menu *menu, *last_menu;
	struct symbol *sym;
	struct property *prop;
	struct expr *parentdep, *basedep, *dep, *dep2, **ep;

	sym = parent->sym;
	if (parent->list) {
		if (sym && sym_is_choice(sym)) {
			if (sym->type == S_UNKNOWN) {
				/* find the first choice value to find out choice type */
				current_entry = parent;
				for (menu = parent->list; menu; menu = menu->next) {
					if (menu->sym && menu->sym->type != S_UNKNOWN) {
						menu_set_type(menu->sym->type);
						break;
					}
				}
			}
			/* set the type of the remaining choice values */
			for (menu = parent->list; menu; menu = menu->next) {
				current_entry = menu;
				if (menu->sym && menu->sym->type == S_UNKNOWN)
					menu_set_type(sym->type);
			}
			parentdep = expr_alloc_symbol(sym);
		} else if (parent->prompt)
			parentdep = parent->prompt->visible.expr;
		else
			parentdep = parent->dep;

		for (menu = parent->list; menu; menu = menu->next) {
			basedep = expr_transform(menu->dep);
			basedep = expr_alloc_and(expr_copy(parentdep), basedep);
			basedep = expr_eliminate_dups(basedep);
			menu->dep = basedep;
			if (menu->sym)
				prop = menu->sym->prop;
			else
				prop = menu->prompt;
			for (; prop; prop = prop->next) {
				if (prop->menu != menu)
					continue;
				dep = expr_transform(prop->visible.expr);
				dep = expr_alloc_and(expr_copy(basedep), dep);
				dep = expr_eliminate_dups(dep);
				if (menu->sym && menu->sym->type != S_TRISTATE)
					dep = expr_trans_bool(dep);
				prop->visible.expr = dep;
				if (prop->type == P_SELECT) {
					struct symbol *es = prop_get_symbol(prop);
					es->rev_dep.expr = expr_alloc_or(es->rev_dep.expr,
							expr_alloc_and(expr_alloc_symbol(menu->sym), expr_copy(dep)));
				}
			}
		}
		for (menu = parent->list; menu; menu = menu->next)
			menu_finalize(menu);
	} else if (sym) {
		basedep = parent->prompt ? parent->prompt->visible.expr : NULL;
		basedep = expr_trans_compare(basedep, E_UNEQUAL, &symbol_no);
		basedep = expr_eliminate_dups(expr_transform(basedep));
		last_menu = NULL;
		for (menu = parent->next; menu; menu = menu->next) {
			dep = menu->prompt ? menu->prompt->visible.expr : menu->dep;
			if (!expr_contains_symbol(dep, sym))
				break;
			if (expr_depends_symbol(dep, sym))
				goto next;
			dep = expr_trans_compare(dep, E_UNEQUAL, &symbol_no);
			dep = expr_eliminate_dups(expr_transform(dep));
			dep2 = expr_copy(basedep);
			expr_eliminate_eq(&dep, &dep2);
			expr_free(dep);
			if (!expr_is_yes(dep2)) {
				expr_free(dep2);
				break;
			}
			expr_free(dep2);
		next:
			menu_finalize(menu);
			menu->parent = parent;
			last_menu = menu;
		}
		if (last_menu) {
			parent->list = parent->next;
			parent->next = last_menu->next;
			last_menu->next = NULL;
		}
	}
	for (menu = parent->list; menu; menu = menu->next) {
		if (sym && sym_is_choice(sym) &&
		    menu->sym && !sym_is_choice_value(menu->sym)) {
			current_entry = menu;
			menu->sym->flags |= SYMBOL_CHOICEVAL;
			if (!menu->prompt)
				menu_warn(menu, "choice value must have a prompt");
			for (prop = menu->sym->prop; prop; prop = prop->next) {
				if (prop->type == P_DEFAULT)
					prop_warn(prop, "defaults for choice "
						  "values not supported");
				if (prop->menu == menu)
					continue;
				if (prop->type == P_PROMPT &&
				    prop->menu->parent->sym != sym)
					prop_warn(prop, "choice value used outside its choice group");
			}
			/* Non-tristate choice values of tristate choices must
			 * depend on the choice being set to Y. The choice
			 * values' dependencies were propagated to their
			 * properties above, so the change here must be re-
			 * propagated.
			 */
			if (sym->type == S_TRISTATE && menu->sym->type != S_TRISTATE) {
				basedep = expr_alloc_comp(E_EQUAL, sym, &symbol_yes);
				menu->dep = expr_alloc_and(basedep, menu->dep);
				for (prop = menu->sym->prop; prop; prop = prop->next) {
					if (prop->menu != menu)
						continue;
					prop->visible.expr = expr_alloc_and(expr_copy(basedep),
									    prop->visible.expr);
				}
			}
			menu_add_symbol(P_CHOICE, sym, NULL);
			prop = sym_get_choice_prop(sym);
			for (ep = &prop->expr; *ep; ep = &(*ep)->left.expr)
				;
			*ep = expr_alloc_one(E_LIST, NULL);
			(*ep)->right.sym = menu->sym;
		}
		if (menu->list && (!menu->prompt || !menu->prompt->text)) {
			for (last_menu = menu->list; ; last_menu = last_menu->next) {
				last_menu->parent = parent;
				if (!last_menu->next)
					break;
			}
			last_menu->next = menu->next;
			menu->next = menu->list;
			menu->list = NULL;
		}
	}

	if (sym && !(sym->flags & SYMBOL_WARNED)) {
		if (sym->type == S_UNKNOWN)
			menu_warn(parent, "config symbol defined without type");

		if (sym_is_choice(sym) && !parent->prompt)
			menu_warn(parent, "choice must have a prompt");

		/* Check properties connected to this symbol */
		sym_check_prop(sym);
		sym->flags |= SYMBOL_WARNED;
	}

	if (sym && !sym_is_optional(sym) && parent->prompt) {
		sym->rev_dep.expr = expr_alloc_or(sym->rev_dep.expr,
				expr_alloc_and(parent->prompt->visible.expr,
					expr_alloc_symbol(&symbol_mod)));
	}
}