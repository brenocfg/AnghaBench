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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 scalar_t__ HONOR_SIGNED_ZEROS (int /*<<< orphan*/ ) ; 
 scalar_t__ REAL_CST ; 
 scalar_t__ REAL_VALUES_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/ * SSA_NAME_VALUE (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_INVARIANT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_REAL_CST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VALUE_HANDLE ; 
 int /*<<< orphan*/  dconst0 ; 
 scalar_t__ loop_depth_of_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_const_or_copy_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
record_equality (tree x, tree y)
{
  tree prev_x = NULL, prev_y = NULL;

  if (TREE_CODE (x) == SSA_NAME)
    prev_x = SSA_NAME_VALUE (x);
  if (TREE_CODE (y) == SSA_NAME)
    prev_y = SSA_NAME_VALUE (y);

  /* If one of the previous values is invariant, or invariant in more loops
     (by depth), then use that.
     Otherwise it doesn't matter which value we choose, just so
     long as we canonicalize on one value.  */
  if (TREE_INVARIANT (y))
    ;
  else if (TREE_INVARIANT (x) || (loop_depth_of_name (x) <= loop_depth_of_name (y)))
    prev_x = x, x = y, y = prev_x, prev_x = prev_y;
  else if (prev_x && TREE_INVARIANT (prev_x))
    x = y, y = prev_x, prev_x = prev_y;
  else if (prev_y && TREE_CODE (prev_y) != VALUE_HANDLE)
    y = prev_y;

  /* After the swapping, we must have one SSA_NAME.  */
  if (TREE_CODE (x) != SSA_NAME)
    return;

  /* For IEEE, -0.0 == 0.0, so we don't necessarily know the sign of a
     variable compared against zero.  If we're honoring signed zeros,
     then we cannot record this value unless we know that the value is
     nonzero.  */
  if (HONOR_SIGNED_ZEROS (TYPE_MODE (TREE_TYPE (x)))
      && (TREE_CODE (y) != REAL_CST
	  || REAL_VALUES_EQUAL (dconst0, TREE_REAL_CST (y))))
    return;

  record_const_or_copy_1 (x, y, prev_x);
}