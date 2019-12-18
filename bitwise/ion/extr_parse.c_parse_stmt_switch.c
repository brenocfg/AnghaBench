#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SwitchCase ;
typedef  int /*<<< orphan*/  Stmt ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_LBRACE ; 
 int /*<<< orphan*/  TOKEN_RBRACE ; 
 int /*<<< orphan*/  buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_token_eof () ; 
 int /*<<< orphan*/ * new_stmt_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parse_paren_expr () ; 
 int /*<<< orphan*/  parse_stmt_switch_case () ; 

Stmt *parse_stmt_switch(SrcPos pos) {
    Expr *expr = parse_paren_expr();
    SwitchCase *cases = NULL;
    expect_token(TOKEN_LBRACE);
    while (!is_token_eof() && !is_token(TOKEN_RBRACE)) {
        buf_push(cases, parse_stmt_switch_case());
    }
    expect_token(TOKEN_RBRACE);
    return new_stmt_switch(pos, expr, cases, buf_len(cases));
}