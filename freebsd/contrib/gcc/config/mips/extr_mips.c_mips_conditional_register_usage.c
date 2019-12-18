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
 scalar_t__ ABI_64 ; 
 scalar_t__ ABI_N32 ; 
 int DSP_ACC_REG_FIRST ; 
 int DSP_ACC_REG_LAST ; 
 int FP_REG_FIRST ; 
 int FP_REG_LAST ; 
 int /*<<< orphan*/  ISA_HAS_8CC ; 
 int ST_REG_FIRST ; 
 int ST_REG_LAST ; 
 int /*<<< orphan*/  TARGET_DSP ; 
 int /*<<< orphan*/  TARGET_HARD_FLOAT ; 
 scalar_t__ TARGET_MIPS16 ; 
 void** call_really_used_regs ; 
 void** call_used_regs ; 
 void** fixed_regs ; 
 scalar_t__ mips_abi ; 

void
mips_conditional_register_usage (void)
{
  if (!TARGET_DSP)
    {
      int regno;

      for (regno = DSP_ACC_REG_FIRST; regno <= DSP_ACC_REG_LAST; regno++)
	fixed_regs[regno] = call_used_regs[regno] = 1;
    }
  if (!TARGET_HARD_FLOAT)
    {
      int regno;

      for (regno = FP_REG_FIRST; regno <= FP_REG_LAST; regno++)
	fixed_regs[regno] = call_used_regs[regno] = 1;
      for (regno = ST_REG_FIRST; regno <= ST_REG_LAST; regno++)
	fixed_regs[regno] = call_used_regs[regno] = 1;
    }
  else if (! ISA_HAS_8CC)
    {
      int regno;

      /* We only have a single condition code register.  We
	 implement this by hiding all the condition code registers,
	 and generating RTL that refers directly to ST_REG_FIRST.  */
      for (regno = ST_REG_FIRST; regno <= ST_REG_LAST; regno++)
	fixed_regs[regno] = call_used_regs[regno] = 1;
    }
  /* In mips16 mode, we permit the $t temporary registers to be used
     for reload.  We prohibit the unused $s registers, since they
     are caller saved, and saving them via a mips16 register would
     probably waste more time than just reloading the value.  */
  if (TARGET_MIPS16)
    {
      fixed_regs[18] = call_used_regs[18] = 1;
      fixed_regs[19] = call_used_regs[19] = 1;
      fixed_regs[20] = call_used_regs[20] = 1;
      fixed_regs[21] = call_used_regs[21] = 1;
      fixed_regs[22] = call_used_regs[22] = 1;
      fixed_regs[23] = call_used_regs[23] = 1;
      fixed_regs[26] = call_used_regs[26] = 1;
      fixed_regs[27] = call_used_regs[27] = 1;
      fixed_regs[30] = call_used_regs[30] = 1;
    }
  /* fp20-23 are now caller saved.  */
  if (mips_abi == ABI_64)
    {
      int regno;
      for (regno = FP_REG_FIRST + 20; regno < FP_REG_FIRST + 24; regno++)
	call_really_used_regs[regno] = call_used_regs[regno] = 1;
    }
  /* Odd registers from fp21 to fp31 are now caller saved.  */
  if (mips_abi == ABI_N32)
    {
      int regno;
      for (regno = FP_REG_FIRST + 21; regno <= FP_REG_FIRST + 31; regno+=2)
	call_really_used_regs[regno] = call_used_regs[regno] = 1;
    }
}