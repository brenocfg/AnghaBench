#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  pos; } ;
struct TYPE_17__ {int /*<<< orphan*/  notes; } ;
typedef  TYPE_1__ Stmt ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Notes ;
typedef  int /*<<< orphan*/  Note ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_COLON ; 
 int /*<<< orphan*/  TOKEN_LBRACE ; 
 int /*<<< orphan*/  TOKEN_POUND ; 
 int /*<<< orphan*/  TOKEN_SEMICOLON ; 
 int /*<<< orphan*/  break_keyword ; 
 int /*<<< orphan*/  continue_keyword ; 
 int /*<<< orphan*/  do_keyword ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_keyword ; 
 int /*<<< orphan*/  goto_keyword ; 
 int /*<<< orphan*/  if_keyword ; 
 scalar_t__ is_token (int /*<<< orphan*/ ) ; 
 scalar_t__ match_keyword (int /*<<< orphan*/ ) ; 
 scalar_t__ match_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* new_stmt_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* new_stmt_break (int /*<<< orphan*/ ) ; 
 TYPE_1__* new_stmt_continue (int /*<<< orphan*/ ) ; 
 TYPE_1__* new_stmt_goto (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* new_stmt_label (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* new_stmt_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* new_stmt_return (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parse_expr () ; 
 int /*<<< orphan*/  parse_name () ; 
 int /*<<< orphan*/  parse_note () ; 
 int /*<<< orphan*/  parse_notes () ; 
 TYPE_1__* parse_simple_stmt () ; 
 int /*<<< orphan*/  parse_stmt_block () ; 
 TYPE_1__* parse_stmt_do_while (int /*<<< orphan*/ ) ; 
 TYPE_1__* parse_stmt_for (int /*<<< orphan*/ ) ; 
 TYPE_1__* parse_stmt_if (int /*<<< orphan*/ ) ; 
 TYPE_1__* parse_stmt_switch (int /*<<< orphan*/ ) ; 
 TYPE_1__* parse_stmt_while (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_keyword ; 
 int /*<<< orphan*/  switch_keyword ; 
 TYPE_2__ token ; 
 int /*<<< orphan*/  while_keyword ; 

Stmt *parse_stmt(void) {
    Notes notes = parse_notes();
    SrcPos pos = token.pos;
    Stmt *stmt = NULL;
    if (match_keyword(if_keyword)) {
        stmt = parse_stmt_if(pos);
    } else if (match_keyword(while_keyword)) {
        stmt = parse_stmt_while(pos);
    } else if (match_keyword(do_keyword)) {
        stmt = parse_stmt_do_while(pos);
    } else if (match_keyword(for_keyword)) {
        stmt = parse_stmt_for(pos);
    } else if (match_keyword(switch_keyword)) {
        stmt = parse_stmt_switch(pos);
    } else if (is_token(TOKEN_LBRACE)) {
        stmt = new_stmt_block(pos, parse_stmt_block());
    } else if (match_keyword(break_keyword)) {
        expect_token(TOKEN_SEMICOLON);
        stmt = new_stmt_break(pos);
    } else if (match_keyword(continue_keyword)) {
        expect_token(TOKEN_SEMICOLON);
        stmt = new_stmt_continue(pos);
    } else if (match_keyword(return_keyword)) {
        Expr *expr = NULL;
        if (!is_token(TOKEN_SEMICOLON)) {
            expr = parse_expr();
        }
        expect_token(TOKEN_SEMICOLON);
        stmt = new_stmt_return(pos, expr);
    } else if (match_token(TOKEN_POUND)) {
        Note note = parse_note();
        expect_token(TOKEN_SEMICOLON);
        stmt = new_stmt_note(pos, note);
    } else if (match_token(TOKEN_COLON)) {
        stmt = new_stmt_label(pos, parse_name());
    } else if (match_keyword(goto_keyword)) {
        stmt = new_stmt_goto(pos, parse_name());
        expect_token(TOKEN_SEMICOLON);
    } else {
        stmt = parse_simple_stmt();
        expect_token(TOKEN_SEMICOLON);
    }
    stmt->notes = notes;
    return stmt;
}