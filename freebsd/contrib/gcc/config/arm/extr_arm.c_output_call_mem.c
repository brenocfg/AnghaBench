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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  LR_REGNUM ; 
 scalar_t__ TARGET_INTERWORK ; 
 scalar_t__ arm_arch4t ; 
 scalar_t__ arm_arch5 ; 
 int /*<<< orphan*/  output_asm_insn (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ regno_use_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *
output_call_mem (rtx *operands)
{
  if (TARGET_INTERWORK && !arm_arch5)
    {
      output_asm_insn ("ldr%?\t%|ip, %0", operands);
      output_asm_insn ("mov%?\t%|lr, %|pc", operands);
      output_asm_insn ("bx%?\t%|ip", operands);
    }
  else if (regno_use_in (LR_REGNUM, operands[0]))
    {
      /* LR is used in the memory address.  We load the address in the
	 first instruction.  It's safe to use IP as the target of the
	 load since the call will kill it anyway.  */
      output_asm_insn ("ldr%?\t%|ip, %0", operands);
      if (arm_arch5)
	output_asm_insn ("blx%?\t%|ip", operands);
      else
	{
	  output_asm_insn ("mov%?\t%|lr, %|pc", operands);
	  if (arm_arch4t)
	    output_asm_insn ("bx%?\t%|ip", operands);
	  else
	    output_asm_insn ("mov%?\t%|pc, %|ip", operands);
	}
    }
  else
    {
      output_asm_insn ("mov%?\t%|lr, %|pc", operands);
      output_asm_insn ("ldr%?\t%|pc, %0", operands);
    }

  return "";
}