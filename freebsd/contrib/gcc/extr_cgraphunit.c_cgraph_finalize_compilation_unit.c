#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct cgraph_varpool_node {int dummy; } ;
struct TYPE_3__ {scalar_t__ finalized; } ;
struct cgraph_node {scalar_t__ analyzed; TYPE_1__ local; struct cgraph_node* next_needed; scalar_t__ reachable; struct cgraph_node* next; int /*<<< orphan*/  decl; scalar_t__ needed; struct cgraph_edge* callees; } ;
struct cgraph_edge {TYPE_2__* callee; struct cgraph_edge* next_callee; } ;
struct TYPE_4__ {int /*<<< orphan*/  reachable; } ;

/* Variables and functions */
 int DECL_SAVED_TREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TV_CGRAPH ; 
 int /*<<< orphan*/  cgraph_analyze_function (struct cgraph_node*) ; 
 int /*<<< orphan*/  cgraph_assemble_pending_functions () ; 
 scalar_t__ cgraph_dump_file ; 
 int /*<<< orphan*/  cgraph_mark_reachable_node (TYPE_2__*) ; 
 char* cgraph_node_name (struct cgraph_node*) ; 
 struct cgraph_node* cgraph_nodes ; 
 struct cgraph_node* cgraph_nodes_queue ; 
 int /*<<< orphan*/  cgraph_output_pending_asms () ; 
 int /*<<< orphan*/  cgraph_remove_node (struct cgraph_node*) ; 
 int /*<<< orphan*/  cgraph_reset_node (struct cgraph_node*) ; 
 int /*<<< orphan*/  cgraph_varpool_analyze_pending_decls () ; 
 struct cgraph_varpool_node* cgraph_varpool_nodes ; 
 int /*<<< orphan*/  cgraph_varpool_output_debug_info () ; 
 int /*<<< orphan*/  dump_cgraph (scalar_t__) ; 
 scalar_t__ errorcount ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/  finish_aliases_1 () ; 
 int /*<<< orphan*/  flag_unit_at_a_time ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  ggc_collect () ; 
 int /*<<< orphan*/  process_function_and_variable_attributes (struct cgraph_node*,struct cgraph_varpool_node*) ; 
 int /*<<< orphan*/  quiet_flag ; 
 scalar_t__ sorrycount ; 
 scalar_t__ stderr ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

void
cgraph_finalize_compilation_unit (void)
{
  struct cgraph_node *node, *next;
  /* Keep track of already processed nodes when called multiple times for
     intermodule optimization.  */
  static struct cgraph_node *first_analyzed;
  struct cgraph_node *first_processed = first_analyzed;
  static struct cgraph_varpool_node *first_analyzed_var;

  if (errorcount || sorrycount)
    return;

  finish_aliases_1 ();

  if (!flag_unit_at_a_time)
    {
      cgraph_output_pending_asms ();
      cgraph_assemble_pending_functions ();
      cgraph_varpool_output_debug_info ();
      return;
    }

  if (!quiet_flag)
    {
      fprintf (stderr, "\nAnalyzing compilation unit");
      fflush (stderr);
    }

  timevar_push (TV_CGRAPH);
  process_function_and_variable_attributes (first_processed,
					    first_analyzed_var);
  first_processed = cgraph_nodes;
  first_analyzed_var = cgraph_varpool_nodes;
  cgraph_varpool_analyze_pending_decls ();
  if (cgraph_dump_file)
    {
      fprintf (cgraph_dump_file, "Initial entry points:");
      for (node = cgraph_nodes; node != first_analyzed; node = node->next)
	if (node->needed && DECL_SAVED_TREE (node->decl))
	  fprintf (cgraph_dump_file, " %s", cgraph_node_name (node));
      fprintf (cgraph_dump_file, "\n");
    }

  /* Propagate reachability flag and lower representation of all reachable
     functions.  In the future, lowering will introduce new functions and
     new entry points on the way (by template instantiation and virtual
     method table generation for instance).  */
  while (cgraph_nodes_queue)
    {
      struct cgraph_edge *edge;
      tree decl = cgraph_nodes_queue->decl;

      node = cgraph_nodes_queue;
      cgraph_nodes_queue = cgraph_nodes_queue->next_needed;
      node->next_needed = NULL;

      /* ??? It is possible to create extern inline function and later using
	 weak alias attribute to kill its body. See
	 gcc.c-torture/compile/20011119-1.c  */
      if (!DECL_SAVED_TREE (decl))
	{
	  cgraph_reset_node (node);
	  continue;
	}

      gcc_assert (!node->analyzed && node->reachable);
      gcc_assert (DECL_SAVED_TREE (decl));

      cgraph_analyze_function (node);

      for (edge = node->callees; edge; edge = edge->next_callee)
	if (!edge->callee->reachable)
	  cgraph_mark_reachable_node (edge->callee);

      /* We finalize local static variables during constructing callgraph
         edges.  Process their attributes too.  */
      process_function_and_variable_attributes (first_processed,
						first_analyzed_var);
      first_processed = cgraph_nodes;
      first_analyzed_var = cgraph_varpool_nodes;
      cgraph_varpool_analyze_pending_decls ();
    }

  /* Collect entry points to the unit.  */
  if (cgraph_dump_file)
    {
      fprintf (cgraph_dump_file, "Unit entry points:");
      for (node = cgraph_nodes; node != first_analyzed; node = node->next)
	if (node->needed && DECL_SAVED_TREE (node->decl))
	  fprintf (cgraph_dump_file, " %s", cgraph_node_name (node));
      fprintf (cgraph_dump_file, "\n\nInitial ");
      dump_cgraph (cgraph_dump_file);
    }

  if (cgraph_dump_file)
    fprintf (cgraph_dump_file, "\nReclaiming functions:");

  for (node = cgraph_nodes; node != first_analyzed; node = next)
    {
      tree decl = node->decl;
      next = node->next;

      if (node->local.finalized && !DECL_SAVED_TREE (decl))
	cgraph_reset_node (node);

      if (!node->reachable && DECL_SAVED_TREE (decl))
	{
	  if (cgraph_dump_file)
	    fprintf (cgraph_dump_file, " %s", cgraph_node_name (node));
	  cgraph_remove_node (node);
	  continue;
	}
      else
	node->next_needed = NULL;
      gcc_assert (!node->local.finalized || DECL_SAVED_TREE (decl));
      gcc_assert (node->analyzed == node->local.finalized);
    }
  if (cgraph_dump_file)
    {
      fprintf (cgraph_dump_file, "\n\nReclaimed ");
      dump_cgraph (cgraph_dump_file);
    }
  first_analyzed = cgraph_nodes;
  ggc_collect ();
  timevar_pop (TV_CGRAPH);
}