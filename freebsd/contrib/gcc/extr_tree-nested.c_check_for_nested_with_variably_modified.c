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
typedef  scalar_t__ tree ;
struct cgraph_node {scalar_t__ decl; struct cgraph_node* next_nested; struct cgraph_node* nested; } ;

/* Variables and functions */
 scalar_t__ DECL_ARGUMENTS (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 struct cgraph_node* cgraph_node (scalar_t__) ; 
 scalar_t__ variably_modified_type_p (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
check_for_nested_with_variably_modified (tree fndecl, tree orig_fndecl)
{
  struct cgraph_node *cgn = cgraph_node (fndecl);
  tree arg;

  for (cgn = cgn->nested; cgn ; cgn = cgn->next_nested)
    {
      for (arg = DECL_ARGUMENTS (cgn->decl); arg; arg = TREE_CHAIN (arg))
	if (variably_modified_type_p (TREE_TYPE (arg), orig_fndecl))
	  return true;

      if (check_for_nested_with_variably_modified (cgn->decl, orig_fndecl))
	return true;
    }

  return false;
}