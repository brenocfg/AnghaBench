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

/* Variables and functions */
 int ARG_POINTER_REGNUM ; 
 int CC_REG ; 
 int CC_REGNUM ; 
 int CIRRUS_REGS ; 
 int FPA_REGS ; 
 int FRAME_POINTER_REGNUM ; 
 int GENERAL_REGS ; 
 int HI_REGS ; 
 scalar_t__ IS_CIRRUS_REGNUM (int) ; 
 scalar_t__ IS_IWMMXT_GR_REGNUM (int) ; 
 scalar_t__ IS_IWMMXT_REGNUM (int) ; 
 scalar_t__ IS_VFP_REGNUM (int) ; 
 int IWMMXT_GR_REGS ; 
 int IWMMXT_REGS ; 
 int LAST_ARM_REGNUM ; 
 int LO_REGS ; 
 int NO_REGS ; 
 int STACK_POINTER_REGNUM ; 
 int STACK_REG ; 
 scalar_t__ TARGET_THUMB ; 
 int VFPCC_REGNUM ; 
 int VFP_REGS ; 

int
arm_regno_class (int regno)
{
  if (TARGET_THUMB)
    {
      if (regno == STACK_POINTER_REGNUM)
	return STACK_REG;
      if (regno == CC_REGNUM)
	return CC_REG;
      if (regno < 8)
	return LO_REGS;
      return HI_REGS;
    }

  if (   regno <= LAST_ARM_REGNUM
      || regno == FRAME_POINTER_REGNUM
      || regno == ARG_POINTER_REGNUM)
    return GENERAL_REGS;

  if (regno == CC_REGNUM || regno == VFPCC_REGNUM)
    return NO_REGS;

  if (IS_CIRRUS_REGNUM (regno))
    return CIRRUS_REGS;

  if (IS_VFP_REGNUM (regno))
    return VFP_REGS;

  if (IS_IWMMXT_REGNUM (regno))
    return IWMMXT_REGS;

  if (IS_IWMMXT_GR_REGNUM (regno))
    return IWMMXT_GR_REGS;

  return FPA_REGS;
}