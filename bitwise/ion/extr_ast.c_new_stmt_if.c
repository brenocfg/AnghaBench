#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t num_elseifs; void* else_block; int /*<<< orphan*/  elseifs; void* then_block; int /*<<< orphan*/ * cond; TYPE_2__* init; } ;
struct TYPE_7__ {TYPE_1__ if_stmt; } ;
typedef  void* StmtList ;
typedef  TYPE_2__ Stmt ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  ElseIf ;

/* Variables and functions */
 int /*<<< orphan*/  AST_DUP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STMT_IF ; 
 TYPE_2__* new_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Stmt *new_stmt_if(SrcPos pos, Stmt *init, Expr *cond, StmtList then_block, ElseIf *elseifs, size_t num_elseifs, StmtList else_block) {
    Stmt *s = new_stmt(STMT_IF, pos);
    s->if_stmt.init = init;
    s->if_stmt.cond = cond;
    s->if_stmt.then_block = then_block;
    s->if_stmt.elseifs = AST_DUP(elseifs);
    s->if_stmt.num_elseifs = num_elseifs;
    s->if_stmt.else_block = else_block;
    return s;
}