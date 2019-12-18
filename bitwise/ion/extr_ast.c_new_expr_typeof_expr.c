#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* typeof_expr; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  TYPE_1__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_TYPEOF_EXPR ; 
 TYPE_1__* new_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Expr *new_expr_typeof_expr(SrcPos pos, Expr *expr) {
    Expr *e = new_expr(EXPR_TYPEOF_EXPR, pos);
    e->typeof_expr  = expr;
    return e;
}