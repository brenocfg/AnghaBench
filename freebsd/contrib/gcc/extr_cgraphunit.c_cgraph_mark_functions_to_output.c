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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {scalar_t__ inlined_to; } ;
struct cgraph_node {int output; TYPE_1__ global; scalar_t__ reachable; scalar_t__ needed; struct cgraph_edge* callers; int /*<<< orphan*/  decl; struct cgraph_node* next; } ;
struct cgraph_edge {scalar_t__ inline_failed; struct cgraph_edge* next_caller; } ;

/* Variables and functions */
 scalar_t__ DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_SAVED_TREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_ASM_WRITTEN (int /*<<< orphan*/ ) ; 
 struct cgraph_node* cgraph_nodes ; 
 int /*<<< orphan*/  dump_cgraph_node (int /*<<< orphan*/ ,struct cgraph_node*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  internal_error (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
cgraph_mark_functions_to_output (void)
{
  struct cgraph_node *node;

  for (node = cgraph_nodes; node; node = node->next)
    {
      tree decl = node->decl;
      struct cgraph_edge *e;

      gcc_assert (!node->output);

      for (e = node->callers; e; e = e->next_caller)
	if (e->inline_failed)
	  break;

      /* We need to output all local functions that are used and not
	 always inlined, as well as those that are reachable from
	 outside the current compilation unit.  */
      if (DECL_SAVED_TREE (decl)
	  && !node->global.inlined_to
	  && (node->needed
	      || (e && node->reachable))
	  && !TREE_ASM_WRITTEN (decl)
	  && !DECL_EXTERNAL (decl))
	node->output = 1;
      else
	{
	  /* We should've reclaimed all functions that are not needed.  */
#ifdef ENABLE_CHECKING
	  if (!node->global.inlined_to && DECL_SAVED_TREE (decl)
	      && !DECL_EXTERNAL (decl))
	    {
	      dump_cgraph_node (stderr, node);
	      internal_error ("failed to reclaim unneeded function");
	    }
#endif
	  gcc_assert (node->global.inlined_to || !DECL_SAVED_TREE (decl)
		      || DECL_EXTERNAL (decl));

	}

    }
}