#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  TYPE_2__* basic_block ;
struct TYPE_17__ {int flags; } ;
struct TYPE_16__ {TYPE_1__* loop_father; } ;
struct TYPE_15__ {TYPE_2__* latch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ARTIFICIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NONLOCAL (int /*<<< orphan*/ ) ; 
 int EDGE_ABNORMAL ; 
 TYPE_2__* EXIT_BLOCK_PTR ; 
 scalar_t__ LABEL_EXPR ; 
 int /*<<< orphan*/  LABEL_EXPR_LABEL (scalar_t__) ; 
 int /*<<< orphan*/  PHI_ARG_DEF (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  PHI_RESULT (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (TYPE_2__*) ; 
 scalar_t__ bsi_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ current_loops ; 
 int /*<<< orphan*/  is_gimple_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ last_stmt (TYPE_2__*) ; 
 int /*<<< orphan*/  may_propagate_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ need_ssa_update_p () ; 
 scalar_t__ phi_nodes (TYPE_2__*) ; 
 int /*<<< orphan*/  single_pred_p (TYPE_2__*) ; 
 TYPE_2__* single_succ (TYPE_2__*) ; 
 TYPE_6__* single_succ_edge (TYPE_2__*) ; 
 int /*<<< orphan*/  single_succ_p (TYPE_2__*) ; 
 scalar_t__ stmt_ends_bb_p (scalar_t__) ; 

__attribute__((used)) static bool
tree_can_merge_blocks_p (basic_block a, basic_block b)
{
  tree stmt;
  block_stmt_iterator bsi;
  tree phi;

  if (!single_succ_p (a))
    return false;

  if (single_succ_edge (a)->flags & EDGE_ABNORMAL)
    return false;

  if (single_succ (a) != b)
    return false;

  if (!single_pred_p (b))
    return false;

  if (b == EXIT_BLOCK_PTR)
    return false;

  /* If A ends by a statement causing exceptions or something similar, we
     cannot merge the blocks.  */
  stmt = last_stmt (a);
  if (stmt && stmt_ends_bb_p (stmt))
    return false;

  /* Do not allow a block with only a non-local label to be merged.  */
  if (stmt && TREE_CODE (stmt) == LABEL_EXPR
      && DECL_NONLOCAL (LABEL_EXPR_LABEL (stmt)))
    return false;

  /* It must be possible to eliminate all phi nodes in B.  If ssa form
     is not up-to-date, we cannot eliminate any phis.  */
  phi = phi_nodes (b);
  if (phi)
    {
      if (need_ssa_update_p ())
	return false;

      for (; phi; phi = PHI_CHAIN (phi))
	if (!is_gimple_reg (PHI_RESULT (phi))
	    && !may_propagate_copy (PHI_RESULT (phi), PHI_ARG_DEF (phi, 0)))
	  return false;
    }

  /* Do not remove user labels.  */
  for (bsi = bsi_start (b); !bsi_end_p (bsi); bsi_next (&bsi))
    {
      stmt = bsi_stmt (bsi);
      if (TREE_CODE (stmt) != LABEL_EXPR)
	break;
      if (!DECL_ARTIFICIAL (LABEL_EXPR_LABEL (stmt)))
	return false;
    }

  /* Protect the loop latches.  */
  if (current_loops
      && b->loop_father->latch == b)
    return false;

  return true;
}