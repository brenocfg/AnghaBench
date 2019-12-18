#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  Operand ;
typedef  TYPE_1__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_cond_operand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_expr_rvalue (TYPE_1__*) ; 

void resolve_cond_expr(Expr *expr) {
    Operand cond = resolve_expr_rvalue(expr);
    if (!is_cond_operand(cond)) {
        fatal_error(expr->pos, "Conditional expression must have scalar type");
    }
}