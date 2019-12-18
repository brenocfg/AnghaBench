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
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_LBRACKET ; 
 int /*<<< orphan*/  TOKEN_LPAREN ; 
 int /*<<< orphan*/  TOKEN_RBRACKET ; 
 int /*<<< orphan*/  TOKEN_RPAREN ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_keyword (int /*<<< orphan*/ ) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_expr_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parse_expr () ; 
 int /*<<< orphan*/  undef_keyword ; 

Expr *parse_expr_new(SrcPos pos) {
    Expr *alloc = NULL;
    if (match_token(TOKEN_LPAREN)) {
        alloc = parse_expr();
        expect_token(TOKEN_RPAREN);
    }
    Expr *len = NULL;
    if (match_token(TOKEN_LBRACKET)) {
        len = parse_expr();
        expect_token(TOKEN_RBRACKET);
    }
    Expr *arg = NULL;
    if (!match_keyword(undef_keyword)) {
        arg = parse_expr();
    }
    return new_expr_new(pos, alloc, len, arg);
}