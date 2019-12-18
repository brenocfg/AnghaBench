#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TokenKind ;
struct TYPE_5__ {int /*<<< orphan*/ * right; int /*<<< orphan*/ * left; int /*<<< orphan*/  op; } ;
struct TYPE_6__ {TYPE_1__ assign; } ;
typedef  TYPE_2__ Stmt ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_ASSIGN ; 
 TYPE_2__* new_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Stmt *new_stmt_assign(SrcPos pos, TokenKind op, Expr *left, Expr *right) {
    Stmt *s = new_stmt(STMT_ASSIGN, pos);
    s->assign.op = op;
    s->assign.left = left;
    s->assign.right = right;
    return s;
}