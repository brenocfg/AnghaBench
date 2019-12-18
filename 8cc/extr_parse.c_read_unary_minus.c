#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  ty; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 TYPE_1__* ast_floattype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ast_inttype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* binop (char,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* conv (TYPE_1__*) ; 
 int /*<<< orphan*/  ensure_arithtype (TYPE_1__*) ; 
 scalar_t__ is_inttype (int /*<<< orphan*/ ) ; 
 TYPE_1__* read_cast_expr () ; 

__attribute__((used)) static Node *read_unary_minus() {
    Node *expr = read_cast_expr();
    ensure_arithtype(expr);
    if (is_inttype(expr->ty))
        return binop('-', conv(ast_inttype(expr->ty, 0)), conv(expr));
    return binop('-', ast_floattype(expr->ty, 0), expr);
}