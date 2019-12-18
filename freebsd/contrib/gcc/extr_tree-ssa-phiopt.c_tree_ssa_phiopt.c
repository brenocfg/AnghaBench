#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
typedef  TYPE_1__* edge ;
typedef  TYPE_2__* basic_block ;
struct TYPE_30__ {int /*<<< orphan*/  succs; } ;
struct TYPE_29__ {int flags; int /*<<< orphan*/  dest_idx; TYPE_2__* dest; } ;

/* Variables and functions */
 scalar_t__ COND_EXPR ; 
 int EDGE_ABNORMAL ; 
 scalar_t__ EDGE_COUNT (int /*<<< orphan*/ ) ; 
 int EDGE_FALLTHRU ; 
 TYPE_1__* EDGE_SUCC (TYPE_2__*,int) ; 
 unsigned int NUM_FIXED_BLOCKS ; 
 int /*<<< orphan*/ * PHI_ARG_DEF_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PHI_CHAIN (int /*<<< orphan*/ *) ; 
 unsigned int TODO_cleanup_cfg ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ abs_replacement (TYPE_2__*,TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__** blocks_in_phiopt_order () ; 
 scalar_t__ conditional_replacement (TYPE_2__*,TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__**) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/ * last_stmt (TYPE_2__*) ; 
 scalar_t__ minmax_replacement (TYPE_2__*,TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int n_basic_blocks ; 
 int /*<<< orphan*/ * phi_nodes (TYPE_2__*) ; 
 TYPE_2__* single_pred (TYPE_2__*) ; 
 int /*<<< orphan*/  single_pred_p (TYPE_2__*) ; 
 int /*<<< orphan*/  single_succ_p (TYPE_2__*) ; 
 scalar_t__ value_replacement (TYPE_2__*,TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int
tree_ssa_phiopt (void)
{
  basic_block bb;
  basic_block *bb_order;
  unsigned n, i;
  bool cfgchanged = false;

  /* Search every basic block for COND_EXPR we may be able to optimize.

     We walk the blocks in order that guarantees that a block with
     a single predecessor is processed before the predecessor.
     This ensures that we collapse inner ifs before visiting the
     outer ones, and also that we do not try to visit a removed
     block.  */
  bb_order = blocks_in_phiopt_order ();
  n = n_basic_blocks - NUM_FIXED_BLOCKS;

  for (i = 0; i < n; i++) 
    {
      tree cond_expr;
      tree phi;
      basic_block bb1, bb2;
      edge e1, e2;
      tree arg0, arg1;

      bb = bb_order[i];

      cond_expr = last_stmt (bb);
      /* Check to see if the last statement is a COND_EXPR.  */
      if (!cond_expr
          || TREE_CODE (cond_expr) != COND_EXPR)
        continue;

      e1 = EDGE_SUCC (bb, 0);
      bb1 = e1->dest;
      e2 = EDGE_SUCC (bb, 1);
      bb2 = e2->dest;

      /* We cannot do the optimization on abnormal edges.  */
      if ((e1->flags & EDGE_ABNORMAL) != 0
          || (e2->flags & EDGE_ABNORMAL) != 0)
       continue;

      /* If either bb1's succ or bb2 or bb2's succ is non NULL.  */
      if (EDGE_COUNT (bb1->succs) == 0
          || bb2 == NULL
	  || EDGE_COUNT (bb2->succs) == 0)
        continue;

      /* Find the bb which is the fall through to the other.  */
      if (EDGE_SUCC (bb1, 0)->dest == bb2)
        ;
      else if (EDGE_SUCC (bb2, 0)->dest == bb1)
        {
	  basic_block bb_tmp = bb1;
	  edge e_tmp = e1;
	  bb1 = bb2;
	  bb2 = bb_tmp;
	  e1 = e2;
	  e2 = e_tmp;
	}
      else
        continue;

      e1 = EDGE_SUCC (bb1, 0);

      /* Make sure that bb1 is just a fall through.  */
      if (!single_succ_p (bb1)
	  || (e1->flags & EDGE_FALLTHRU) == 0)
        continue;

      /* Also make sure that bb1 only have one predecessor and that it
	 is bb.  */
      if (!single_pred_p (bb1)
          || single_pred (bb1) != bb)
	continue;

      phi = phi_nodes (bb2);

      /* Check to make sure that there is only one PHI node.
         TODO: we could do it with more than one iff the other PHI nodes
	 have the same elements for these two edges.  */
      if (!phi || PHI_CHAIN (phi) != NULL)
	continue;

      arg0 = PHI_ARG_DEF_TREE (phi, e1->dest_idx);
      arg1 = PHI_ARG_DEF_TREE (phi, e2->dest_idx);

      /* Something is wrong if we cannot find the arguments in the PHI
	 node.  */
      gcc_assert (arg0 != NULL && arg1 != NULL);

      /* Do the replacement of conditional if it can be done.  */
      if (conditional_replacement (bb, bb1, e1, e2, phi, arg0, arg1))
	cfgchanged = true;
      else if (value_replacement (bb, bb1, e1, e2, phi, arg0, arg1))
	cfgchanged = true;
      else if (abs_replacement (bb, bb1, e1, e2, phi, arg0, arg1))
	cfgchanged = true;
      else if (minmax_replacement (bb, bb1, e1, e2, phi, arg0, arg1))
	cfgchanged = true;
    }

  free (bb_order);
  
  /* If the CFG has changed, we should cleanup the CFG. */
  return cfgchanged ? TODO_cleanup_cfg : 0;
}