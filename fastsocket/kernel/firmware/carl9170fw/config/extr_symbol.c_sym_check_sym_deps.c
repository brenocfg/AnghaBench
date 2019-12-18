#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * expr; } ;
struct symbol {struct property* prop; TYPE_1__ rev_dep; } ;
struct TYPE_4__ {int /*<<< orphan*/ * expr; } ;
struct property {scalar_t__ type; int /*<<< orphan*/ * expr; TYPE_2__ visible; struct property* next; } ;
struct dep_stack {int /*<<< orphan*/ * expr; struct property* prop; } ;

/* Variables and functions */
 scalar_t__ P_CHOICE ; 
 scalar_t__ P_DEFAULT ; 
 scalar_t__ P_SELECT ; 
 int /*<<< orphan*/  dep_stack_insert (struct dep_stack*,struct symbol*) ; 
 int /*<<< orphan*/  dep_stack_remove () ; 
 struct symbol* sym_check_expr_deps (int /*<<< orphan*/ *) ; 
 scalar_t__ sym_is_choice (struct symbol*) ; 

__attribute__((used)) static struct symbol *sym_check_sym_deps(struct symbol *sym)
{
	struct symbol *sym2;
	struct property *prop;
	struct dep_stack stack;

	dep_stack_insert(&stack, sym);

	sym2 = sym_check_expr_deps(sym->rev_dep.expr);
	if (sym2)
		goto out;

	for (prop = sym->prop; prop; prop = prop->next) {
		if (prop->type == P_CHOICE || prop->type == P_SELECT)
			continue;
		stack.prop = prop;
		sym2 = sym_check_expr_deps(prop->visible.expr);
		if (sym2)
			break;
		if (prop->type != P_DEFAULT || sym_is_choice(sym))
			continue;
		stack.expr = prop->expr;
		sym2 = sym_check_expr_deps(prop->expr);
		if (sym2)
			break;
		stack.expr = NULL;
	}

out:
	dep_stack_remove();

	return sym2;
}