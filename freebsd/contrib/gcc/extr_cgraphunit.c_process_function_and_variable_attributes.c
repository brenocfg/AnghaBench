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
struct cgraph_varpool_node {int externally_visible; scalar_t__ finalized; int /*<<< orphan*/  decl; struct cgraph_varpool_node* next; } ;
struct TYPE_2__ {int externally_visible; scalar_t__ finalized; } ;
struct cgraph_node {TYPE_1__ local; int /*<<< orphan*/  decl; struct cgraph_node* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_Wattributes ; 
 int /*<<< orphan*/  TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_mark_needed_node (struct cgraph_node*) ; 
 struct cgraph_node* cgraph_nodes ; 
 int /*<<< orphan*/  cgraph_varpool_mark_needed_node (struct cgraph_varpool_node*) ; 
 struct cgraph_varpool_node* cgraph_varpool_nodes ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_decl_referenced (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_function_and_variable_attributes (struct cgraph_node *first,
                                          struct cgraph_varpool_node *first_var)
{
  struct cgraph_node *node;
  struct cgraph_varpool_node *vnode;

  for (node = cgraph_nodes; node != first; node = node->next)
    {
      tree decl = node->decl;
      if (lookup_attribute ("used", DECL_ATTRIBUTES (decl)))
	{
	  mark_decl_referenced (decl);
	  if (node->local.finalized)
	     cgraph_mark_needed_node (node);
	}
      if (lookup_attribute ("externally_visible", DECL_ATTRIBUTES (decl)))
	{
	  if (! TREE_PUBLIC (node->decl))
	    warning (OPT_Wattributes,
		     "%J%<externally_visible%> attribute have effect only on public objects",
		     node->decl);
	  else
	    {
	      if (node->local.finalized)
		cgraph_mark_needed_node (node);
	      node->local.externally_visible = true;
	    }
	}
    }
  for (vnode = cgraph_varpool_nodes; vnode != first_var; vnode = vnode->next)
    {
      tree decl = vnode->decl;
      if (lookup_attribute ("used", DECL_ATTRIBUTES (decl)))
	{
	  mark_decl_referenced (decl);
	  if (vnode->finalized)
	    cgraph_varpool_mark_needed_node (vnode);
	}
      if (lookup_attribute ("externally_visible", DECL_ATTRIBUTES (decl)))
	{
	  if (! TREE_PUBLIC (vnode->decl))
	    warning (OPT_Wattributes,
		     "%J%<externally_visible%> attribute have effect only on public objects",
		     vnode->decl);
	  else
	    {
	      if (vnode->finalized)
		cgraph_varpool_mark_needed_node (vnode);
	      vnode->externally_visible = true;
	    }
	}
    }
}