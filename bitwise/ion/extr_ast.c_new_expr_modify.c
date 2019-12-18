#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TokenKind ;
struct TYPE_6__ {int post; TYPE_2__* expr; int /*<<< orphan*/  op; } ;
struct TYPE_7__ {TYPE_1__ modify; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_MODIFY ; 
 TYPE_2__* new_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Expr *new_expr_modify(SrcPos pos, TokenKind op, bool post, Expr *expr) {
    Expr *e = new_expr(EXPR_MODIFY, pos);
    e->modify.op = op;
    e->modify.post = post;
    e->modify.expr = expr;
    return e;
}