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
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ PUBLICLY_UNIQUELY_DERIVED_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_type_quals (int /*<<< orphan*/ ) ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
comp_except_types (tree a, tree b, bool exact)
{
  if (same_type_p (a, b))
    return true;
  else if (!exact)
    {
      if (cp_type_quals (a) || cp_type_quals (b))
	return false;

      if (TREE_CODE (a) == POINTER_TYPE
	  && TREE_CODE (b) == POINTER_TYPE)
	{
	  a = TREE_TYPE (a);
	  b = TREE_TYPE (b);
	  if (cp_type_quals (a) || cp_type_quals (b))
	    return false;
	}

      if (TREE_CODE (a) != RECORD_TYPE
	  || TREE_CODE (b) != RECORD_TYPE)
	return false;

      if (PUBLICLY_UNIQUELY_DERIVED_P (a, b))
	return true;
    }
  return false;
}