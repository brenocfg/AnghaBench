#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {int finalized; } ;
struct cgraph_node {scalar_t__ nested; int /*<<< orphan*/  lowered; TYPE_1__ local; int /*<<< orphan*/  decl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * cfg; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* deferred_inline_function ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_COMDAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 TYPE_3__* DECL_STRUCT_FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_ASM_WRITTEN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_analyze_function (struct cgraph_node*) ; 
 int /*<<< orphan*/  cgraph_assemble_pending_functions () ; 
 int /*<<< orphan*/  cgraph_decide_inlining_incrementally (struct cgraph_node*,int) ; 
 int /*<<< orphan*/  cgraph_mark_needed_node (struct cgraph_node*) ; 
 int /*<<< orphan*/  cgraph_mark_reachable_node (struct cgraph_node*) ; 
 struct cgraph_node* cgraph_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_reset_node (struct cgraph_node*) ; 
 TYPE_2__* debug_hooks ; 
 scalar_t__ decide_is_function_needed (struct cgraph_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_warn_unused_parameter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_unit_at_a_time ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  ggc_collect () ; 
 int /*<<< orphan*/  lower_nested_functions (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  notice_global_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ warn_unused_parameter ; 

void
cgraph_finalize_function (tree decl, bool nested)
{
  struct cgraph_node *node = cgraph_node (decl);

  if (node->local.finalized)
    cgraph_reset_node (node);

  notice_global_symbol (decl);
  node->decl = decl;
  node->local.finalized = true;
  node->lowered = DECL_STRUCT_FUNCTION (decl)->cfg != NULL;
  if (node->nested)
    /* APPLE LOCAL radar 6305545 */
    lower_nested_functions (decl, false);
  gcc_assert (!node->nested);

  /* If not unit at a time, then we need to create the call graph
     now, so that called functions can be queued and emitted now.  */
  if (!flag_unit_at_a_time)
    {
      cgraph_analyze_function (node);
      cgraph_decide_inlining_incrementally (node, false);
    }

  if (decide_is_function_needed (node, decl))
    cgraph_mark_needed_node (node);

  /* Since we reclaim unreachable nodes at the end of every language
     level unit, we need to be conservative about possible entry points
     there.  */
  if ((TREE_PUBLIC (decl) && !DECL_COMDAT (decl) && !DECL_EXTERNAL (decl)))
    cgraph_mark_reachable_node (node);

  /* If not unit at a time, go ahead and emit everything we've found
     to be reachable at this time.  */
  if (!nested)
    {
      if (!cgraph_assemble_pending_functions ())
	ggc_collect ();
    }

  /* If we've not yet emitted decl, tell the debug info about it.  */
  if (!TREE_ASM_WRITTEN (decl))
    (*debug_hooks->deferred_inline_function) (decl);

  /* Possibly warn about unused parameters.  */
  if (warn_unused_parameter)
    do_warn_unused_parameter (decl);
}