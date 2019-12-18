#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct cgraph_node {int /*<<< orphan*/  nested; } ;
struct TYPE_8__ {struct TYPE_8__* inner; } ;

/* Variables and functions */
 struct cgraph_node* cgraph_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_all_function_calls (TYPE_1__*) ; 
 int /*<<< orphan*/  convert_local_reference ; 
 int /*<<< orphan*/  convert_nl_goto_receiver ; 
 int /*<<< orphan*/  convert_nl_goto_reference ; 
 int /*<<< orphan*/  convert_nonlocal_reference ; 
 TYPE_1__* create_nesting_tree (struct cgraph_node*) ; 
 int /*<<< orphan*/  finalize_nesting_tree (TYPE_1__*) ; 
 int /*<<< orphan*/  free_nesting_tree (TYPE_1__*) ; 
 TYPE_1__* root ; 
 int /*<<< orphan*/  unnest_nesting_tree (TYPE_1__*) ; 
 int /*<<< orphan*/  walk_all_functions (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
/* APPLE LOCAL radar 6305545 */
lower_nested_functions (tree fndecl, bool skip_outermost_fndecl)
{
  struct cgraph_node *cgn;

  /* If there are no nested functions, there's nothing to do.  */
  cgn = cgraph_node (fndecl);
  if (!cgn->nested)
    return;

  root = create_nesting_tree (cgn);
  /* APPLE LOCAL begin radar 6305545 */
  /* If skip_outermost_fndecl is true, we are lowering nested functions of
     a constructor/destructor which are cloned and thrown away. But we
     still have to lower their nested functions, but not the outermost function. */
  if (skip_outermost_fndecl)
    root = root->inner;
  /* APPLE LOCAL end radar 6305545 */
  walk_all_functions (convert_nonlocal_reference, root);
  walk_all_functions (convert_local_reference, root);
  walk_all_functions (convert_nl_goto_reference, root);
  walk_all_functions (convert_nl_goto_receiver, root);
  convert_all_function_calls (root);
  finalize_nesting_tree (root);
  unnest_nesting_tree (root);
  free_nesting_tree (root);
  root = NULL;
}