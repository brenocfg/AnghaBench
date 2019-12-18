#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ kind; int /*<<< orphan*/  sval; } ;
typedef  TYPE_2__ Token ;
struct TYPE_17__ {TYPE_1__* ty; } ;
struct TYPE_15__ {scalar_t__ kind; } ;
typedef  TYPE_3__ Node ;

/* Variables and functions */
 scalar_t__ KIND_PTR ; 
 scalar_t__ TIDENT ; 
 TYPE_3__* ast_computed_goto (TYPE_3__*) ; 
 TYPE_3__* ast_goto (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errort (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (char) ; 
 TYPE_2__* get () ; 
 int /*<<< orphan*/  gotos ; 
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/  node2s (TYPE_3__*) ; 
 TYPE_2__* peek () ; 
 TYPE_3__* read_cast_expr () ; 
 int /*<<< orphan*/  tok2s (TYPE_2__*) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static Node *read_goto_stmt() {
    if (next_token('*')) {
        // [GNU] computed goto. "goto *p" jumps to the address pointed by p.
        Token *tok = peek();
        Node *expr = read_cast_expr();
        if (expr->ty->kind != KIND_PTR)
            errort(tok, "pointer expected for computed goto, but got %s", node2s(expr));
        return ast_computed_goto(expr);
    }
    Token *tok = get();
    if (!tok || tok->kind != TIDENT)
        errort(tok, "identifier expected, but got %s", tok2s(tok));
    expect(';');
    Node *r = ast_goto(tok->sval);
    vec_push(gotos, r);
    return r;
}