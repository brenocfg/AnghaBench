#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_SAME_STMT ; 
 int /*<<< orphan*/  bsi_insert_before (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ force_gimple_operand (scalar_t__,scalar_t__*,int,scalar_t__) ; 

tree
force_gimple_operand_bsi (block_stmt_iterator *bsi, tree expr,
			  bool simple_p, tree var)
{
  tree stmts;

  expr = force_gimple_operand (expr, &stmts, simple_p, var);
  if (stmts)
    bsi_insert_before (bsi, stmts, BSI_SAME_STMT);

  return expr;
}