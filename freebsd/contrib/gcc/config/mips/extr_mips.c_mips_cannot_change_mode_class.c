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
 int /*<<< orphan*/  ACC_REGS ; 
 int FP_INC ; 
 int /*<<< orphan*/  FP_REGS ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 scalar_t__ MAX (scalar_t__,scalar_t__) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int SImode ; 
 scalar_t__ TARGET_BIG_ENDIAN ; 
 scalar_t__ TARGET_FLOAT64 ; 
 scalar_t__ UNITS_PER_WORD ; 
 scalar_t__ reg_classes_intersect_p (int /*<<< orphan*/ ,int) ; 

bool
mips_cannot_change_mode_class (enum machine_mode from,
			       enum machine_mode to, enum reg_class class)
{
  if (MIN (GET_MODE_SIZE (from), GET_MODE_SIZE (to)) <= UNITS_PER_WORD
      && MAX (GET_MODE_SIZE (from), GET_MODE_SIZE (to)) > UNITS_PER_WORD)
    {
      if (TARGET_BIG_ENDIAN)
	{
	  /* When a multi-word value is stored in paired floating-point
	     registers, the first register always holds the low word.
	     We therefore can't allow FPRs to change between single-word
	     and multi-word modes.  */
	  if (FP_INC > 1 && reg_classes_intersect_p (FP_REGS, class))
	    return true;
	}
      else
	{
	  /* LO_REGNO == HI_REGNO + 1, so if a multi-word value is stored
	     in LO and HI, the high word always comes first.  We therefore
	     can't allow values stored in HI to change between single-word
	     and multi-word modes.
	     This rule applies to both the original HI/LO pair and the new
	     DSP accumulators.  */
	  if (reg_classes_intersect_p (ACC_REGS, class))
	    return true;
	}
    }
  /* Loading a 32-bit value into a 64-bit floating-point register
     will not sign-extend the value, despite what LOAD_EXTEND_OP says.
     We can't allow 64-bit float registers to change from SImode to
     to a wider mode.  */
  if (TARGET_FLOAT64
      && from == SImode
      && GET_MODE_SIZE (to) >= UNITS_PER_WORD
      && reg_classes_intersect_p (FP_REGS, class))
    return true;
  return false;
}