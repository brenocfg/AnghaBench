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
typedef  int /*<<< orphan*/  TokenKind ;
struct TYPE_2__ {int /*<<< orphan*/  kind; int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  Stmt ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ is_assign_op () ; 
 int /*<<< orphan*/ * new_stmt_assign (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_stmt_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_token () ; 
 int /*<<< orphan*/ * parse_expr () ; 
 int /*<<< orphan*/ * parse_init_stmt (int /*<<< orphan*/ *) ; 
 TYPE_1__ token ; 

Stmt *parse_simple_stmt(void) {
    SrcPos pos = token.pos;
    Expr *expr = parse_expr();
    Stmt *stmt = parse_init_stmt(expr);
    if (!stmt) {
        if (is_assign_op()) {
            TokenKind op = token.kind;
            next_token();
            stmt = new_stmt_assign(pos, op, expr, parse_expr());
        } else {
            stmt = new_stmt_expr(pos, expr);
        }
    }
    return stmt;
}