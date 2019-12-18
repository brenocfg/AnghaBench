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
 int IP_REGNUM ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_asm_insn (char*,int /*<<< orphan*/ *) ; 

const char *
output_mov_long_double_fpa_from_arm (rtx *operands)
{
  int arm_reg0 = REGNO (operands[1]);
  rtx ops[3];

  gcc_assert (arm_reg0 != IP_REGNUM);

  ops[0] = gen_rtx_REG (SImode, arm_reg0);
  ops[1] = gen_rtx_REG (SImode, 1 + arm_reg0);
  ops[2] = gen_rtx_REG (SImode, 2 + arm_reg0);

  output_asm_insn ("stm%?fd\t%|sp!, {%0, %1, %2}", ops);
  output_asm_insn ("ldf%?e\t%0, [%|sp], #12", operands);

  return "";
}