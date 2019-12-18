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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 int /*<<< orphan*/  CCmode ; 
 int EQ ; 
 int /*<<< orphan*/  FPSW_REGNUM ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ ISA_HAS_8CC ; 
 scalar_t__ MODE_INT ; 
 int NE ; 
 scalar_t__* cmp_operands ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ force_reg (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_emit_binary (int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mips_emit_int_relational (int,int*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ mips_reverse_fp_cond_p (int*) ; 
 scalar_t__ mips_zero_if_equal (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
mips_emit_compare (enum rtx_code *code, rtx *op0, rtx *op1, bool need_eq_ne_p)
{
  if (GET_MODE_CLASS (GET_MODE (cmp_operands[0])) == MODE_INT)
    {
      if (!need_eq_ne_p && cmp_operands[1] == const0_rtx)
	{
	  *op0 = cmp_operands[0];
	  *op1 = cmp_operands[1];
	}
      else if (*code == EQ || *code == NE)
	{
	  if (need_eq_ne_p)
	    {
	      *op0 = mips_zero_if_equal (cmp_operands[0], cmp_operands[1]);
	      *op1 = const0_rtx;
	    }
	  else
	    {
	      *op0 = cmp_operands[0];
	      *op1 = force_reg (GET_MODE (*op0), cmp_operands[1]);
	    }
	}
      else
	{
	  /* The comparison needs a separate scc instruction.  Store the
	     result of the scc in *OP0 and compare it against zero.  */
	  bool invert = false;
	  *op0 = gen_reg_rtx (GET_MODE (cmp_operands[0]));
	  *op1 = const0_rtx;
	  mips_emit_int_relational (*code, &invert, *op0,
				    cmp_operands[0], cmp_operands[1]);
	  *code = (invert ? EQ : NE);
	}
    }
  else
    {
      enum rtx_code cmp_code;

      /* Floating-point tests use a separate c.cond.fmt comparison to
	 set a condition code register.  The branch or conditional move
	 will then compare that register against zero.

	 Set CMP_CODE to the code of the comparison instruction and
	 *CODE to the code that the branch or move should use.  */
      cmp_code = *code;
      *code = mips_reverse_fp_cond_p (&cmp_code) ? EQ : NE;
      *op0 = (ISA_HAS_8CC
	      ? gen_reg_rtx (CCmode)
	      : gen_rtx_REG (CCmode, FPSW_REGNUM));
      *op1 = const0_rtx;
      mips_emit_binary (cmp_code, *op0, cmp_operands[0], cmp_operands[1]);
    }
}