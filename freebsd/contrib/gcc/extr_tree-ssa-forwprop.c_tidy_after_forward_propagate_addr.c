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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bb_for_stmt (int /*<<< orphan*/ ) ; 
 int cfg_changed ; 
 int /*<<< orphan*/  mark_new_vars_to_rename (int /*<<< orphan*/ ) ; 
 scalar_t__ maybe_clean_or_replace_eh_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recompute_tree_invariant_for_addr_expr (int /*<<< orphan*/ ) ; 
 scalar_t__ tree_purge_dead_eh_edges (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tidy_after_forward_propagate_addr (tree stmt)
{
  /* We may have turned a trapping insn into a non-trapping insn.  */
  if (maybe_clean_or_replace_eh_stmt (stmt, stmt)
      && tree_purge_dead_eh_edges (bb_for_stmt (stmt)))
    cfg_changed = true;

  if (TREE_CODE (TREE_OPERAND (stmt, 1)) == ADDR_EXPR)
     recompute_tree_invariant_for_addr_expr (TREE_OPERAND (stmt, 1));

  mark_new_vars_to_rename (stmt);
}