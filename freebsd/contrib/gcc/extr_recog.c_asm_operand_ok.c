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
 int /*<<< orphan*/  BLKmode ; 
 int /*<<< orphan*/  CONSTANT_P (int /*<<< orphan*/ ) ; 
 int CONSTRAINT_LEN (char,char const*) ; 
 int /*<<< orphan*/  CONST_DOUBLE ; 
 int /*<<< orphan*/  CONST_DOUBLE_OK_FOR_CONSTRAINT_P (int /*<<< orphan*/ ,char,char const*) ; 
 int /*<<< orphan*/  CONST_INT ; 
 int /*<<< orphan*/  CONST_OK_FOR_CONSTRAINT_P (int /*<<< orphan*/ ,char,char const*) ; 
 int /*<<< orphan*/  CONST_VECTOR ; 
 int /*<<< orphan*/  EXTRA_ADDRESS_CONSTRAINT (char,char const*) ; 
 int /*<<< orphan*/  EXTRA_CONSTRAINT_STR (int /*<<< orphan*/ ,char,char const*) ; 
 int /*<<< orphan*/  EXTRA_MEMORY_CONSTRAINT (char,char const*) ; 
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISDIGIT (char const) ; 
 int /*<<< orphan*/  LEGITIMATE_PIC_OPERAND_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODE_VECTOR_FLOAT ; 
 int /*<<< orphan*/  NO_REGS ; 
 int /*<<< orphan*/  POST_DEC ; 
 int /*<<< orphan*/  POST_INC ; 
 int /*<<< orphan*/  PRE_DEC ; 
 int /*<<< orphan*/  PRE_INC ; 
 int /*<<< orphan*/  REG_CLASS_FROM_CONSTRAINT (char,char const*) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  address_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_pic ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  general_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offsettable_nonstrict_memref_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reload_completed ; 

