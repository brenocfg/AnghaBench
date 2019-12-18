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
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM ; 
 scalar_t__ PLUS ; 
 scalar_t__ REG ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_asm_insn (char*,int /*<<< orphan*/ *) ; 

const char *
arm_output_load_gr (rtx *operands)
{
  rtx reg;
  rtx offset;
  rtx wcgr;
  rtx sum;

  if (GET_CODE (operands [1]) != MEM
      || GET_CODE (sum = XEXP (operands [1], 0)) != PLUS
      || GET_CODE (reg = XEXP (sum, 0)) != REG
      || GET_CODE (offset = XEXP (sum, 1)) != CONST_INT
      || ((INTVAL (offset) < 1024) && (INTVAL (offset) > -1024)))
    return "wldrw%?\t%0, %1";

  /* Fix up an out-of-range load of a GR register.  */
  output_asm_insn ("str%?\t%0, [sp, #-4]!\t@ Start of GR load expansion", & reg);
  wcgr = operands[0];
  operands[0] = reg;
  output_asm_insn ("ldr%?\t%0, %1", operands);

  operands[0] = wcgr;
  operands[1] = reg;
  output_asm_insn ("tmcr%?\t%0, %1", operands);
  output_asm_insn ("ldr%?\t%0, [sp], #4\t@ End of GR load expansion", & reg);

  return "";
}