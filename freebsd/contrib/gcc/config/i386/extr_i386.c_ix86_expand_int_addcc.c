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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CCFPUmode ; 
 scalar_t__ CCFPmode ; 
#define  DImode 131 
 int GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
#define  HImode 130 
 int LTU ; 
 int /*<<< orphan*/  PUT_CODE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_MODE (scalar_t__,int) ; 
#define  QImode 129 
#define  SImode 128 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ const1_rtx ; 
 scalar_t__ constm1_rtx ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_adddi3_carry_rex64 (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_addhi3_carry (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_addqi3_carry (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_addsi3_carry (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_subdi3_carry_rex64 (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_subhi3_carry (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_subqi3_carry (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_subsi3_carry (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ix86_compare_op0 ; 
 int /*<<< orphan*/  ix86_compare_op1 ; 
 int /*<<< orphan*/  ix86_expand_carry_flag_compare (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int ix86_fp_compare_code_to_integer (int) ; 
 int /*<<< orphan*/  reverse_condition (int) ; 
 int /*<<< orphan*/  reverse_condition_maybe_unordered (int) ; 

int
ix86_expand_int_addcc (rtx operands[])
{
  enum rtx_code code = GET_CODE (operands[1]);
  rtx compare_op;
  rtx val = const0_rtx;
  bool fpcmp = false;
  enum machine_mode mode = GET_MODE (operands[0]);

  if (operands[3] != const1_rtx
      && operands[3] != constm1_rtx)
    return 0;
  if (!ix86_expand_carry_flag_compare (code, ix86_compare_op0,
				       ix86_compare_op1, &compare_op))
     return 0;
  code = GET_CODE (compare_op);

  if (GET_MODE (XEXP (compare_op, 0)) == CCFPmode
      || GET_MODE (XEXP (compare_op, 0)) == CCFPUmode)
    {
      fpcmp = true;
      code = ix86_fp_compare_code_to_integer (code);
    }

  if (code != LTU)
    {
      val = constm1_rtx;
      if (fpcmp)
	PUT_CODE (compare_op,
		  reverse_condition_maybe_unordered
		    (GET_CODE (compare_op)));
      else
	PUT_CODE (compare_op, reverse_condition (GET_CODE (compare_op)));
    }
  PUT_MODE (compare_op, mode);

  /* Construct either adc or sbb insn.  */
  if ((code == LTU) == (operands[3] == constm1_rtx))
    {
      switch (GET_MODE (operands[0]))
	{
	  case QImode:
            emit_insn (gen_subqi3_carry (operands[0], operands[2], val, compare_op));
	    break;
	  case HImode:
            emit_insn (gen_subhi3_carry (operands[0], operands[2], val, compare_op));
	    break;
	  case SImode:
            emit_insn (gen_subsi3_carry (operands[0], operands[2], val, compare_op));
	    break;
	  case DImode:
            emit_insn (gen_subdi3_carry_rex64 (operands[0], operands[2], val, compare_op));
	    break;
	  default:
	    gcc_unreachable ();
	}
    }
  else
    {
      switch (GET_MODE (operands[0]))
	{
	  case QImode:
            emit_insn (gen_addqi3_carry (operands[0], operands[2], val, compare_op));
	    break;
	  case HImode:
            emit_insn (gen_addhi3_carry (operands[0], operands[2], val, compare_op));
	    break;
	  case SImode:
            emit_insn (gen_addsi3_carry (operands[0], operands[2], val, compare_op));
	    break;
	  case DImode:
            emit_insn (gen_adddi3_carry_rex64 (operands[0], operands[2], val, compare_op));
	    break;
	  default:
	    gcc_unreachable ();
	}
    }
  return 1; /* DONE */
}