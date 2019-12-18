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
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  BB_END (int /*<<< orphan*/ ) ; 
 scalar_t__ COMPARISON_P (int /*<<< orphan*/ ) ; 
#define  CONST_INT 138 
#define  EQ 137 
 int /*<<< orphan*/  FLOAT_MODE_P (int /*<<< orphan*/ ) ; 
#define  GE 136 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
#define  GT 135 
#define  LE 134 
#define  LT 133 
#define  LTGT 132 
#define  NE 131 
 int /*<<< orphan*/  NOT_TAKEN ; 
#define  ORDERED 130 
 int /*<<< orphan*/  PRED_FPOPCODE ; 
 int /*<<< orphan*/  PRED_OPCODE_NONEQUAL ; 
 int /*<<< orphan*/  PRED_OPCODE_POSITIVE ; 
 int /*<<< orphan*/  PRED_POINTER ; 
 int /*<<< orphan*/  PRED_UNCONDITIONAL ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAKEN ; 
#define  UNEQ 129 
#define  UNORDERED 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  can_predict_insn_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  const1_rtx ; 
 int /*<<< orphan*/  constm1_rtx ; 
 int /*<<< orphan*/  get_condition (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  predict_insn_def (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bb_estimate_probability_locally (basic_block bb)
{
  rtx last_insn = BB_END (bb);
  rtx cond;

  if (! can_predict_insn_p (last_insn))
    return;
  cond = get_condition (last_insn, NULL, false, false);
  if (! cond)
    return;

  /* Try "pointer heuristic."
     A comparison ptr == 0 is predicted as false.
     Similarly, a comparison ptr1 == ptr2 is predicted as false.  */
  if (COMPARISON_P (cond)
      && ((REG_P (XEXP (cond, 0)) && REG_POINTER (XEXP (cond, 0)))
	  || (REG_P (XEXP (cond, 1)) && REG_POINTER (XEXP (cond, 1)))))
    {
      if (GET_CODE (cond) == EQ)
	predict_insn_def (last_insn, PRED_POINTER, NOT_TAKEN);
      else if (GET_CODE (cond) == NE)
	predict_insn_def (last_insn, PRED_POINTER, TAKEN);
    }
  else

  /* Try "opcode heuristic."
     EQ tests are usually false and NE tests are usually true. Also,
     most quantities are positive, so we can make the appropriate guesses
     about signed comparisons against zero.  */
    switch (GET_CODE (cond))
      {
      case CONST_INT:
	/* Unconditional branch.  */
	predict_insn_def (last_insn, PRED_UNCONDITIONAL,
			  cond == const0_rtx ? NOT_TAKEN : TAKEN);
	break;

      case EQ:
      case UNEQ:
	/* Floating point comparisons appears to behave in a very
	   unpredictable way because of special role of = tests in
	   FP code.  */
	if (FLOAT_MODE_P (GET_MODE (XEXP (cond, 0))))
	  ;
	/* Comparisons with 0 are often used for booleans and there is
	   nothing useful to predict about them.  */
	else if (XEXP (cond, 1) == const0_rtx
		 || XEXP (cond, 0) == const0_rtx)
	  ;
	else
	  predict_insn_def (last_insn, PRED_OPCODE_NONEQUAL, NOT_TAKEN);
	break;

      case NE:
      case LTGT:
	/* Floating point comparisons appears to behave in a very
	   unpredictable way because of special role of = tests in
	   FP code.  */
	if (FLOAT_MODE_P (GET_MODE (XEXP (cond, 0))))
	  ;
	/* Comparisons with 0 are often used for booleans and there is
	   nothing useful to predict about them.  */
	else if (XEXP (cond, 1) == const0_rtx
		 || XEXP (cond, 0) == const0_rtx)
	  ;
	else
	  predict_insn_def (last_insn, PRED_OPCODE_NONEQUAL, TAKEN);
	break;

      case ORDERED:
	predict_insn_def (last_insn, PRED_FPOPCODE, TAKEN);
	break;

      case UNORDERED:
	predict_insn_def (last_insn, PRED_FPOPCODE, NOT_TAKEN);
	break;

      case LE:
      case LT:
	if (XEXP (cond, 1) == const0_rtx || XEXP (cond, 1) == const1_rtx
	    || XEXP (cond, 1) == constm1_rtx)
	  predict_insn_def (last_insn, PRED_OPCODE_POSITIVE, NOT_TAKEN);
	break;

      case GE:
      case GT:
	if (XEXP (cond, 1) == const0_rtx || XEXP (cond, 1) == const1_rtx
	    || XEXP (cond, 1) == constm1_rtx)
	  predict_insn_def (last_insn, PRED_OPCODE_POSITIVE, TAKEN);
	break;

      default:
	break;
      }
}