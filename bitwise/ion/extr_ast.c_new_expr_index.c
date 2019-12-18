#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* index; TYPE_2__* expr; } ;
struct TYPE_8__ {TYPE_1__ index; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_INDEX ; 
 TYPE_2__* new_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Expr *new_expr_index(SrcPos pos, Expr *expr, Expr *index) {
    Expr *e = new_expr(EXPR_INDEX, pos);
    e->index.expr = expr;
    e->index.index = index;
    return e;
}