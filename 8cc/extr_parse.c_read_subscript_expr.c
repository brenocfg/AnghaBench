#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Token ;
struct TYPE_11__ {TYPE_1__* ty; } ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  AST_DEREF ; 
 TYPE_2__* ast_uop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* binop (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conv (TYPE_2__*) ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/ * peek () ; 
 TYPE_2__* read_expr () ; 

__attribute__((used)) static Node *read_subscript_expr(Node *node) {
    Token *tok = peek();
    Node *sub = read_expr();
    if (!sub)
        errort(tok, "subscription expected");
    expect(']');
    Node *t = binop('+', conv(node), conv(sub));
    return ast_uop(AST_DEREF, t->ty->ptr, t);
}