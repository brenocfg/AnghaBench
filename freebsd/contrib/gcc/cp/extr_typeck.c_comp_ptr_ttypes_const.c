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
 scalar_t__ OFFSET_TYPE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_OFFSET_BASETYPE (int /*<<< orphan*/ ) ; 
 int same_type_ignoring_top_level_qualifiers_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
comp_ptr_ttypes_const (tree to, tree from)
{
  for (; ; to = TREE_TYPE (to), from = TREE_TYPE (from))
    {
      if (TREE_CODE (to) != TREE_CODE (from))
	return false;

      if (TREE_CODE (from) == OFFSET_TYPE
	  && same_type_p (TYPE_OFFSET_BASETYPE (from),
			  TYPE_OFFSET_BASETYPE (to)))
	  continue;

      if (TREE_CODE (to) != POINTER_TYPE)
	return same_type_ignoring_top_level_qualifiers_p (to, from);
    }
}