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
struct TYPE_5__ {int /*<<< orphan*/  block; int /*<<< orphan*/ * cond; } ;
struct TYPE_6__ {TYPE_1__ while_stmt; } ;
typedef  int /*<<< orphan*/  StmtList ;
typedef  TYPE_2__ Stmt ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_DO_WHILE ; 
 TYPE_2__* new_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Stmt *new_stmt_do_while(SrcPos pos, Expr *cond, StmtList block) {
    Stmt *s = new_stmt(STMT_DO_WHILE, pos);
    s->while_stmt.cond = cond;
    s->while_stmt.block = block;
    return s;
}