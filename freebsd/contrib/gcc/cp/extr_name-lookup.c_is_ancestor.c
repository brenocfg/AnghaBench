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
 scalar_t__ CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_NAME (scalar_t__) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ global_namespace ; 

bool
is_ancestor (tree root, tree child)
{
  gcc_assert ((TREE_CODE (root) == NAMESPACE_DECL
	       || TREE_CODE (root) == FUNCTION_DECL
	       || CLASS_TYPE_P (root)));
  gcc_assert ((TREE_CODE (child) == NAMESPACE_DECL
	       || CLASS_TYPE_P (child)));

  /* The global namespace encloses everything.  */
  if (root == global_namespace)
    return true;

  while (true)
    {
      /* If we've run out of scopes, stop.  */
      if (!child)
	return false;
      /* If we've reached the ROOT, it encloses CHILD.  */
      if (root == child)
	return true;
      /* Go out one level.  */
      if (TYPE_P (child))
	child = TYPE_NAME (child);
      child = DECL_CONTEXT (child);
    }
}