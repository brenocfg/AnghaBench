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
struct TYPE_3__ {size_t num_stmts; int /*<<< orphan*/ * stmts; } ;
typedef  TYPE_1__ StmtList ;

/* Variables and functions */
 int /*<<< orphan*/  gen_indent ; 
 int /*<<< orphan*/  gen_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genf (char*) ; 
 int /*<<< orphan*/  genlnf (char*) ; 

void gen_stmt_block(StmtList block) {
    genf("{");
    gen_indent++;
    for (size_t i = 0; i < block.num_stmts; i++) {
        gen_stmt(block.stmts[i]);
    }
    gen_indent--;
    genlnf("}");
}