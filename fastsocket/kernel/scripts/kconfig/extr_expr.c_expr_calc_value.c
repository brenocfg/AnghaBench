#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tristate ;
struct TYPE_8__ {TYPE_4__* sym; struct expr* expr; } ;
struct TYPE_7__ {TYPE_4__* sym; struct expr* expr; } ;
struct expr {int type; TYPE_3__ right; TYPE_2__ left; } ;
struct TYPE_6__ {int /*<<< orphan*/  tri; } ;
struct TYPE_9__ {TYPE_1__ curr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_AND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPR_NOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPR_OR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  E_AND 133 
#define  E_EQUAL 132 
#define  E_NOT 131 
#define  E_OR 130 
#define  E_SYMBOL 129 
#define  E_UNEQUAL 128 
 int /*<<< orphan*/  no ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  sym_calc_value (TYPE_4__*) ; 
 char* sym_get_string_value (TYPE_4__*) ; 
 int /*<<< orphan*/  yes ; 

tristate expr_calc_value(struct expr *e)
{
	tristate val1, val2;
	const char *str1, *str2;

	if (!e)
		return yes;

	switch (e->type) {
	case E_SYMBOL:
		sym_calc_value(e->left.sym);
		return e->left.sym->curr.tri;
	case E_AND:
		val1 = expr_calc_value(e->left.expr);
		val2 = expr_calc_value(e->right.expr);
		return EXPR_AND(val1, val2);
	case E_OR:
		val1 = expr_calc_value(e->left.expr);
		val2 = expr_calc_value(e->right.expr);
		return EXPR_OR(val1, val2);
	case E_NOT:
		val1 = expr_calc_value(e->left.expr);
		return EXPR_NOT(val1);
	case E_EQUAL:
		sym_calc_value(e->left.sym);
		sym_calc_value(e->right.sym);
		str1 = sym_get_string_value(e->left.sym);
		str2 = sym_get_string_value(e->right.sym);
		return !strcmp(str1, str2) ? yes : no;
	case E_UNEQUAL:
		sym_calc_value(e->left.sym);
		sym_calc_value(e->right.sym);
		str1 = sym_get_string_value(e->left.sym);
		str2 = sym_get_string_value(e->right.sym);
		return !strcmp(str1, str2) ? no : yes;
	default:
		printf("expr_calc_value: %d?\n", e->type);
		return no;
	}
}