int
asm_operand_ok (rtx op, const char *constraint)
{
  int result = 0;

  /* Use constrain_operands after reload.  */
  gcc_assert (!reload_completed);

  while (*constraint)
    {
      char c = *constraint;
      int len;
      switch (c)
	{
	case ',':
	  constraint++;
	  continue;
	case '=':
	case '+':
	case '*':
	case '%':
	case '!':
	case '#':
	case '&':
	case '?':
	  break;

	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	  /* For best results, our caller should have given us the
	     proper matching constraint, but we can't actually fail
	     the check if they didn't.  Indicate that results are
	     inconclusive.  */
	  do
	    constraint++;
	  while (ISDIGIT (*constraint));
	  if (! result)
	    result = -1;
	  continue;

	case 'p':
	  if (address_operand (op, VOIDmode))
	    result = 1;
	  break;

	case 'm':
	case 'V': /* non-offsettable */
	  if (memory_operand (op, VOIDmode))
	    result = 1;
	  break;

	case 'o': /* offsettable */
	  if (offsettable_nonstrict_memref_p (op))
	    result = 1;
	  break;

	case '<':
	  /* ??? Before flow, auto inc/dec insns are not supposed to exist,
	     excepting those that expand_call created.  Further, on some
	     machines which do not have generalized auto inc/dec, an inc/dec
	     is not a memory_operand.

	     Match any memory and hope things are resolved after reload.  */

	  if (MEM_P (op)
	      && (1
		  || GET_CODE (XEXP (op, 0)) == PRE_DEC
		  || GET_CODE (XEXP (op, 0)) == POST_DEC))
	    result = 1;
	  break;

	case '>':
	  if (MEM_P (op)
	      && (1
		  || GET_CODE (XEXP (op, 0)) == PRE_INC
		  || GET_CODE (XEXP (op, 0)) == POST_INC))
	    result = 1;
	  break;

	case 'E':
	case 'F':
	  if (GET_CODE (op) == CONST_DOUBLE
	      || (GET_CODE (op) == CONST_VECTOR
		  && GET_MODE_CLASS (GET_MODE (op)) == MODE_VECTOR_FLOAT))
	    result = 1;
	  break;

	case 'G':
	  if (GET_CODE (op) == CONST_DOUBLE
	      && CONST_DOUBLE_OK_FOR_CONSTRAINT_P (op, 'G', constraint))
	    result = 1;
	  break;
	case 'H':
	  if (GET_CODE (op) == CONST_DOUBLE
	      && CONST_DOUBLE_OK_FOR_CONSTRAINT_P (op, 'H', constraint))
	    result = 1;
	  break;

	case 's':
	  if (GET_CODE (op) == CONST_INT
	      || (GET_CODE (op) == CONST_DOUBLE
		  && GET_MODE (op) == VOIDmode))
	    break;
	  /* Fall through.  */

	case 'i':
	  if (CONSTANT_P (op) && (! flag_pic || LEGITIMATE_PIC_OPERAND_P (op)))
	    result = 1;
	  break;

	case 'n':
	  if (GET_CODE (op) == CONST_INT
	      || (GET_CODE (op) == CONST_DOUBLE
		  && GET_MODE (op) == VOIDmode))
	    result = 1;
	  break;

	case 'I':
	  if (GET_CODE (op) == CONST_INT
	      && CONST_OK_FOR_CONSTRAINT_P (INTVAL (op), 'I', constraint))
	    result = 1;
	  break;
	case 'J':
	  if (GET_CODE (op) == CONST_INT
	      && CONST_OK_FOR_CONSTRAINT_P (INTVAL (op), 'J', constraint))
	    result = 1;
	  break;
	case 'K':
	  if (GET_CODE (op) == CONST_INT
	      && CONST_OK_FOR_CONSTRAINT_P (INTVAL (op), 'K', constraint))
	    result = 1;
	  break;
	case 'L':
	  if (GET_CODE (op) == CONST_INT
	      && CONST_OK_FOR_CONSTRAINT_P (INTVAL (op), 'L', constraint))
	    result = 1;
	  break;
	case 'M':
	  if (GET_CODE (op) == CONST_INT
	      && CONST_OK_FOR_CONSTRAINT_P (INTVAL (op), 'M', constraint))
	    result = 1;
	  break;
	case 'N':
	  if (GET_CODE (op) == CONST_INT
	      && CONST_OK_FOR_CONSTRAINT_P (INTVAL (op), 'N', constraint))
	    result = 1;
	  break;
	case 'O':
	  if (GET_CODE (op) == CONST_INT
	      && CONST_OK_FOR_CONSTRAINT_P (INTVAL (op), 'O', constraint))
	    result = 1;
	  break;
	case 'P':
	  if (GET_CODE (op) == CONST_INT
	      && CONST_OK_FOR_CONSTRAINT_P (INTVAL (op), 'P', constraint))
	    result = 1;
	  break;

	case 'X':
	  result = 1;
	  break;

	case 'g':
	  if (general_operand (op, VOIDmode))
	    result = 1;
	  break;

	default:
	  /* For all other letters, we first check for a register class,
	     otherwise it is an EXTRA_CONSTRAINT.  */
	  if (REG_CLASS_FROM_CONSTRAINT (c, constraint) != NO_REGS)
	    {
	    case 'r':
	      if (GET_MODE (op) == BLKmode)
		break;
	      if (register_operand (op, VOIDmode))
		result = 1;
	    }
#ifdef EXTRA_CONSTRAINT_STR
	  else if (EXTRA_CONSTRAINT_STR (op, c, constraint))
	    result = 1;
	  else if (EXTRA_MEMORY_CONSTRAINT (c, constraint)
		   /* Every memory operand can be reloaded to fit.  */
		   && memory_operand (op, VOIDmode))
	    result = 1;
	  else if (EXTRA_ADDRESS_CONSTRAINT (c, constraint)
		   /* Every address operand can be reloaded to fit.  */
		   && address_operand (op, VOIDmode))
	    result = 1;
#endif
	  break;
	}
      len = CONSTRAINT_LEN (c, constraint);
      do
	constraint++;
      while (--len && *constraint);
      if (len)
	return 0;
    }

  return result;
}