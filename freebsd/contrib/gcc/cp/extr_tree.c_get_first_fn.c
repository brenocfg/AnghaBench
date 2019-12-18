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
 int /*<<< orphan*/  BASELINK_FUNCTIONS (int /*<<< orphan*/ ) ; 
 scalar_t__ BASELINK_P (int /*<<< orphan*/ ) ; 
 scalar_t__ COMPONENT_REF ; 
 int /*<<< orphan*/  OVL_CURRENT (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_overloaded_fn (int /*<<< orphan*/ ) ; 

tree
get_first_fn (tree from)
{
  gcc_assert (is_overloaded_fn (from));
  /* A baselink is also considered an overloaded function.  */
  if (TREE_CODE (from) == COMPONENT_REF)
    from = TREE_OPERAND (from, 1);
  if (BASELINK_P (from))
    from = BASELINK_FUNCTIONS (from);
  return OVL_CURRENT (from);
}