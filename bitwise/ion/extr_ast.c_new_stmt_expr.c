#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * expr; } ;
typedef  TYPE_1__ Stmt ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_EXPR ; 
 TYPE_1__* new_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Stmt *new_stmt_expr(SrcPos pos, Expr *expr) {
    Stmt *s = new_stmt(STMT_EXPR, pos);
    s->expr = expr;
    return s;
}