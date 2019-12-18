#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  block; TYPE_2__* next; int /*<<< orphan*/ * cond; TYPE_2__* init; } ;
struct TYPE_8__ {TYPE_1__ for_stmt; } ;
typedef  int /*<<< orphan*/  StmtList ;
typedef  TYPE_2__ Stmt ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_FOR ; 
 TYPE_2__* new_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Stmt *new_stmt_for(SrcPos pos, Stmt *init, Expr *cond, Stmt *next, StmtList block) {
    Stmt *s = new_stmt(STMT_FOR, pos);
    s->for_stmt.init = init;
    s->for_stmt.cond = cond;
    s->for_stmt.next = next;
    s->for_stmt.block = block;
    return s;
}