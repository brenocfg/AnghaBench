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
 int E_AND ; 
 int E_OR ; 
 struct expr* e1 ; 
 struct expr* e2 ; 
 void* expr_alloc_symbol (int /*<<< orphan*/ *) ; 
 struct expr* expr_alloc_two (int,struct expr*,struct expr*) ; 
 scalar_t__ expr_eq (struct expr*,struct expr*) ; 
 int /*<<< orphan*/  expr_free (struct expr*) ; 
 int /*<<< orphan*/  symbol_no ; 
 int /*<<< orphan*/  symbol_yes ; 

void expr_extract_eq(enum expr_type type, struct expr **ep, struct expr **ep1, struct expr **ep2)
{
#define e1 (*ep1)
#define e2 (*ep2)
	if (e1->type == type) {
		expr_extract_eq(type, ep, &e1->left.expr, &e2);
		expr_extract_eq(type, ep, &e1->right.expr, &e2);
		return;
	}
	if (e2->type == type) {
		expr_extract_eq(type, ep, ep1, &e2->left.expr);
		expr_extract_eq(type, ep, ep1, &e2->right.expr);
		return;
	}
	if (expr_eq(e1, e2)) {
		*ep = *ep ? expr_alloc_two(type, *ep, e1) : e1;
		expr_free(e2);
		if (type == E_AND) {
			e1 = expr_alloc_symbol(&symbol_yes);
			e2 = expr_alloc_symbol(&symbol_yes);
		} else if (type == E_OR) {
			e1 = expr_alloc_symbol(&symbol_no);
			e2 = expr_alloc_symbol(&symbol_no);
		}
	}
#undef e1
#undef e2
}