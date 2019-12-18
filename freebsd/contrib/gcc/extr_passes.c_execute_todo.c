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

/* Variables and functions */
 int PROP_cfg ; 
 int PROP_ssa ; 
 int PROP_trees ; 
 int TDF_BLOCKS ; 
 int TDF_GRAPH ; 
 int TDF_SLIM ; 
 unsigned int TODO_cleanup_cfg ; 
 unsigned int TODO_dump_cgraph ; 
 unsigned int TODO_dump_func ; 
 unsigned int TODO_ggc_collect ; 
 unsigned int TODO_remove_unused_locals ; 
 unsigned int TODO_update_smt_usage ; 
 unsigned int TODO_update_ssa ; 
 unsigned int TODO_update_ssa_any ; 
 unsigned int TODO_verify_all ; 
 unsigned int TODO_verify_flow ; 
 unsigned int TODO_verify_loops ; 
 unsigned int TODO_verify_ssa ; 
 unsigned int TODO_verify_stmts ; 
 int /*<<< orphan*/  cleanup_tree_cfg () ; 
 int /*<<< orphan*/  cleanup_tree_cfg_loop () ; 
 int curr_properties ; 
 scalar_t__ current_function_decl ; 
 scalar_t__ current_loops ; 
 int /*<<< orphan*/  dump_cgraph (scalar_t__) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_file_name ; 
 int dump_flags ; 
 int /*<<< orphan*/  dump_function_to_file (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (unsigned int) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  ggc_collect () ; 
 scalar_t__ graph_dump_format ; 
 unsigned int last_verified ; 
 scalar_t__ need_ssa_update_p () ; 
 scalar_t__ no_graph ; 
 int /*<<< orphan*/  print_rtl (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_rtl_graph_with_bb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_rtl_slim_with_bb (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_rtl_with_bb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recalculate_used_alone () ; 
 int /*<<< orphan*/  remove_unused_locals () ; 
 int /*<<< orphan*/  update_ssa (unsigned int) ; 
 int updating_used_alone ; 
 int /*<<< orphan*/  verify_flow_info () ; 
 int /*<<< orphan*/  verify_loop_closed_ssa () ; 
 int /*<<< orphan*/  verify_ssa (int) ; 
 int /*<<< orphan*/  verify_stmts () ; 

__attribute__((used)) static void
execute_todo (unsigned int flags)
{
#if defined ENABLE_CHECKING
  if (need_ssa_update_p ())
    gcc_assert (flags & TODO_update_ssa_any);
#endif

  if (curr_properties & PROP_ssa)
    flags |= TODO_verify_ssa;
  flags &= ~last_verified;
  if (!flags)
    return;
  
  /* Always recalculate SMT usage before doing anything else.  */
  if (flags & TODO_update_smt_usage)
    recalculate_used_alone ();

  /* Always cleanup the CFG before trying to update SSA .  */
  if (flags & TODO_cleanup_cfg)
    {
      /* CFG Cleanup can cause a constant to prop into an ARRAY_REF.  */
      updating_used_alone = true;

      if (current_loops)
	cleanup_tree_cfg_loop ();
      else
	cleanup_tree_cfg ();

      /* Update the used alone after cleanup cfg.  */
      recalculate_used_alone ();

      /* When cleanup_tree_cfg merges consecutive blocks, it may
	 perform some simplistic propagation when removing single
	 valued PHI nodes.  This propagation may, in turn, cause the
	 SSA form to become out-of-date (see PR 22037).  So, even
	 if the parent pass had not scheduled an SSA update, we may
	 still need to do one.  */
      if (!(flags & TODO_update_ssa_any) && need_ssa_update_p ())
	flags |= TODO_update_ssa;
    }

  if (flags & TODO_update_ssa_any)
    {
      unsigned update_flags = flags & TODO_update_ssa_any;
      update_ssa (update_flags);
      last_verified &= ~TODO_verify_ssa;
    }

  if (flags & TODO_remove_unused_locals)
    remove_unused_locals ();

  if ((flags & TODO_dump_func)
      && dump_file && current_function_decl)
    {
      if (curr_properties & PROP_trees)
        dump_function_to_file (current_function_decl,
                               dump_file, dump_flags);
      else
	{
	  if (dump_flags & TDF_SLIM)
	    print_rtl_slim_with_bb (dump_file, get_insns (), dump_flags);
	  else if ((curr_properties & PROP_cfg) && (dump_flags & TDF_BLOCKS))
	    print_rtl_with_bb (dump_file, get_insns ());
          else
	    print_rtl (dump_file, get_insns ());

	  if (curr_properties & PROP_cfg
	      && graph_dump_format != no_graph
	      && (dump_flags & TDF_GRAPH))
	    print_rtl_graph_with_bb (dump_file_name, get_insns ());
	}

      /* Flush the file.  If verification fails, we won't be able to
	 close the file before aborting.  */
      fflush (dump_file);
    }
  if ((flags & TODO_dump_cgraph)
      && dump_file && !current_function_decl)
    {
      dump_cgraph (dump_file);
      /* Flush the file.  If verification fails, we won't be able to
	 close the file before aborting.  */
      fflush (dump_file);
    }

  if (flags & TODO_ggc_collect)
    {
      ggc_collect ();
    }

#if defined ENABLE_CHECKING
  if (flags & TODO_verify_ssa)
    verify_ssa (true);
  if (flags & TODO_verify_flow)
    verify_flow_info ();
  if (flags & TODO_verify_stmts)
    verify_stmts ();
  if (flags & TODO_verify_loops)
    verify_loop_closed_ssa ();
#endif

  last_verified = flags & TODO_verify_all;
}