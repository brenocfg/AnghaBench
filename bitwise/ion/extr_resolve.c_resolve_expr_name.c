#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ kind; int /*<<< orphan*/  name; int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  Operand ;
typedef  TYPE_1__ Expr ;

/* Variables and functions */
 scalar_t__ EXPR_NAME ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  resolve_name_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Operand resolve_expr_name(Expr *expr) {
    assert(expr->kind == EXPR_NAME);
    return resolve_name_operand(expr->pos, expr->name);
}