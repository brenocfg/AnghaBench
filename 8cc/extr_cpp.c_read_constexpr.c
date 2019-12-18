#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ TEOF ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int eval_intexpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* lex () ; 
 int /*<<< orphan*/ * read_expr () ; 
 int /*<<< orphan*/  read_intexpr_line () ; 
 int /*<<< orphan*/  tok2s (TYPE_1__*) ; 
 int /*<<< orphan*/  token_buffer_stash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  token_buffer_unstash () ; 
 int /*<<< orphan*/  vec_reverse (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool read_constexpr() {
    token_buffer_stash(vec_reverse(read_intexpr_line()));
    Node *expr = read_expr();
    Token *tok = lex();
    if (tok->kind != TEOF)
        errort(tok, "stray token: %s", tok2s(tok));
    token_buffer_unstash();
    return eval_intexpr(expr, NULL);
}