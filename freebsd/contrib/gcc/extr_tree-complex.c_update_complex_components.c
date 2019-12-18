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
 int /*<<< orphan*/  BSI_CONTINUE_LINKING ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_after (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ set_component_ssa_name (scalar_t__,int,scalar_t__) ; 

__attribute__((used)) static void
update_complex_components (block_stmt_iterator *bsi, tree stmt, tree r, tree i)
{
  tree lhs = TREE_OPERAND (stmt, 0);
  tree list;

  list = set_component_ssa_name (lhs, false, r);
  if (list)
    bsi_insert_after (bsi, list, BSI_CONTINUE_LINKING);

  list = set_component_ssa_name (lhs, true, i);
  if (list)
    bsi_insert_after (bsi, list, BSI_CONTINUE_LINKING);
}