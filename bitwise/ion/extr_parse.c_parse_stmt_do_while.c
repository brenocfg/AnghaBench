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
typedef  int /*<<< orphan*/  StmtList ;
typedef  int /*<<< orphan*/  Stmt ;
typedef  int /*<<< orphan*/  SrcPos ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_SEMICOLON ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error_here (char*) ; 
 int /*<<< orphan*/  match_keyword (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * new_stmt_do_while (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_paren_expr () ; 
 int /*<<< orphan*/  parse_stmt_block () ; 
 int /*<<< orphan*/  while_keyword ; 

Stmt *parse_stmt_do_while(SrcPos pos) {
    StmtList block = parse_stmt_block();
    if (!match_keyword(while_keyword)) {
        fatal_error_here("Expected 'while' after 'do' block");
        return NULL;
    }
    Stmt *stmt = new_stmt_do_while(pos, parse_paren_expr(), block);
    expect_token(TOKEN_SEMICOLON);
    return stmt;
}