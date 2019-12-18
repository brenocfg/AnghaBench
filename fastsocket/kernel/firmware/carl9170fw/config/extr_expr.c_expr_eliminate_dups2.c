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
struct TYPE_4__ {struct expr* expr; } ;
struct TYPE_3__ {struct expr* expr; } ;
struct expr {int type; TYPE_2__ right; TYPE_1__ left; } ;
typedef  enum expr_type { ____Placeholder_expr_type } expr_type ;

/* Variables and functions */
#define  E_AND 129 
 int /*<<< orphan*/  E_NOT ; 
#define  E_OR 128 
 struct expr* e1 ; 
 struct expr* e2 ; 
 int /*<<< orphan*/  expr_alloc_one (int /*<<< orphan*/ ,struct expr*) ; 
 struct expr* expr_alloc_symbol (int /*<<< orphan*/ *) ; 
 struct expr* expr_copy (struct expr*) ; 
 struct expr* expr_extract_eq_and (struct expr**,struct expr**) ; 
 struct expr* expr_extract_eq_or (struct expr**,struct expr**) ; 
 int /*<<< orphan*/  expr_free (struct expr*) ; 
 int /*<<< orphan*/  expr_is_no (struct expr*) ; 
 int /*<<< orphan*/  expr_is_yes (struct expr*) ; 
 struct expr* expr_transform (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol_no ; 
 int /*<<< orphan*/  symbol_yes ; 
 int /*<<< orphan*/  trans_count ; 

__attribute__((used)) static void expr_eliminate_dups2(enum expr_type type, struct expr **ep1, struct expr **ep2)
{
#define e1 (*ep1)
#define e2 (*ep2)
	struct expr *tmp, *tmp1, *tmp2;

	if (e1->type == type) {
		expr_eliminate_dups2(type, &e1->left.expr, &e2);
		expr_eliminate_dups2(type, &e1->right.expr, &e2);
		return;
	}
	if (e2->type == type) {
		expr_eliminate_dups2(type, &e1, &e2->left.expr);
		expr_eliminate_dups2(type, &e1, &e2->right.expr);
	}
	if (e1 == e2)
		return;

	switch (e1->type) {
	case E_OR:
		expr_eliminate_dups2(e1->type, &e1, &e1);
		// (FOO || BAR) && (!FOO && !BAR) -> n
		tmp1 = expr_transform(expr_alloc_one(E_NOT, expr_copy(e1)));
		tmp2 = expr_copy(e2);
		tmp = expr_extract_eq_and(&tmp1, &tmp2);
		if (expr_is_yes(tmp1)) {
			expr_free(e1);
			e1 = expr_alloc_symbol(&symbol_no);
			trans_count++;
		}
		expr_free(tmp2);
		expr_free(tmp1);
		expr_free(tmp);
		break;
	case E_AND:
		expr_eliminate_dups2(e1->type, &e1, &e1);
		// (FOO && BAR) || (!FOO || !BAR) -> y
		tmp1 = expr_transform(expr_alloc_one(E_NOT, expr_copy(e1)));
		tmp2 = expr_copy(e2);
		tmp = expr_extract_eq_or(&tmp1, &tmp2);
		if (expr_is_no(tmp1)) {
			expr_free(e1);
			e1 = expr_alloc_symbol(&symbol_yes);
			trans_count++;
		}
		expr_free(tmp2);
		expr_free(tmp1);
		expr_free(tmp);
		break;
	default:
		;
	}
#undef e1
#undef e2
}