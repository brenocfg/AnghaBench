#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_11__ {int /*<<< orphan*/ * ty; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 TYPE_1__* ast_ternary (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* conv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (char) ; 
 scalar_t__ is_arithtype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_comma_expr () ; 
 int /*<<< orphan*/  read_conditional_expr () ; 
 int /*<<< orphan*/ * usual_arith_conv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* wrap (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static Node *do_read_conditional_expr(Node *cond) {
    Node *then = conv(read_comma_expr());
    expect(':');
    Node *els = conv(read_conditional_expr());
    // [GNU] Omitting the middle operand is allowed.
    Type *t = then ? then->ty : cond->ty;
    Type *u = els->ty;
    // C11 6.5.15p5: if both types are arithemtic type, the result
    // type is the result of the usual arithmetic conversions.
    if (is_arithtype(t) && is_arithtype(u)) {
        Type *r = usual_arith_conv(t, u);
        return ast_ternary(r, cond, (then ? wrap(r, then) : NULL), wrap(r, els));
    }
    return ast_ternary(u, cond, then, els);
}