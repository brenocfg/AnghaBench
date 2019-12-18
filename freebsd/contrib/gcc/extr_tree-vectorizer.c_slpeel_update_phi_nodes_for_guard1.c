#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct loop {TYPE_1__* single_exit; int /*<<< orphan*/  latch; int /*<<< orphan*/  outer; int /*<<< orphan*/  header; } ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  bitmap ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_8__ {int /*<<< orphan*/  dest_idx; int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 TYPE_1__* EDGE_SUCC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ PHI_ARG_DEF_FROM_EDGE (scalar_t__,TYPE_1__*) ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 scalar_t__ PHI_RESULT (scalar_t__) ; 
 int /*<<< orphan*/  SET_PHI_ARG_DEF (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SSA_NAME_VAR (scalar_t__) ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (scalar_t__) ; 
 int /*<<< orphan*/  add_bb_to_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_phi_arg (scalar_t__,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ create_phi_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_current_def (scalar_t__) ; 
 int /*<<< orphan*/  is_gimple_reg (int /*<<< orphan*/ ) ; 
 TYPE_1__* loop_preheader_edge (struct loop*) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phi_reverse (scalar_t__) ; 
 int /*<<< orphan*/  set_current_def (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_phi_nodes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  split_edge (TYPE_1__*) ; 
 int /*<<< orphan*/  vect_vnames_to_rename ; 

__attribute__((used)) static void
slpeel_update_phi_nodes_for_guard1 (edge guard_edge, struct loop *loop,
                                    bool is_new_loop, basic_block *new_exit_bb,
                                    bitmap *defs)
{
  tree orig_phi, new_phi;
  tree update_phi, update_phi2;
  tree guard_arg, loop_arg;
  basic_block new_merge_bb = guard_edge->dest;
  edge e = EDGE_SUCC (new_merge_bb, 0);
  basic_block update_bb = e->dest;
  basic_block orig_bb = loop->header;
  edge new_exit_e;
  tree current_new_name;
  tree name;

  /* Create new bb between loop and new_merge_bb.  */
  *new_exit_bb = split_edge (loop->single_exit);
  add_bb_to_loop (*new_exit_bb, loop->outer);

  new_exit_e = EDGE_SUCC (*new_exit_bb, 0);

  for (orig_phi = phi_nodes (orig_bb), update_phi = phi_nodes (update_bb);
       orig_phi && update_phi;
       orig_phi = PHI_CHAIN (orig_phi), update_phi = PHI_CHAIN (update_phi))
    {
      /* Virtual phi; Mark it for renaming. We actually want to call
	 mar_sym_for_renaming, but since all ssa renaming datastructures
	 are going to be freed before we get to call ssa_upate, we just
	 record this name for now in a bitmap, and will mark it for
	 renaming later.  */
      name = PHI_RESULT (orig_phi);
      if (!is_gimple_reg (SSA_NAME_VAR (name)))
        bitmap_set_bit (vect_vnames_to_rename, SSA_NAME_VERSION (name));

      /** 1. Handle new-merge-point phis  **/

      /* 1.1. Generate new phi node in NEW_MERGE_BB:  */
      new_phi = create_phi_node (SSA_NAME_VAR (PHI_RESULT (orig_phi)),
                                 new_merge_bb);

      /* 1.2. NEW_MERGE_BB has two incoming edges: GUARD_EDGE and the exit-edge
            of LOOP. Set the two phi args in NEW_PHI for these edges:  */
      loop_arg = PHI_ARG_DEF_FROM_EDGE (orig_phi, EDGE_SUCC (loop->latch, 0));
      guard_arg = PHI_ARG_DEF_FROM_EDGE (orig_phi, loop_preheader_edge (loop));

      add_phi_arg (new_phi, loop_arg, new_exit_e);
      add_phi_arg (new_phi, guard_arg, guard_edge);

      /* 1.3. Update phi in successor block.  */
      gcc_assert (PHI_ARG_DEF_FROM_EDGE (update_phi, e) == loop_arg
                  || PHI_ARG_DEF_FROM_EDGE (update_phi, e) == guard_arg);
      SET_PHI_ARG_DEF (update_phi, e->dest_idx, PHI_RESULT (new_phi));
      update_phi2 = new_phi;


      /** 2. Handle loop-closed-ssa-form phis  **/

      /* 2.1. Generate new phi node in NEW_EXIT_BB:  */
      new_phi = create_phi_node (SSA_NAME_VAR (PHI_RESULT (orig_phi)),
                                 *new_exit_bb);

      /* 2.2. NEW_EXIT_BB has one incoming edge: the exit-edge of the loop.  */
      add_phi_arg (new_phi, loop_arg, loop->single_exit);

      /* 2.3. Update phi in successor of NEW_EXIT_BB:  */
      gcc_assert (PHI_ARG_DEF_FROM_EDGE (update_phi2, new_exit_e) == loop_arg);
      SET_PHI_ARG_DEF (update_phi2, new_exit_e->dest_idx, PHI_RESULT (new_phi));

      /* 2.4. Record the newly created name with set_current_def.
         We want to find a name such that
                name = get_current_def (orig_loop_name)
         and to set its current definition as follows:
                set_current_def (name, new_phi_name)

         If LOOP is a new loop then loop_arg is already the name we're
         looking for. If LOOP is the original loop, then loop_arg is
         the orig_loop_name and the relevant name is recorded in its
         current reaching definition.  */
      if (is_new_loop)
        current_new_name = loop_arg;
      else
        {
          current_new_name = get_current_def (loop_arg);
	  /* current_def is not available only if the variable does not
	     change inside the loop, in which case we also don't care
	     about recording a current_def for it because we won't be
	     trying to create loop-exit-phis for it.  */
	  if (!current_new_name)
	    continue;
        }
      gcc_assert (get_current_def (current_new_name) == NULL_TREE);

      set_current_def (current_new_name, PHI_RESULT (new_phi));
      bitmap_set_bit (*defs, SSA_NAME_VERSION (current_new_name));
    }

  set_phi_nodes (new_merge_bb, phi_reverse (phi_nodes (new_merge_bb)));
}