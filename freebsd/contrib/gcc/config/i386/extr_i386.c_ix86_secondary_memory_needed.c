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
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int DFmode ; 
 scalar_t__ FLOAT_CLASS_P (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 scalar_t__ MAYBE_FLOAT_CLASS_P (int) ; 
 scalar_t__ MAYBE_MMX_CLASS_P (int) ; 
 scalar_t__ MAYBE_SSE_CLASS_P (int) ; 
 scalar_t__ MMX_CLASS_P (int) ; 
 int SFmode ; 
 scalar_t__ SSE_CLASS_P (int) ; 
 int /*<<< orphan*/  TARGET_INTER_UNIT_MOVES ; 
 int /*<<< orphan*/  TARGET_SSE2 ; 
 scalar_t__ UNITS_PER_WORD ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  optimize_size ; 

int
ix86_secondary_memory_needed (enum reg_class class1, enum reg_class class2,
			      enum machine_mode mode, int strict)
{
  if (MAYBE_FLOAT_CLASS_P (class1) != FLOAT_CLASS_P (class1)
      || MAYBE_FLOAT_CLASS_P (class2) != FLOAT_CLASS_P (class2)
      || MAYBE_SSE_CLASS_P (class1) != SSE_CLASS_P (class1)
      || MAYBE_SSE_CLASS_P (class2) != SSE_CLASS_P (class2)
      || MAYBE_MMX_CLASS_P (class1) != MMX_CLASS_P (class1)
      || MAYBE_MMX_CLASS_P (class2) != MMX_CLASS_P (class2))
    {
      gcc_assert (!strict);
      return true;
    }

  if (FLOAT_CLASS_P (class1) != FLOAT_CLASS_P (class2))
    return true;

  /* ??? This is a lie.  We do have moves between mmx/general, and for
     mmx/sse2.  But by saying we need secondary memory we discourage the
     register allocator from using the mmx registers unless needed.  */
  if (MMX_CLASS_P (class1) != MMX_CLASS_P (class2))
    return true;

  if (SSE_CLASS_P (class1) != SSE_CLASS_P (class2))
    {
      /* SSE1 doesn't have any direct moves from other classes.  */
      if (!TARGET_SSE2)
	return true;

      /* If the target says that inter-unit moves are more expensive
	 than moving through memory, then don't generate them.  */
      if (!TARGET_INTER_UNIT_MOVES && !optimize_size)
	return true;

      /* Between SSE and general, we have moves no larger than word size.  */
      if (GET_MODE_SIZE (mode) > UNITS_PER_WORD)
	return true;

      /* ??? For the cost of one register reformat penalty, we could use
	 the same instructions to move SFmode and DFmode data, but the
	 relevant move patterns don't support those alternatives.  */
      if (mode == SFmode || mode == DFmode)
	return true;
    }

  return false;
}