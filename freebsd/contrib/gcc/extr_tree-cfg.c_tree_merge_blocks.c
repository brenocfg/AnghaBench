#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree_stmt_iterator ;
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  TYPE_1__* basic_block ;
struct TYPE_14__ {int flags; } ;
struct TYPE_13__ {int index; scalar_t__ loop_father; int /*<<< orphan*/ * stmt_list; } ;
typedef  scalar_t__ SSA_NAME_DEF_STMT ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_NEW_STMT ; 
 int EDGE_FALLTHRU ; 
 scalar_t__ FORCED_LABEL (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_EXPR ; 
 int /*<<< orphan*/  LABEL_EXPR_LABEL (scalar_t__) ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ PHI_ARG_DEF (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PHI_RESULT (scalar_t__) ; 
 int /*<<< orphan*/  SET_PHI_RESULT (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TSI_NEW_STMT ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_after (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_before (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (TYPE_1__*) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bsi_start (TYPE_1__*) ; 
 scalar_t__ bsi_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  change_bb_for_stmt (scalar_t__,TYPE_1__*) ; 
 scalar_t__ current_loops ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int is_gimple_reg (scalar_t__) ; 
 int /*<<< orphan*/  last_stmt (TYPE_1__*) ; 
 int may_propagate_copy (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  move_block_after (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ phi_nodes (TYPE_1__*) ; 
 int /*<<< orphan*/  remove_phi_node (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replace_uses_by (scalar_t__,scalar_t__) ; 
 TYPE_4__* single_succ_edge (TYPE_1__*) ; 
 int /*<<< orphan*/  stmt_ends_bb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_last (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_link_after (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
tree_merge_blocks (basic_block a, basic_block b)
{
  block_stmt_iterator bsi;
  tree_stmt_iterator last;
  tree phi;

  if (dump_file)
    fprintf (dump_file, "Merging blocks %d and %d\n", a->index, b->index);

  /* Remove all single-valued PHI nodes from block B of the form
     V_i = PHI <V_j> by propagating V_j to all the uses of V_i.  */
  bsi = bsi_last (a);
  for (phi = phi_nodes (b); phi; phi = phi_nodes (b))
    {
      tree def = PHI_RESULT (phi), use = PHI_ARG_DEF (phi, 0);
      tree copy;
      bool may_replace_uses = may_propagate_copy (def, use);

      /* In case we have loops to care about, do not propagate arguments of
	 loop closed ssa phi nodes.  */
      if (current_loops
	  && is_gimple_reg (def)
	  && TREE_CODE (use) == SSA_NAME
	  && a->loop_father != b->loop_father)
	may_replace_uses = false;

      if (!may_replace_uses)
	{
	  gcc_assert (is_gimple_reg (def));

	  /* Note that just emitting the copies is fine -- there is no problem
	     with ordering of phi nodes.  This is because A is the single
	     predecessor of B, therefore results of the phi nodes cannot
	     appear as arguments of the phi nodes.  */
	  copy = build2 (MODIFY_EXPR, void_type_node, def, use);
	  bsi_insert_after (&bsi, copy, BSI_NEW_STMT);
	  SET_PHI_RESULT (phi, NULL_TREE);
	  SSA_NAME_DEF_STMT (def) = copy;
	}
      else
	replace_uses_by (def, use);

      remove_phi_node (phi, NULL);
    }

  /* Ensure that B follows A.  */
  move_block_after (b, a);

  gcc_assert (single_succ_edge (a)->flags & EDGE_FALLTHRU);
  gcc_assert (!last_stmt (a) || !stmt_ends_bb_p (last_stmt (a)));

  /* Remove labels from B and set bb_for_stmt to A for other statements.  */
  for (bsi = bsi_start (b); !bsi_end_p (bsi);)
    {
      if (TREE_CODE (bsi_stmt (bsi)) == LABEL_EXPR)
	{
	  tree label = bsi_stmt (bsi);

	  bsi_remove (&bsi, false);
	  /* Now that we can thread computed gotos, we might have
	     a situation where we have a forced label in block B
	     However, the label at the start of block B might still be
	     used in other ways (think about the runtime checking for
	     Fortran assigned gotos).  So we can not just delete the
	     label.  Instead we move the label to the start of block A.  */
	  if (FORCED_LABEL (LABEL_EXPR_LABEL (label)))
	    {
	      block_stmt_iterator dest_bsi = bsi_start (a);
	      bsi_insert_before (&dest_bsi, label, BSI_NEW_STMT);
	    }
	}
      else
	{
	  change_bb_for_stmt (bsi_stmt (bsi), a);
	  bsi_next (&bsi);
	}
    }

  /* Merge the chains.  */
  last = tsi_last (a->stmt_list);
  tsi_link_after (&last, b->stmt_list, TSI_NEW_STMT);
  b->stmt_list = NULL;
}