#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* else_expr; TYPE_2__* then_expr; TYPE_2__* cond; } ;
struct TYPE_9__ {TYPE_1__ ternary; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_TERNARY ; 
 TYPE_2__* new_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Expr *new_expr_ternary(SrcPos pos, Expr *cond, Expr *then_expr, Expr *else_expr) {
    Expr *e = new_expr(EXPR_TERNARY, pos);
    e->ternary.cond = cond;
    e->ternary.then_expr = then_expr;
    e->ternary.else_expr = else_expr;
    return e;
}