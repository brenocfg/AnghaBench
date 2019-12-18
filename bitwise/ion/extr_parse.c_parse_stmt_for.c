#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Stmt ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ STMT_INIT ; 
 int /*<<< orphan*/  TOKEN_LBRACE ; 
 int /*<<< orphan*/  TOKEN_LPAREN ; 
 int /*<<< orphan*/  TOKEN_RPAREN ; 
 int /*<<< orphan*/  TOKEN_SEMICOLON ; 
 int /*<<< orphan*/  error_here (char*) ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_token (int /*<<< orphan*/ ) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* new_stmt_for (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parse_expr () ; 
 TYPE_1__* parse_simple_stmt () ; 
 int /*<<< orphan*/  parse_stmt_block () ; 

Stmt *parse_stmt_for(SrcPos pos) {
    Stmt *init = NULL;
    Expr *cond = NULL;
    Stmt *next = NULL;
    if (!is_token(TOKEN_LBRACE)) {
        expect_token(TOKEN_LPAREN);
        if (!is_token(TOKEN_SEMICOLON)) {
            init = parse_simple_stmt();
        }
        if (match_token(TOKEN_SEMICOLON)) {
            if (!is_token(TOKEN_SEMICOLON)) {
                cond = parse_expr();
            }
            if (match_token(TOKEN_SEMICOLON)) {
                if (!is_token(TOKEN_RPAREN)) {
                    next = parse_simple_stmt();
                    if (next->kind == STMT_INIT) {
                        error_here("Init statements not allowed in for-statement's next clause");
                    }
                }
            }
        }
        expect_token(TOKEN_RPAREN);
    }
    return new_stmt_for(pos, init, cond, next, parse_stmt_block());
}