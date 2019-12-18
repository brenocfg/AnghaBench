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
struct TYPE_8__ {size_t num_args; int /*<<< orphan*/  args; TYPE_2__* expr; } ;
struct TYPE_9__ {TYPE_1__ call; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  AST_DUP (TYPE_2__**) ; 
 int /*<<< orphan*/  EXPR_CALL ; 
 TYPE_2__* new_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Expr *new_expr_call(SrcPos pos, Expr *expr, Expr **args, size_t num_args) {
    Expr *e = new_expr(EXPR_CALL, pos);
    e->call.expr = expr;
    e->call.args = AST_DUP(args);
    e->call.num_args = num_args;
    return e;
}