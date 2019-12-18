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
typedef  scalar_t__ TokenKind ;
struct TYPE_2__ {scalar_t__ kind; int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ TOKEN_DEC ; 
 scalar_t__ TOKEN_INC ; 
 scalar_t__ is_unary_op () ; 
 int /*<<< orphan*/ * new_expr_modify (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_expr_unary (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_token () ; 
 int /*<<< orphan*/ * parse_expr_base () ; 
 TYPE_1__ token ; 

Expr *parse_expr_unary(void) {
    if (is_unary_op()) {
        SrcPos pos = token.pos;
        TokenKind op = token.kind;
        next_token();
        if (op == TOKEN_INC || op == TOKEN_DEC) {
            return new_expr_modify(pos, op, false, parse_expr_unary());
        } else {
            return new_expr_unary(pos, op, parse_expr_unary());
        }
    } else {
        return parse_expr_base();
    }
}