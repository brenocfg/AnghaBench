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
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MIN_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 int /*<<< orphan*/  is_overflow_infinity (int /*<<< orphan*/ ) ; 
 scalar_t__ operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline tree
avoid_overflow_infinity (tree val)
{
  if (!is_overflow_infinity (val))
    return val;

  if (operand_equal_p (val, TYPE_MAX_VALUE (TREE_TYPE (val)), 0))
    return TYPE_MAX_VALUE (TREE_TYPE (val));
  else
    {
#ifdef ENABLE_CHECKING
      gcc_assert (operand_equal_p (val, TYPE_MIN_VALUE (TREE_TYPE (val)), 0));
#endif
      return TYPE_MIN_VALUE (TREE_TYPE (val));
    }
}