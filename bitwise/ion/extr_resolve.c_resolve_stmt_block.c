#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_3__ {size_t num_stmts; int /*<<< orphan*/ * stmts; } ;
typedef  int /*<<< orphan*/  Sym ;
typedef  TYPE_1__ StmtList ;
typedef  int /*<<< orphan*/  StmtCtx ;

/* Variables and functions */
 scalar_t__ resolve_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sym_enter () ; 
 int /*<<< orphan*/  sym_leave (int /*<<< orphan*/ *) ; 

bool resolve_stmt_block(StmtList block, Type *ret_type, StmtCtx ctx) {
    Sym *scope = sym_enter();
    bool returns = false;
    for (size_t i = 0; i < block.num_stmts; i++) {
        returns = resolve_stmt(block.stmts[i], ret_type, ctx) || returns;
    }
    sym_leave(scope);
    return returns;
}