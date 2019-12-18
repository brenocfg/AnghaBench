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
struct cgraph_varpool_node {scalar_t__ force_output; scalar_t__ finalized; scalar_t__ needed; struct cgraph_varpool_node* next_needed; int /*<<< orphan*/  decl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_ASSEMBLER_NAME_SET_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_RTL_SET_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_SYMBOL_REFERENCED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_varpool_analyze_pending_decls () ; 
 int /*<<< orphan*/  cgraph_varpool_mark_needed_node (struct cgraph_varpool_node*) ; 
 struct cgraph_varpool_node* cgraph_varpool_nodes_queue ; 
 int /*<<< orphan*/  cgraph_varpool_reset_queue () ; 
 scalar_t__ decide_is_variable_needed (struct cgraph_varpool_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ errorcount ; 
 int /*<<< orphan*/  finish_aliases_1 () ; 
 scalar_t__ sorrycount ; 

__attribute__((used)) static void
cgraph_varpool_remove_unreferenced_decls (void)
{
  struct cgraph_varpool_node *next, *node = cgraph_varpool_nodes_queue;

  cgraph_varpool_reset_queue ();

  if (errorcount || sorrycount)
    return;

  while (node)
    {
      tree decl = node->decl;
      next = node->next_needed;
      node->needed = 0;

      if (node->finalized
	  && ((DECL_ASSEMBLER_NAME_SET_P (decl)
	       && TREE_SYMBOL_REFERENCED (DECL_ASSEMBLER_NAME (decl)))
	      || node->force_output
	      || decide_is_variable_needed (node, decl)
	      /* ??? Cgraph does not yet rule the world with an iron hand,
		 and does not control the emission of debug information.
		 After a variable has its DECL_RTL set, we must assume that
		 it may be referenced by the debug information, and we can
		 no longer elide it.  */
	      || DECL_RTL_SET_P (decl)))
	cgraph_varpool_mark_needed_node (node);

      node = next;
    }
  /* Make sure we mark alias targets as used targets.  */
  finish_aliases_1 ();
  cgraph_varpool_analyze_pending_decls ();
}