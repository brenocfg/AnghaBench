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
struct loops {int dummy; } ;
struct loop {scalar_t__ single_exit; int /*<<< orphan*/  outer; } ;
typedef  scalar_t__ edge ;
typedef  int /*<<< orphan*/  bitmap ;
typedef  int /*<<< orphan*/  basic_block ;
typedef  scalar_t__ LOC ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EQ_EXPR ; 
 int /*<<< orphan*/  LE_EXPR ; 
 char* LOC_FILE (scalar_t__) ; 
 int LOC_LINE (scalar_t__) ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ UNKNOWN_LOC ; 
 int /*<<< orphan*/  add_bb_to_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_update_ssa () ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 scalar_t__ find_loop_location (struct loop*) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 scalar_t__ loop_preheader_edge (struct loop*) ; 
 int /*<<< orphan*/  rename_variables_in_loop (struct loop*) ; 
 scalar_t__ slpeel_add_loop_guard (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slpeel_can_duplicate_loop_p (struct loop*,scalar_t__) ; 
 int /*<<< orphan*/  slpeel_make_loop_iterate_ntimes (struct loop*,int /*<<< orphan*/ ) ; 
 struct loop* slpeel_tree_duplicate_loop_to_edge_cfg (struct loop*,struct loops*,scalar_t__) ; 
 int /*<<< orphan*/  slpeel_update_phi_nodes_for_guard1 (scalar_t__,struct loop*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slpeel_update_phi_nodes_for_guard2 (scalar_t__,struct loop*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slpeel_update_phis_for_duplicate_loop (struct loop*,struct loop*,int) ; 
 int /*<<< orphan*/  split_edge (scalar_t__) ; 
 int /*<<< orphan*/  ssa_names_to_replace () ; 
 int /*<<< orphan*/  tree_register_cfg_hooks () ; 

struct loop*
slpeel_tree_peel_loop_to_edge (struct loop *loop, struct loops *loops, 
			       edge e, tree first_niters, 
			       tree niters, bool update_first_loop_count)
{
  struct loop *new_loop = NULL, *first_loop, *second_loop;
  edge skip_e;
  tree pre_condition;
  bitmap definitions;
  basic_block bb_before_second_loop, bb_after_second_loop;
  basic_block bb_before_first_loop;
  basic_block bb_between_loops;
  basic_block new_exit_bb;
  edge exit_e = loop->single_exit;
  LOC loop_loc;
  
  if (!slpeel_can_duplicate_loop_p (loop, e))
    return NULL;
  
  /* We have to initialize cfg_hooks. Then, when calling
   cfg_hooks->split_edge, the function tree_split_edge 
   is actually called and, when calling cfg_hooks->duplicate_block,
   the function tree_duplicate_bb is called.  */
  tree_register_cfg_hooks ();


  /* 1. Generate a copy of LOOP and put it on E (E is the entry/exit of LOOP).
        Resulting CFG would be:

        first_loop:
        do {
        } while ...

        second_loop:
        do {
        } while ...

        orig_exit_bb:
   */
  
  if (!(new_loop = slpeel_tree_duplicate_loop_to_edge_cfg (loop, loops, e)))
    {
      loop_loc = find_loop_location (loop);
      if (dump_file && (dump_flags & TDF_DETAILS))
        {
          if (loop_loc != UNKNOWN_LOC)
            fprintf (dump_file, "\n%s:%d: note: ",
                     LOC_FILE (loop_loc), LOC_LINE (loop_loc));
          fprintf (dump_file, "tree_duplicate_loop_to_edge_cfg failed.\n");
        }
      return NULL;
    }
  
  if (e == exit_e)
    {
      /* NEW_LOOP was placed after LOOP.  */
      first_loop = loop;
      second_loop = new_loop;
    }
  else
    {
      /* NEW_LOOP was placed before LOOP.  */
      first_loop = new_loop;
      second_loop = loop;
    }

  definitions = ssa_names_to_replace ();
  slpeel_update_phis_for_duplicate_loop (loop, new_loop, e == exit_e);
  rename_variables_in_loop (new_loop);


  /* 2. Add the guard that controls whether the first loop is executed.
        Resulting CFG would be:

        bb_before_first_loop:
        if (FIRST_NITERS == 0) GOTO bb_before_second_loop
                               GOTO first-loop

        first_loop:
        do {
        } while ...

        bb_before_second_loop:

        second_loop:
        do {
        } while ...

        orig_exit_bb:
   */

  bb_before_first_loop = split_edge (loop_preheader_edge (first_loop));
  add_bb_to_loop (bb_before_first_loop, first_loop->outer);
  bb_before_second_loop = split_edge (first_loop->single_exit);
  add_bb_to_loop (bb_before_second_loop, first_loop->outer);

  pre_condition =
    fold_build2 (LE_EXPR, boolean_type_node, first_niters, 
                 build_int_cst (TREE_TYPE (first_niters), 0));
  skip_e = slpeel_add_loop_guard (bb_before_first_loop, pre_condition,
                                  bb_before_second_loop, bb_before_first_loop);
  slpeel_update_phi_nodes_for_guard1 (skip_e, first_loop,
				      first_loop == new_loop,
				      &new_exit_bb, &definitions);


  /* 3. Add the guard that controls whether the second loop is executed.
        Resulting CFG would be:

        bb_before_first_loop:
        if (FIRST_NITERS == 0) GOTO bb_before_second_loop (skip first loop)
                               GOTO first-loop

        first_loop:
        do {
        } while ...

        bb_between_loops:
        if (FIRST_NITERS == NITERS) GOTO bb_after_second_loop (skip second loop)
                                    GOTO bb_before_second_loop

        bb_before_second_loop:

        second_loop:
        do {
        } while ...

        bb_after_second_loop:

        orig_exit_bb:
   */

  bb_between_loops = new_exit_bb;
  bb_after_second_loop = split_edge (second_loop->single_exit);
  add_bb_to_loop (bb_after_second_loop, second_loop->outer);

  pre_condition = 
	fold_build2 (EQ_EXPR, boolean_type_node, first_niters, niters);
  skip_e = slpeel_add_loop_guard (bb_between_loops, pre_condition,
                                  bb_after_second_loop, bb_before_first_loop);
  slpeel_update_phi_nodes_for_guard2 (skip_e, second_loop,
                                     second_loop == new_loop, &new_exit_bb);

  /* 4. Make first-loop iterate FIRST_NITERS times, if requested.
   */
  if (update_first_loop_count)
    slpeel_make_loop_iterate_ntimes (first_loop, first_niters);

  BITMAP_FREE (definitions);
  delete_update_ssa ();

  return new_loop;
}