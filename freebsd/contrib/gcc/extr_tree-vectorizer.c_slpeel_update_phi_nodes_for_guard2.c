#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct loop {TYPE_1__* single_exit; int /*<<< orphan*/  outer; } ;
typedef  TYPE_1__* edge ;
typedef  TYPE_2__* basic_block ;
struct TYPE_18__ {int /*<<< orphan*/  preds; } ;
struct TYPE_17__ {int /*<<< orphan*/  dest_idx; TYPE_2__* src; TYPE_2__* dest; } ;

/* Variables and functions */
 int EDGE_COUNT (int /*<<< orphan*/ ) ; 
 TYPE_1__* EDGE_PRED (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* EDGE_SUCC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ PHI_ARG_DEF_FROM_EDGE (scalar_t__,TYPE_1__*) ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  PHI_RESULT (scalar_t__) ; 
 int /*<<< orphan*/  SET_PHI_ARG_DEF (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  add_bb_to_loop (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_phi_arg (scalar_t__,scalar_t__,TYPE_1__*) ; 
 scalar_t__ create_phi_node (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_current_def (scalar_t__) ; 
 scalar_t__ phi_nodes (TYPE_2__*) ; 
 int /*<<< orphan*/  phi_reverse (scalar_t__) ; 
 int /*<<< orphan*/  set_phi_nodes (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* split_edge (TYPE_1__*) ; 

__attribute__((used)) static void
slpeel_update_phi_nodes_for_guard2 (edge guard_edge, struct loop *loop,
                                    bool is_new_loop, basic_block *new_exit_bb)
{
  tree orig_phi, new_phi;
  tree update_phi, update_phi2;
  tree guard_arg, loop_arg;
  basic_block new_merge_bb = guard_edge->dest;
  edge e = EDGE_SUCC (new_merge_bb, 0);
  basic_block update_bb = e->dest;
  edge new_exit_e;
  tree orig_def, orig_def_new_name;
  tree new_name, new_name2;
  tree arg;

  /* Create new bb between loop and new_merge_bb.  */
  *new_exit_bb = split_edge (loop->single_exit);
  add_bb_to_loop (*new_exit_bb, loop->outer);

  new_exit_e = EDGE_SUCC (*new_exit_bb, 0);

  for (update_phi = phi_nodes (update_bb); update_phi; 
       update_phi = PHI_CHAIN (update_phi))
    {
      orig_phi = update_phi;
      orig_def = PHI_ARG_DEF_FROM_EDGE (orig_phi, e);
      /* This loop-closed-phi actually doesn't represent a use
         out of the loop - the phi arg is a constant.  */ 
      if (TREE_CODE (orig_def) != SSA_NAME)
        continue;
      orig_def_new_name = get_current_def (orig_def);
      arg = NULL_TREE;

      /** 1. Handle new-merge-point phis  **/

      /* 1.1. Generate new phi node in NEW_MERGE_BB:  */
      new_phi = create_phi_node (SSA_NAME_VAR (PHI_RESULT (orig_phi)),
                                 new_merge_bb);

      /* 1.2. NEW_MERGE_BB has two incoming edges: GUARD_EDGE and the exit-edge
            of LOOP. Set the two PHI args in NEW_PHI for these edges:  */
      new_name = orig_def;
      new_name2 = NULL_TREE;
      if (orig_def_new_name)
        {
          new_name = orig_def_new_name;
	  /* Some variables have both loop-entry-phis and loop-exit-phis.
	     Such variables were given yet newer names by phis placed in
	     guard_bb by slpeel_update_phi_nodes_for_guard1. I.e:
	     new_name2 = get_current_def (get_current_def (orig_name)).  */
          new_name2 = get_current_def (new_name);
        }
  
      if (is_new_loop)
        {
          guard_arg = orig_def;
          loop_arg = new_name;
        }
      else
        {
          guard_arg = new_name;
          loop_arg = orig_def;
        }
      if (new_name2)
        guard_arg = new_name2;
  
      add_phi_arg (new_phi, loop_arg, new_exit_e);
      add_phi_arg (new_phi, guard_arg, guard_edge);

      /* 1.3. Update phi in successor block.  */
      gcc_assert (PHI_ARG_DEF_FROM_EDGE (update_phi, e) == orig_def);
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


      /** 3. Handle loop-closed-ssa-form phis for first loop  **/

      /* 3.1. Find the relevant names that need an exit-phi in
	 GUARD_BB, i.e. names for which
	 slpeel_update_phi_nodes_for_guard1 had not already created a
	 phi node. This is the case for names that are used outside
	 the loop (and therefore need an exit phi) but are not updated
	 across loop iterations (and therefore don't have a
	 loop-header-phi).

	 slpeel_update_phi_nodes_for_guard1 is responsible for
	 creating loop-exit phis in GUARD_BB for names that have a
	 loop-header-phi.  When such a phi is created we also record
	 the new name in its current definition.  If this new name
	 exists, then guard_arg was set to this new name (see 1.2
	 above).  Therefore, if guard_arg is not this new name, this
	 is an indication that an exit-phi in GUARD_BB was not yet
	 created, so we take care of it here.  */
      if (guard_arg == new_name2)
	continue;
      arg = guard_arg;

      /* 3.2. Generate new phi node in GUARD_BB:  */
      new_phi = create_phi_node (SSA_NAME_VAR (PHI_RESULT (orig_phi)),
                                 guard_edge->src);

      /* 3.3. GUARD_BB has one incoming edge:  */
      gcc_assert (EDGE_COUNT (guard_edge->src->preds) == 1);
      add_phi_arg (new_phi, arg, EDGE_PRED (guard_edge->src, 0));

      /* 3.4. Update phi in successor of GUARD_BB:  */
      gcc_assert (PHI_ARG_DEF_FROM_EDGE (update_phi2, guard_edge)
                                                                == guard_arg);
      SET_PHI_ARG_DEF (update_phi2, guard_edge->dest_idx, PHI_RESULT (new_phi));
    }

  set_phi_nodes (new_merge_bb, phi_reverse (phi_nodes (new_merge_bb)));
}