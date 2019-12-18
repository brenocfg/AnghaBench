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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 scalar_t__ gen_lowpart (scalar_t__,scalar_t__) ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
rtx_equal_for_field_assignment_p (rtx x, rtx y)
{
  if (x == y || rtx_equal_p (x, y))
    return 1;

  if (x == 0 || y == 0 || GET_MODE (x) != GET_MODE (y))
    return 0;

  /* Check for a paradoxical SUBREG of a MEM compared with the MEM.
     Note that all SUBREGs of MEM are paradoxical; otherwise they
     would have been rewritten.  */
  if (MEM_P (x) && GET_CODE (y) == SUBREG
      && MEM_P (SUBREG_REG (y))
      && rtx_equal_p (SUBREG_REG (y),
		      gen_lowpart (GET_MODE (SUBREG_REG (y)), x)))
    return 1;

  if (MEM_P (y) && GET_CODE (x) == SUBREG
      && MEM_P (SUBREG_REG (x))
      && rtx_equal_p (SUBREG_REG (x),
		      gen_lowpart (GET_MODE (SUBREG_REG (x)), y)))
    return 1;

  /* We used to see if get_last_value of X and Y were the same but that's
     not correct.  In one direction, we'll cause the assignment to have
     the wrong destination and in the case, we'll import a register into this
     insn that might have already have been dead.   So fail if none of the
     above cases are true.  */
  return 0;
}