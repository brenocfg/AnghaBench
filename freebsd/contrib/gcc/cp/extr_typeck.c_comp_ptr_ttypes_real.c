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
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ METHOD_TYPE ; 
 scalar_t__ OFFSET_TYPE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_OFFSET_BASETYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_P (int /*<<< orphan*/ ) ; 
 int TYPE_READONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at_least_as_qualified_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int objc_type_quals_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ same_type_ignoring_top_level_qualifiers_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
comp_ptr_ttypes_real (tree to, tree from, int constp)
{
  bool to_more_cv_qualified = false;

  for (; ; to = TREE_TYPE (to), from = TREE_TYPE (from))
    {
      if (TREE_CODE (to) != TREE_CODE (from))
	return 0;

      if (TREE_CODE (from) == OFFSET_TYPE
	  && !same_type_p (TYPE_OFFSET_BASETYPE (from),
			   TYPE_OFFSET_BASETYPE (to)))
	return 0;

      /* Const and volatile mean something different for function types,
	 so the usual checks are not appropriate.  */
      if (TREE_CODE (to) != FUNCTION_TYPE && TREE_CODE (to) != METHOD_TYPE)
	{
	  /* In Objective-C++, some types may have been 'volatilized' by
	     the compiler for EH; when comparing them here, the volatile
	     qualification must be ignored.  */
	  bool objc_quals_match = objc_type_quals_match (to, from);

	  if (!at_least_as_qualified_p (to, from) && !objc_quals_match)
	    return 0;

	  if (!at_least_as_qualified_p (from, to) && !objc_quals_match)
	    {
	      if (constp == 0)
		return 0;
	      to_more_cv_qualified = true;
	    }

	  if (constp > 0)
	    constp &= TYPE_READONLY (to);
	}

      if (TREE_CODE (to) != POINTER_TYPE && !TYPE_PTRMEM_P (to))
	return ((constp >= 0 || to_more_cv_qualified)
		&& same_type_ignoring_top_level_qualifiers_p (to, from));
    }
}