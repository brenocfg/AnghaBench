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
struct TYPE_2__ {int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_COLON ; 
 int /*<<< orphan*/  TOKEN_QUESTION ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_expr_ternary (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parse_expr_or () ; 
 TYPE_1__ token ; 

Expr *parse_expr_ternary(void) {
    SrcPos pos = token.pos;
    Expr *expr = parse_expr_or();
    if (match_token(TOKEN_QUESTION)) {
        Expr *then_expr = parse_expr_ternary();
        expect_token(TOKEN_COLON);
        Expr *else_expr = parse_expr_ternary();
        expr = new_expr_ternary(pos, expr, then_expr, else_expr);
    }
    return expr;
}