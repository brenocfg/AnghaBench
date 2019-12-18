#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  StmtList ;
typedef  int /*<<< orphan*/  Stmt ;
typedef  int /*<<< orphan*/  SrcPos ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_LBRACE ; 
 int /*<<< orphan*/  TOKEN_RBRACE ; 
 int /*<<< orphan*/  buf_len (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_token_eof () ; 
 int /*<<< orphan*/  new_stmt_list (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_stmt () ; 
 TYPE_1__ token ; 

StmtList parse_stmt_block(void) {
    SrcPos pos = token.pos;
    expect_token(TOKEN_LBRACE);
    Stmt **stmts = NULL;
    while (!is_token_eof() && !is_token(TOKEN_RBRACE)) {
        buf_push(stmts, parse_stmt());
    }
    expect_token(TOKEN_RBRACE);
    return new_stmt_list(pos, stmts, buf_len(stmts));
}