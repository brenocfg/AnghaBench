#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {scalar_t__ (* guard_mask_bit ) () ;} ;
struct TYPE_4__ {TYPE_1__ cxx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_AND_EXPR ; 
 int /*<<< orphan*/  EQ_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_build_binary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_guard_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 () ; 
 TYPE_2__ targetm ; 

tree
get_guard_cond (tree guard)
{
  tree guard_value;

  /* Check to see if the GUARD is zero.  */
  guard = get_guard_bits (guard);

  /* Mask off all but the low bit.  */
  if (targetm.cxx.guard_mask_bit ())
    {
      guard_value = integer_one_node;
      if (!same_type_p (TREE_TYPE (guard_value), TREE_TYPE (guard)))
	guard_value = convert (TREE_TYPE (guard), guard_value);
	guard = cp_build_binary_op (BIT_AND_EXPR, guard, guard_value);
    }

  guard_value = integer_zero_node;
  if (!same_type_p (TREE_TYPE (guard_value), TREE_TYPE (guard)))
    guard_value = convert (TREE_TYPE (guard), guard_value);
  return cp_build_binary_op (EQ_EXPR, guard, guard_value);
}