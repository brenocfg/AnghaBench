#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Token ;
struct TYPE_9__ {int /*<<< orphan*/  ty; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 TYPE_1__* ast_uop (char,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* conv (TYPE_1__*) ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_inttype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node2s (TYPE_1__*) ; 
 TYPE_1__* read_cast_expr () ; 

__attribute__((used)) static Node *read_unary_bitnot(Token *tok) {
    Node *expr = read_cast_expr();
    expr = conv(expr);
    if (!is_inttype(expr->ty))
        errort(tok, "invalid use of ~: %s", node2s(expr));
    return ast_uop('~', expr->ty, expr);
}