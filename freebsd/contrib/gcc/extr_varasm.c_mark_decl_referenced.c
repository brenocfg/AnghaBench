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
struct cgraph_varpool_node {int force_output; } ;
struct TYPE_2__ {int /*<<< orphan*/  finalized; int /*<<< orphan*/  vtable_method; } ;
struct cgraph_node {TYPE_1__ local; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  cgraph_global_info_ready ; 
 int /*<<< orphan*/  cgraph_mark_needed_node (struct cgraph_node*) ; 
 struct cgraph_node* cgraph_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_varpool_mark_needed_node (struct cgraph_varpool_node*) ; 
 struct cgraph_varpool_node* cgraph_varpool_node (int /*<<< orphan*/ ) ; 

void
mark_decl_referenced (tree decl)
{
  if (TREE_CODE (decl) == FUNCTION_DECL)
    {
      /* Extern inline functions don't become needed when referenced.
	 If we know a method will be emitted in other TU and no new
	 functions can be marked reachable, just use the external
	 definition.  */
      struct cgraph_node *node = cgraph_node (decl);
      if (!DECL_EXTERNAL (decl)
	  && (!node->local.vtable_method || !cgraph_global_info_ready
	      || !node->local.finalized))
	cgraph_mark_needed_node (node);
    }
  else if (TREE_CODE (decl) == VAR_DECL)
    {
      struct cgraph_varpool_node *node = cgraph_varpool_node (decl);
      cgraph_varpool_mark_needed_node (node);
      /* C++ frontend use mark_decl_references to force COMDAT variables
         to be output that might appear dead otherwise.  */
      node->force_output = true;
    }
  /* else do nothing - we can get various sorts of CST nodes here,
     which do not need to be marked.  */
}