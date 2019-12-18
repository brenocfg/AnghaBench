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
 int /*<<< orphan*/  IP_REGNUM ; 
 scalar_t__ LR_REGNUM ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SImode ; 
 scalar_t__ TARGET_INTERWORK ; 
 scalar_t__ arm_arch4t ; 
 int /*<<< orphan*/  arm_arch5 ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_asm_insn (char*,int /*<<< orphan*/ *) ; 

const char *
output_call (rtx *operands)
{
  gcc_assert (!arm_arch5); /* Patterns should call blx <reg> directly.  */

  /* Handle calls to lr using ip (which may be clobbered in subr anyway).  */
  if (REGNO (operands[0]) == LR_REGNUM)
    {
      operands[0] = gen_rtx_REG (SImode, IP_REGNUM);
      output_asm_insn ("mov%?\t%0, %|lr", operands);
    }

  output_asm_insn ("mov%?\t%|lr, %|pc", operands);

  if (TARGET_INTERWORK || arm_arch4t)
    output_asm_insn ("bx%?\t%0", operands);
  else
    output_asm_insn ("mov%?\t%|pc, %0", operands);

  return "";
}