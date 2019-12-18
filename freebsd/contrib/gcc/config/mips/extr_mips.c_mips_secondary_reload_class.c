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
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_REGS ; 
 scalar_t__ ACC_REG_P (int) ; 
 scalar_t__ CONST0_RTX (int) ; 
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 int FP_REGS ; 
 scalar_t__ FP_REG_P (int) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 int GP_REG_P (int) ; 
 int GR_REGS ; 
 int LEA_REGS ; 
 int M16_NA_REGS ; 
 int M16_REGS ; 
 int M16_REG_P (int) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ MODE_FLOAT ; 
 int NO_REGS ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int ST_REGS ; 
 scalar_t__ ST_REG_P (int) ; 
 scalar_t__ SUBREG ; 
 scalar_t__ TARGET_MIPS16 ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mips_dangerous_for_la25_p (scalar_t__) ; 
 int /*<<< orphan*/ * reg_class_contents ; 
 scalar_t__ reg_class_subset_p (int,int /*<<< orphan*/ ) ; 
 int true_regnum (scalar_t__) ; 

enum reg_class
mips_secondary_reload_class (enum reg_class class,
			     enum machine_mode mode, rtx x, int in_p)
{
  enum reg_class gr_regs = TARGET_MIPS16 ? M16_REGS : GR_REGS;
  int regno = -1;
  int gp_reg_p;

  if (REG_P (x)|| GET_CODE (x) == SUBREG)
    regno = true_regnum (x);

  gp_reg_p = TARGET_MIPS16 ? M16_REG_P (regno) : GP_REG_P (regno);

  if (mips_dangerous_for_la25_p (x))
    {
      gr_regs = LEA_REGS;
      if (TEST_HARD_REG_BIT (reg_class_contents[(int) class], 25))
	return gr_regs;
    }

  /* Copying from HI or LO to anywhere other than a general register
     requires a general register.
     This rule applies to both the original HI/LO pair and the new
     DSP accumulators.  */
  if (reg_class_subset_p (class, ACC_REGS))
    {
      if (TARGET_MIPS16 && in_p)
	{
	  /* We can't really copy to HI or LO at all in mips16 mode.  */
	  return M16_REGS;
	}
      return gp_reg_p ? NO_REGS : gr_regs;
    }
  if (ACC_REG_P (regno))
    {
      if (TARGET_MIPS16 && ! in_p)
	{
	  /* We can't really copy to HI or LO at all in mips16 mode.  */
	  return M16_REGS;
	}
      return class == gr_regs ? NO_REGS : gr_regs;
    }

  /* We can only copy a value to a condition code register from a
     floating point register, and even then we require a scratch
     floating point register.  We can only copy a value out of a
     condition code register into a general register.  */
  if (class == ST_REGS)
    {
      if (in_p)
	return FP_REGS;
      return gp_reg_p ? NO_REGS : gr_regs;
    }
  if (ST_REG_P (regno))
    {
      if (! in_p)
	return FP_REGS;
      return class == gr_regs ? NO_REGS : gr_regs;
    }

  if (class == FP_REGS)
    {
      if (MEM_P (x))
	{
	  /* In this case we can use lwc1, swc1, ldc1 or sdc1.  */
	  return NO_REGS;
	}
      else if (CONSTANT_P (x) && GET_MODE_CLASS (mode) == MODE_FLOAT)
	{
	  /* We can use the l.s and l.d macros to load floating-point
	     constants.  ??? For l.s, we could probably get better
	     code by returning GR_REGS here.  */
	  return NO_REGS;
	}
      else if (gp_reg_p || x == CONST0_RTX (mode))
	{
	  /* In this case we can use mtc1, mfc1, dmtc1 or dmfc1.  */
	  return NO_REGS;
	}
      else if (FP_REG_P (regno))
	{
	  /* In this case we can use mov.s or mov.d.  */
	  return NO_REGS;
	}
      else
	{
	  /* Otherwise, we need to reload through an integer register.  */
	  return gr_regs;
	}
    }

  /* In mips16 mode, going between memory and anything but M16_REGS
     requires an M16_REG.  */
  if (TARGET_MIPS16)
    {
      if (class != M16_REGS && class != M16_NA_REGS)
	{
	  if (gp_reg_p)
	    return NO_REGS;
	  return M16_REGS;
	}
      if (! gp_reg_p)
	{
	  if (class == M16_REGS || class == M16_NA_REGS)
	    return NO_REGS;
	  return M16_REGS;
	}
    }

  return NO_REGS;
}