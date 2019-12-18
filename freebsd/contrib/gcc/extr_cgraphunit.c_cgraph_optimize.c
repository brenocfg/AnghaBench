#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ inlined_to; } ;
struct cgraph_node {int /*<<< orphan*/  decl; TYPE_1__ global; scalar_t__ analyzed; struct cgraph_node* next; } ;

/* Variables and functions */
 scalar_t__ DECL_SAVED_TREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TV_CGRAPHOPT ; 
 scalar_t__ cgraph_dump_file ; 
 int /*<<< orphan*/  cgraph_expand_all_functions () ; 
 int /*<<< orphan*/  cgraph_function_and_variable_visibility () ; 
 int cgraph_global_info_ready ; 
 int /*<<< orphan*/  cgraph_increase_alignment () ; 
 int /*<<< orphan*/  cgraph_mark_functions_to_output () ; 
 struct cgraph_node* cgraph_nodes ; 
 int /*<<< orphan*/  cgraph_output_in_order () ; 
 int /*<<< orphan*/  cgraph_output_pending_asms () ; 
 int /*<<< orphan*/  cgraph_remove_unreachable_nodes (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_varpool_analyze_pending_decls () ; 
 int /*<<< orphan*/  cgraph_varpool_assemble_pending_decls () ; 
 int /*<<< orphan*/  cgraph_varpool_output_debug_info () ; 
 int /*<<< orphan*/  cgraph_varpool_remove_unreferenced_decls () ; 
 int /*<<< orphan*/  dump_cgraph (scalar_t__) ; 
 int /*<<< orphan*/  dump_cgraph_node (scalar_t__,struct cgraph_node*) ; 
 int /*<<< orphan*/  dump_file ; 
 int /*<<< orphan*/  dump_varpool (scalar_t__) ; 
 scalar_t__ errorcount ; 
 int /*<<< orphan*/  flag_toplevel_reorder ; 
 scalar_t__ flag_unit_at_a_time ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  internal_error (char*) ; 
 int /*<<< orphan*/  ipa_passes () ; 
 int /*<<< orphan*/  quiet_flag ; 
 scalar_t__ sorrycount ; 
 scalar_t__ stderr ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_cgraph () ; 

void
cgraph_optimize (void)
{
  if (errorcount || sorrycount)
    return;

#ifdef ENABLE_CHECKING
  verify_cgraph ();
#endif
  if (!flag_unit_at_a_time)
    {
      cgraph_output_pending_asms ();
      cgraph_varpool_assemble_pending_decls ();
      cgraph_varpool_output_debug_info ();
      return;
    }

  /* Frontend may output common variables after the unit has been finalized.
     It is safe to deal with them here as they are always zero initialized.  */
  cgraph_varpool_analyze_pending_decls ();

  timevar_push (TV_CGRAPHOPT);
  if (!quiet_flag)
    fprintf (stderr, "Performing interprocedural optimizations\n");

  cgraph_function_and_variable_visibility ();
  if (cgraph_dump_file)
    {
      fprintf (cgraph_dump_file, "Marked ");
      dump_cgraph (cgraph_dump_file);
    }
    
  /* Don't run the IPA passes if there was any error or sorry messages.  */
  if (errorcount == 0 && sorrycount == 0)
    ipa_passes ();

  /* This pass remove bodies of extern inline functions we never inlined.
     Do this later so other IPA passes see what is really going on.  */
  cgraph_remove_unreachable_nodes (false, dump_file);
  cgraph_increase_alignment ();
  cgraph_global_info_ready = true;
  if (cgraph_dump_file)
    {
      fprintf (cgraph_dump_file, "Optimized ");
      dump_cgraph (cgraph_dump_file);
      dump_varpool (cgraph_dump_file);
    }
  timevar_pop (TV_CGRAPHOPT);

  /* Output everything.  */
  if (!quiet_flag)
    fprintf (stderr, "Assembling functions:\n");
#ifdef ENABLE_CHECKING
  verify_cgraph ();
#endif

  cgraph_mark_functions_to_output ();

  if (!flag_toplevel_reorder)
    cgraph_output_in_order ();
  else
    {
      cgraph_output_pending_asms ();

      cgraph_expand_all_functions ();
      cgraph_varpool_remove_unreferenced_decls ();

      cgraph_varpool_assemble_pending_decls ();
      cgraph_varpool_output_debug_info ();
    }

  if (cgraph_dump_file)
    {
      fprintf (cgraph_dump_file, "\nFinal ");
      dump_cgraph (cgraph_dump_file);
    }
#ifdef ENABLE_CHECKING
  verify_cgraph ();
  /* Double check that all inline clones are gone and that all
     function bodies have been released from memory.  */
  if (flag_unit_at_a_time
      && !(sorrycount || errorcount))
    {
      struct cgraph_node *node;
      bool error_found = false;

      for (node = cgraph_nodes; node; node = node->next)
	if (node->analyzed
	    && (node->global.inlined_to
		|| DECL_SAVED_TREE (node->decl)))
	  {
	    error_found = true;
	    dump_cgraph_node (stderr, node);
	  }
      if (error_found)
	internal_error ("nodes with no released memory found");
    }
#endif
}