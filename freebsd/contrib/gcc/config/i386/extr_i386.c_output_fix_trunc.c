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
 scalar_t__ DImode ; 
 int /*<<< orphan*/  FIRST_STACK_REG ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int I387_CW_ANY ; 
 scalar_t__ MEM ; 
 int /*<<< orphan*/  REG_DEAD ; 
 int STACK_TOP_P (int /*<<< orphan*/ ) ; 
 scalar_t__ find_regno_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int get_attr_i387_cw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_asm_insn (char*,int /*<<< orphan*/ *) ; 

const char *
output_fix_trunc (rtx insn, rtx *operands, int fisttp)
{
  int stack_top_dies = find_regno_note (insn, REG_DEAD, FIRST_STACK_REG) != 0;
  int dimode_p = GET_MODE (operands[0]) == DImode;
  int round_mode = get_attr_i387_cw (insn);

  /* Jump through a hoop or two for DImode, since the hardware has no
     non-popping instruction.  We used to do this a different way, but
     that was somewhat fragile and broke with post-reload splitters.  */
  if ((dimode_p || fisttp) && !stack_top_dies)
    output_asm_insn ("fld\t%y1", operands);

  gcc_assert (STACK_TOP_P (operands[1]));
  gcc_assert (GET_CODE (operands[0]) == MEM);

  if (fisttp)
      output_asm_insn ("fisttp%z0\t%0", operands);
  else
    {
      if (round_mode != I387_CW_ANY)
	output_asm_insn ("fldcw\t%3", operands);
      if (stack_top_dies || dimode_p)
	output_asm_insn ("fistp%z0\t%0", operands);
      else
	output_asm_insn ("fist%z0\t%0", operands);
      if (round_mode != I387_CW_ANY)
	output_asm_insn ("fldcw\t%2", operands);
    }

  return "";
}