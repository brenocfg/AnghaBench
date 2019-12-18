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
struct cgraph_varpool_node {int finalized; scalar_t__ needed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_COMDAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 scalar_t__ cgraph_global_info_ready ; 
 int /*<<< orphan*/  cgraph_varpool_assemble_pending_decls () ; 
 int /*<<< orphan*/  cgraph_varpool_enqueue_needed_node (struct cgraph_varpool_node*) ; 
 int /*<<< orphan*/  cgraph_varpool_mark_needed_node (struct cgraph_varpool_node*) ; 
 struct cgraph_varpool_node* cgraph_varpool_node (int /*<<< orphan*/ ) ; 
 scalar_t__ decide_is_variable_needed (struct cgraph_varpool_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_openmp ; 
 int /*<<< orphan*/  flag_unit_at_a_time ; 

void
cgraph_varpool_finalize_decl (tree decl)
{
  struct cgraph_varpool_node *node = cgraph_varpool_node (decl);

  /* The first declaration of a variable that comes through this function
     decides whether it is global (in C, has external linkage)
     or local (in C, has internal linkage).  So do nothing more
     if this function has already run.  */
  if (node->finalized)
    {
      if (cgraph_global_info_ready || (!flag_unit_at_a_time && !flag_openmp))
	cgraph_varpool_assemble_pending_decls ();
      return;
    }
  if (node->needed)
    cgraph_varpool_enqueue_needed_node (node);
  node->finalized = true;

  if (decide_is_variable_needed (node, decl))
    cgraph_varpool_mark_needed_node (node);
  /* Since we reclaim unreachable nodes at the end of every language
     level unit, we need to be conservative about possible entry points
     there.  */
  else if (TREE_PUBLIC (decl) && !DECL_COMDAT (decl) && !DECL_EXTERNAL (decl))
    cgraph_varpool_mark_needed_node (node);
  if (cgraph_global_info_ready || (!flag_unit_at_a_time && !flag_openmp))
    cgraph_varpool_assemble_pending_decls ();
}