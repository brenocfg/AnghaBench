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
 int COMPARE_BASE ; 
 int COMPARE_DERIVED ; 
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ INTEGER_TYPE ; 
 scalar_t__ OFFSET_TYPE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_OFFSET_BASETYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 scalar_t__ VECTOR_TYPE ; 
 scalar_t__ VOID_TYPE ; 
 int comptypes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vector_types_convertible_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
ptr_reasonably_similar (tree to, tree from)
{
  for (; ; to = TREE_TYPE (to), from = TREE_TYPE (from))
    {
      /* Any target type is similar enough to void.  */
      if (TREE_CODE (to) == VOID_TYPE
	  || TREE_CODE (from) == VOID_TYPE)
	return 1;

      if (TREE_CODE (to) != TREE_CODE (from))
	return 0;

      if (TREE_CODE (from) == OFFSET_TYPE
	  && comptypes (TYPE_OFFSET_BASETYPE (to),
			TYPE_OFFSET_BASETYPE (from),
			COMPARE_BASE | COMPARE_DERIVED))
	continue;

      if (TREE_CODE (to) == VECTOR_TYPE
	  && vector_types_convertible_p (to, from, false))
	return 1;

      if (TREE_CODE (to) == INTEGER_TYPE
	  && TYPE_PRECISION (to) == TYPE_PRECISION (from))
	return 1;

      if (TREE_CODE (to) == FUNCTION_TYPE)
	return 1;

      if (TREE_CODE (to) != POINTER_TYPE)
	return comptypes
	  (TYPE_MAIN_VARIANT (to), TYPE_MAIN_VARIANT (from),
	   COMPARE_BASE | COMPARE_DERIVED);
    }
}