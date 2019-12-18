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
#define  AND 143 
#define  ASM_OPERANDS 142 
 scalar_t__ ASM_OPERANDS_INPUT (scalar_t__,int) ; 
 int /*<<< orphan*/  ASM_OPERANDS_INPUT_CONSTRAINT (scalar_t__,int) ; 
 int /*<<< orphan*/  ASM_OPERANDS_INPUT_LENGTH (scalar_t__) ; 
 int /*<<< orphan*/  ASM_OPERANDS_OUTPUT_CONSTRAINT (scalar_t__) ; 
 int /*<<< orphan*/  ASM_OPERANDS_OUTPUT_IDX (scalar_t__) ; 
 int /*<<< orphan*/  ASM_OPERANDS_TEMPLATE (scalar_t__) ; 
#define  CC0 141 
#define  CONST_DOUBLE 140 
#define  CONST_INT 139 
#define  EQ 138 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 int GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  IOR 137 
#define  LABEL_REF 136 
#define  MEM 135 
 int /*<<< orphan*/  MEM_ATTRS (scalar_t__) ; 
 int /*<<< orphan*/  MEM_VOLATILE_P (scalar_t__) ; 
#define  MULT 134 
#define  NE 133 
#define  PC 132 
#define  PLUS 131 
#define  REG 130 
 unsigned int REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_IN_TABLE (unsigned int) ; 
 int /*<<< orphan*/  REG_QTY (unsigned int) ; 
 int /*<<< orphan*/  REG_TICK (unsigned int) ; 
#define  SYMBOL_REF 129 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  XINT (scalar_t__,int) ; 
#define  XOR 128 
 int /*<<< orphan*/  XSTR (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 int /*<<< orphan*/  XWINT (scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int** hard_regno_nregs ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
exp_equiv_p (rtx x, rtx y, int validate, bool for_gcse)
{
  int i, j;
  enum rtx_code code;
  const char *fmt;

  /* Note: it is incorrect to assume an expression is equivalent to itself
     if VALIDATE is nonzero.  */
  if (x == y && !validate)
    return 1;

  if (x == 0 || y == 0)
    return x == y;

  code = GET_CODE (x);
  if (code != GET_CODE (y))
    return 0;

  /* (MULT:SI x y) and (MULT:HI x y) are NOT equivalent.  */
  if (GET_MODE (x) != GET_MODE (y))
    return 0;

  switch (code)
    {
    case PC:
    case CC0:
    case CONST_INT:
    case CONST_DOUBLE:
      return x == y;

    case LABEL_REF:
      return XEXP (x, 0) == XEXP (y, 0);

    case SYMBOL_REF:
      return XSTR (x, 0) == XSTR (y, 0);

    case REG:
      if (for_gcse)
	return REGNO (x) == REGNO (y);
      else
	{
	  unsigned int regno = REGNO (y);
	  unsigned int i;
	  unsigned int endregno
	    = regno + (regno >= FIRST_PSEUDO_REGISTER ? 1
		       : hard_regno_nregs[regno][GET_MODE (y)]);

	  /* If the quantities are not the same, the expressions are not
	     equivalent.  If there are and we are not to validate, they
	     are equivalent.  Otherwise, ensure all regs are up-to-date.  */

	  if (REG_QTY (REGNO (x)) != REG_QTY (regno))
	    return 0;

	  if (! validate)
	    return 1;

	  for (i = regno; i < endregno; i++)
	    if (REG_IN_TABLE (i) != REG_TICK (i))
	      return 0;

	  return 1;
	}

    case MEM:
      if (for_gcse)
	{
	  /* A volatile mem should not be considered equivalent to any
	     other.  */
	  if (MEM_VOLATILE_P (x) || MEM_VOLATILE_P (y))
	    return 0;

	  /* Can't merge two expressions in different alias sets, since we
	     can decide that the expression is transparent in a block when
	     it isn't, due to it being set with the different alias set.

	     Also, can't merge two expressions with different MEM_ATTRS.
	     They could e.g. be two different entities allocated into the
	     same space on the stack (see e.g. PR25130).  In that case, the
	     MEM addresses can be the same, even though the two MEMs are
	     absolutely not equivalent.  
   
	     But because really all MEM attributes should be the same for
	     equivalent MEMs, we just use the invariant that MEMs that have
	     the same attributes share the same mem_attrs data structure.  */
	  if (MEM_ATTRS (x) != MEM_ATTRS (y))
	    return 0;
	}
      break;

    /*  For commutative operations, check both orders.  */
    case PLUS:
    case MULT:
    case AND:
    case IOR:
    case XOR:
    case NE:
    case EQ:
      return ((exp_equiv_p (XEXP (x, 0), XEXP (y, 0),
			     validate, for_gcse)
	       && exp_equiv_p (XEXP (x, 1), XEXP (y, 1),
				validate, for_gcse))
	      || (exp_equiv_p (XEXP (x, 0), XEXP (y, 1),
				validate, for_gcse)
		  && exp_equiv_p (XEXP (x, 1), XEXP (y, 0),
				   validate, for_gcse)));

    case ASM_OPERANDS:
      /* We don't use the generic code below because we want to
	 disregard filename and line numbers.  */

      /* A volatile asm isn't equivalent to any other.  */
      if (MEM_VOLATILE_P (x) || MEM_VOLATILE_P (y))
	return 0;

      if (GET_MODE (x) != GET_MODE (y)
	  || strcmp (ASM_OPERANDS_TEMPLATE (x), ASM_OPERANDS_TEMPLATE (y))
	  || strcmp (ASM_OPERANDS_OUTPUT_CONSTRAINT (x),
		     ASM_OPERANDS_OUTPUT_CONSTRAINT (y))
	  || ASM_OPERANDS_OUTPUT_IDX (x) != ASM_OPERANDS_OUTPUT_IDX (y)
	  || ASM_OPERANDS_INPUT_LENGTH (x) != ASM_OPERANDS_INPUT_LENGTH (y))
	return 0;

      if (ASM_OPERANDS_INPUT_LENGTH (x))
	{
	  for (i = ASM_OPERANDS_INPUT_LENGTH (x) - 1; i >= 0; i--)
	    if (! exp_equiv_p (ASM_OPERANDS_INPUT (x, i),
			       ASM_OPERANDS_INPUT (y, i),
			       validate, for_gcse)
		|| strcmp (ASM_OPERANDS_INPUT_CONSTRAINT (x, i),
			   ASM_OPERANDS_INPUT_CONSTRAINT (y, i)))
	      return 0;
	}

      return 1;

    default:
      break;
    }

  /* Compare the elements.  If any pair of corresponding elements
     fail to match, return 0 for the whole thing.  */

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      switch (fmt[i])
	{
	case 'e':
	  if (! exp_equiv_p (XEXP (x, i), XEXP (y, i),
			      validate, for_gcse))
	    return 0;
	  break;

	case 'E':
	  if (XVECLEN (x, i) != XVECLEN (y, i))
	    return 0;
	  for (j = 0; j < XVECLEN (x, i); j++)
	    if (! exp_equiv_p (XVECEXP (x, i, j), XVECEXP (y, i, j),
				validate, for_gcse))
	      return 0;
	  break;

	case 's':
	  if (strcmp (XSTR (x, i), XSTR (y, i)))
	    return 0;
	  break;

	case 'i':
	  if (XINT (x, i) != XINT (y, i))
	    return 0;
	  break;

	case 'w':
	  if (XWINT (x, i) != XWINT (y, i))
	    return 0;
	  break;

	case '0':
	case 't':
	  break;

	default:
	  gcc_unreachable ();
	}
    }

  return 1;
}