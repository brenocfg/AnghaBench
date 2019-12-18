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
#define  ASM_OPERANDS 144 
 scalar_t__ ASM_OPERANDS_INPUT (scalar_t__,int) ; 
 int /*<<< orphan*/  ASM_OPERANDS_INPUT_LENGTH (scalar_t__) ; 
#define  CALL_INSN 143 
 scalar_t__ CALL_INSN_FUNCTION_USAGE (scalar_t__) ; 
#define  CC0 142 
#define  CLOBBER 141 
#define  CONST 140 
#define  CONST_DOUBLE 139 
#define  CONST_INT 138 
#define  CONST_VECTOR 137 
#define  EXPR_LIST 136 
 int const GET_CODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  INSN 135 
#define  INSN_LIST 134 
#define  JUMP_INSN 133 
#define  LABEL_REF 132 
 int /*<<< orphan*/  MEM_P (scalar_t__) ; 
 int /*<<< orphan*/  MEM_VOLATILE_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PATTERN (scalar_t__) ; 
#define  PC 131 
#define  REG 130 
 size_t REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_EQUAL ; 
 int /*<<< orphan*/  REG_NONNEG ; 
 int /*<<< orphan*/  REG_NOTE_KIND (scalar_t__) ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
#define  SET 129 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
#define  SYMBOL_REF 128 
 int const USE ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 scalar_t__ find_reg_equal_equiv_note (scalar_t__) ; 
 int /*<<< orphan*/  flag_non_call_exceptions ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  may_trap_p (scalar_t__) ; 
 scalar_t__ pc_rtx ; 

__attribute__((used)) static void
count_reg_usage (rtx x, int *counts, rtx dest, int incr)
{
  enum rtx_code code;
  rtx note;
  const char *fmt;
  int i, j;

  if (x == 0)
    return;

  switch (code = GET_CODE (x))
    {
    case REG:
      if (x != dest)
	counts[REGNO (x)] += incr;
      return;

    case PC:
    case CC0:
    case CONST:
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case SYMBOL_REF:
    case LABEL_REF:
      return;

    case CLOBBER:
      /* If we are clobbering a MEM, mark any registers inside the address
         as being used.  */
      if (MEM_P (XEXP (x, 0)))
	count_reg_usage (XEXP (XEXP (x, 0), 0), counts, NULL_RTX, incr);
      return;

    case SET:
      /* Unless we are setting a REG, count everything in SET_DEST.  */
      if (!REG_P (SET_DEST (x)))
	count_reg_usage (SET_DEST (x), counts, NULL_RTX, incr);
      count_reg_usage (SET_SRC (x), counts,
		       dest ? dest : SET_DEST (x),
		       incr);
      return;

    case CALL_INSN:
    case INSN:
    case JUMP_INSN:
    /* We expect dest to be NULL_RTX here.  If the insn may trap, mark
       this fact by setting DEST to pc_rtx.  */
      if (flag_non_call_exceptions && may_trap_p (PATTERN (x)))
	dest = pc_rtx;
      if (code == CALL_INSN)
	count_reg_usage (CALL_INSN_FUNCTION_USAGE (x), counts, dest, incr);
      count_reg_usage (PATTERN (x), counts, dest, incr);

      /* Things used in a REG_EQUAL note aren't dead since loop may try to
	 use them.  */

      note = find_reg_equal_equiv_note (x);
      if (note)
	{
	  rtx eqv = XEXP (note, 0);

	  if (GET_CODE (eqv) == EXPR_LIST)
	  /* This REG_EQUAL note describes the result of a function call.
	     Process all the arguments.  */
	    do
	      {
		count_reg_usage (XEXP (eqv, 0), counts, dest, incr);
		eqv = XEXP (eqv, 1);
	      }
	    while (eqv && GET_CODE (eqv) == EXPR_LIST);
	  else
	    count_reg_usage (eqv, counts, dest, incr);
	}
      return;

    case EXPR_LIST:
      if (REG_NOTE_KIND (x) == REG_EQUAL
	  || (REG_NOTE_KIND (x) != REG_NONNEG && GET_CODE (XEXP (x,0)) == USE)
	  /* FUNCTION_USAGE expression lists may include (CLOBBER (mem /u)),
	     involving registers in the address.  */
	  || GET_CODE (XEXP (x, 0)) == CLOBBER)
	count_reg_usage (XEXP (x, 0), counts, NULL_RTX, incr);

      count_reg_usage (XEXP (x, 1), counts, NULL_RTX, incr);
      return;

    case ASM_OPERANDS:
      /* If the asm is volatile, then this insn cannot be deleted,
	 and so the inputs *must* be live.  */
      if (MEM_VOLATILE_P (x))
	dest = NULL_RTX;
      /* Iterate over just the inputs, not the constraints as well.  */
      for (i = ASM_OPERANDS_INPUT_LENGTH (x) - 1; i >= 0; i--)
	count_reg_usage (ASM_OPERANDS_INPUT (x, i), counts, dest, incr);
      return;

    case INSN_LIST:
      gcc_unreachable ();

    default:
      break;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	count_reg_usage (XEXP (x, i), counts, dest, incr);
      else if (fmt[i] == 'E')
	for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	  count_reg_usage (XVECEXP (x, i, j), counts, dest, incr);
    }
}