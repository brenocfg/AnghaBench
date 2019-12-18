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

/* Variables and functions */
 scalar_t__ FUNCTION_TYPE ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_RAISES_EXCEPTIONS (scalar_t__) ; 
 scalar_t__ build_exception_variant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_function_type (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  pedwarn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr_type_node ; 
 int /*<<< orphan*/  same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_type_node ; 
 scalar_t__ tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ void_list_node ; 

tree
coerce_new_type (tree type)
{
  int e = 0;
  tree args = TYPE_ARG_TYPES (type);

  gcc_assert (TREE_CODE (type) == FUNCTION_TYPE);

  if (!same_type_p (TREE_TYPE (type), ptr_type_node))
    {
      e = 1;
      error ("%<operator new%> must return type %qT", ptr_type_node);
    }

  if (!args || args == void_list_node
      || !same_type_p (TREE_VALUE (args), size_type_node))
    {
      e = 2;
      if (args && args != void_list_node)
	args = TREE_CHAIN (args);
      pedwarn ("%<operator new%> takes type %<size_t%> (%qT) "
	       "as first parameter", size_type_node);
    }
  switch (e)
  {
    case 2:
      args = tree_cons (NULL_TREE, size_type_node, args);
      /* Fall through.  */
    case 1:
      type = build_exception_variant
	      (build_function_type (ptr_type_node, args),
	       TYPE_RAISES_EXCEPTIONS (type));
      /* Fall through.  */
    default:;
  }
  return type;
}