#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TokenKind ;
struct TYPE_2__ {int /*<<< orphan*/  kind; int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ is_cmp_op () ; 
 int /*<<< orphan*/ * new_expr_binary (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_token () ; 
 int /*<<< orphan*/ * parse_expr_add () ; 
 TYPE_1__ token ; 

Expr *parse_expr_cmp(void) {
    Expr *expr = parse_expr_add();
    while (is_cmp_op()) {
        SrcPos pos = token.pos;
        TokenKind op = token.kind;
        next_token();
        expr = new_expr_binary(pos, op, expr, parse_expr_add());
    }
    return expr;
}