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
typedef  int /*<<< orphan*/  value_range_t ;
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  VR_RANGE ; 
 int /*<<< orphan*/  avoid_overflow_infinity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_min_invariant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_value_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
set_value_range_to_value (value_range_t *vr, tree val, bitmap equiv)
{
  gcc_assert (is_gimple_min_invariant (val));
  val = avoid_overflow_infinity (val);
  set_value_range (vr, VR_RANGE, val, val, equiv);
}