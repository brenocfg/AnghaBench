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
typedef  void* rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CCFPUmode ; 
 scalar_t__ CCFPmode ; 
 int CONST_INT ; 
 int DImode ; 
#define  EQ 137 
 scalar_t__ FLOAT_MODE_P (int) ; 
#define  GE 136 
 int GET_CODE (void*) ; 
 int GET_MODE (void*) ; 
 int /*<<< orphan*/  GET_MODE_BITSIZE (int) ; 
#define  GEU 135 
#define  GT 134 
#define  GTU 133 
 int /*<<< orphan*/  INTEGRAL_MODE_P (int) ; 
 int /*<<< orphan*/  INTVAL (void*) ; 
#define  LE 132 
#define  LEU 131 
#define  LT 130 
 int LTGT ; 
#define  LTU 129 
#define  NE 128 
 int /*<<< orphan*/  NULL_RTX ; 
 int ORDERED ; 
 scalar_t__ TARGET_64BIT ; 
 int /*<<< orphan*/  TARGET_IEEE_FP ; 
 int TImode ; 
 int UNEQ ; 
 int UNGT ; 
 int UNLE ; 
 int UNORDERED ; 
 scalar_t__ VOIDmode ; 
 void* XEXP (void*,int /*<<< orphan*/ ) ; 
 void* const0_rtx ; 
 void* const1_rtx ; 
 void* constm1_rtx ; 
 int /*<<< orphan*/  emit_insn (void*) ; 
 int /*<<< orphan*/  end_sequence () ; 
 void* force_reg (int,void*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 void* gen_int_mode (int,int) ; 
 void* get_insns () ; 
 void* ix86_compare_op0 ; 
 void* ix86_compare_op1 ; 
 void* ix86_expand_compare (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* ix86_expand_fp_compare (int,void*,void*,int /*<<< orphan*/ ,void**,void**) ; 
 int ix86_fp_compare_code_to_integer (int) ; 
 scalar_t__ no_new_pseudos ; 
 int /*<<< orphan*/  nonimmediate_operand (void*,scalar_t__) ; 
 int /*<<< orphan*/  start_sequence () ; 
 int swap_condition (int) ; 
 int /*<<< orphan*/  x86_64_immediate_operand (void*,int) ; 

__attribute__((used)) static bool
ix86_expand_carry_flag_compare (enum rtx_code code, rtx op0, rtx op1, rtx *pop)
{
  enum machine_mode mode =
    GET_MODE (op0) != VOIDmode ? GET_MODE (op0) : GET_MODE (op1);

  /* Do not handle DImode compares that go through special path.  Also we can't
     deal with FP compares yet.  This is possible to add.  */
  if (mode == (TARGET_64BIT ? TImode : DImode))
    return false;
  if (FLOAT_MODE_P (mode))
    {
      rtx second_test = NULL, bypass_test = NULL;
      rtx compare_op, compare_seq;

      /* Shortcut:  following common codes never translate into carry flag compares.  */
      if (code == EQ || code == NE || code == UNEQ || code == LTGT
	  || code == ORDERED || code == UNORDERED)
	return false;

      /* These comparisons require zero flag; swap operands so they won't.  */
      if ((code == GT || code == UNLE || code == LE || code == UNGT)
	  && !TARGET_IEEE_FP)
	{
	  rtx tmp = op0;
	  op0 = op1;
	  op1 = tmp;
	  code = swap_condition (code);
	}

      /* Try to expand the comparison and verify that we end up with carry flag
	 based comparison.  This is fails to be true only when we decide to expand
	 comparison using arithmetic that is not too common scenario.  */
      start_sequence ();
      compare_op = ix86_expand_fp_compare (code, op0, op1, NULL_RTX,
					   &second_test, &bypass_test);
      compare_seq = get_insns ();
      end_sequence ();

      if (second_test || bypass_test)
	return false;
      if (GET_MODE (XEXP (compare_op, 0)) == CCFPmode
	  || GET_MODE (XEXP (compare_op, 0)) == CCFPUmode)
        code = ix86_fp_compare_code_to_integer (GET_CODE (compare_op));
      else
	code = GET_CODE (compare_op);
      if (code != LTU && code != GEU)
	return false;
      emit_insn (compare_seq);
      *pop = compare_op;
      return true;
    }
  if (!INTEGRAL_MODE_P (mode))
    return false;
  switch (code)
    {
    case LTU:
    case GEU:
      break;

    /* Convert a==0 into (unsigned)a<1.  */
    case EQ:
    case NE:
      if (op1 != const0_rtx)
	return false;
      op1 = const1_rtx;
      code = (code == EQ ? LTU : GEU);
      break;

    /* Convert a>b into b<a or a>=b-1.  */
    case GTU:
    case LEU:
      if (GET_CODE (op1) == CONST_INT)
	{
	  op1 = gen_int_mode (INTVAL (op1) + 1, GET_MODE (op0));
	  /* Bail out on overflow.  We still can swap operands but that
	     would force loading of the constant into register.  */
	  if (op1 == const0_rtx
	      || !x86_64_immediate_operand (op1, GET_MODE (op1)))
	    return false;
	  code = (code == GTU ? GEU : LTU);
	}
      else
	{
	  rtx tmp = op1;
	  op1 = op0;
	  op0 = tmp;
	  code = (code == GTU ? LTU : GEU);
	}
      break;

    /* Convert a>=0 into (unsigned)a<0x80000000.  */
    case LT:
    case GE:
      if (mode == DImode || op1 != const0_rtx)
	return false;
      op1 = gen_int_mode (1 << (GET_MODE_BITSIZE (mode) - 1), mode);
      code = (code == LT ? GEU : LTU);
      break;
    case LE:
    case GT:
      if (mode == DImode || op1 != constm1_rtx)
	return false;
      op1 = gen_int_mode (1 << (GET_MODE_BITSIZE (mode) - 1), mode);
      code = (code == LE ? GEU : LTU);
      break;

    default:
      return false;
    }
  /* Swapping operands may cause constant to appear as first operand.  */
  if (!nonimmediate_operand (op0, VOIDmode))
    {
      if (no_new_pseudos)
	return false;
      op0 = force_reg (mode, op0);
    }
  ix86_compare_op0 = op0;
  ix86_compare_op1 = op1;
  *pop = ix86_expand_compare (code, NULL, NULL);
  gcc_assert (GET_CODE (*pop) == LTU || GET_CODE (*pop) == GEU);
  return true;
}