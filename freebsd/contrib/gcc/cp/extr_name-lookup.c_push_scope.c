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

/* Variables and functions */
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ NAMESPACE_DECL ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at_class_scope_p () ; 
 int /*<<< orphan*/  current_class_type ; 
 int /*<<< orphan*/  push_decl_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_nested_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
push_scope (tree t)
{
  if (TREE_CODE (t) == NAMESPACE_DECL)
    push_decl_namespace (t);
  else if (CLASS_TYPE_P (t))
    {
      if (!at_class_scope_p ()
	  || !same_type_p (current_class_type, t))
	push_nested_class (t);
      else
	/* T is the same as the current scope.  There is therefore no
	   need to re-enter the scope.  Since we are not actually
	   pushing a new scope, our caller should not call
	   pop_scope.  */
	t = NULL_TREE;
    }

  return t;
}