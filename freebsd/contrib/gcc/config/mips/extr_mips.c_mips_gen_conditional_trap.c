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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GE ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int GEU ; 
#define  GT 131 
#define  GTU 130 
#define  LE 129 
#define  LEU 128 
 int LT ; 
 int LTU ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  arith_operand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * cmp_operands ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_TRAP_IF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mips_gen_conditional_trap (rtx *operands)
{
  rtx op0, op1;
  enum rtx_code cmp_code = GET_CODE (operands[0]);
  enum machine_mode mode = GET_MODE (cmp_operands[0]);

  /* MIPS conditional trap machine instructions don't have GT or LE
     flavors, so we must invert the comparison and convert to LT and
     GE, respectively.  */
  switch (cmp_code)
    {
    case GT: cmp_code = LT; break;
    case LE: cmp_code = GE; break;
    case GTU: cmp_code = LTU; break;
    case LEU: cmp_code = GEU; break;
    default: break;
    }
  if (cmp_code == GET_CODE (operands[0]))
    {
      op0 = cmp_operands[0];
      op1 = cmp_operands[1];
    }
  else
    {
      op0 = cmp_operands[1];
      op1 = cmp_operands[0];
    }
  op0 = force_reg (mode, op0);
  if (!arith_operand (op1, mode))
    op1 = force_reg (mode, op1);

  emit_insn (gen_rtx_TRAP_IF (VOIDmode,
			      gen_rtx_fmt_ee (cmp_code, mode, op0, op1),
			      operands[1]));
}