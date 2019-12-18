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
struct iv {scalar_t__ step; } ;

/* Variables and functions */
 scalar_t__ INTEGER_CST ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PRECISION (scalar_t__) ; 
 scalar_t__ build_low_bits_mask (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ num_ending_zeros (scalar_t__) ; 
 scalar_t__ tree_low_cst (scalar_t__,int) ; 
 scalar_t__ unsigned_type_for (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
iv_period (struct iv *iv)
{
  tree step = iv->step, period, type;
  tree pow2div;

  gcc_assert (step && TREE_CODE (step) == INTEGER_CST);

  /* Period of the iv is gcd (step, type range).  Since type range is power
     of two, it suffices to determine the maximum power of two that divides
     step.  */
  pow2div = num_ending_zeros (step);
  type = unsigned_type_for (TREE_TYPE (step));

  period = build_low_bits_mask (type,
				(TYPE_PRECISION (type)
				 - tree_low_cst (pow2div, 1)));

  return period;
}