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
typedef  scalar_t__ RTX_CODE ;

/* Variables and functions */
#define  CONST_DOUBLE 131 
#define  CONST_INT 130 
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 size_t GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_SIZE (size_t) ; 
 char* GET_RTX_FORMAT (scalar_t__) ; 
 int GET_RTX_LENGTH (scalar_t__) ; 
#define  LABEL_REF 129 
 scalar_t__ POST_DEC ; 
 scalar_t__ POST_INC ; 
 scalar_t__ POST_MODIFY ; 
 scalar_t__ PRE_DEC ; 
 scalar_t__ PRE_INC ; 
 scalar_t__ PRE_MODIFY ; 
 scalar_t__ REG ; 
 int REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ SCALAR_INT_MODE_P (size_t) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_BYTE (scalar_t__) ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
#define  SYMBOL_REF 128 
 scalar_t__ UNITS_PER_WORD ; 
 scalar_t__ WORDS_BIG_ENDIAN ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  XINT (scalar_t__,int) ; 
 int /*<<< orphan*/  XSTR (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int /*<<< orphan*/  XVECLEN (scalar_t__,int) ; 
 int /*<<< orphan*/  XWINT (scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int** hard_regno_nregs ; 
 scalar_t__ subreg_regno_offset (int,size_t,int /*<<< orphan*/ ,size_t) ; 

int
operands_match_p (rtx x, rtx y)
{
  int i;
  RTX_CODE code = GET_CODE (x);
  const char *fmt;
  int success_2;

  if (x == y)
    return 1;
  if ((code == REG || (code == SUBREG && REG_P (SUBREG_REG (x))))
      && (REG_P (y) || (GET_CODE (y) == SUBREG
				  && REG_P (SUBREG_REG (y)))))
    {
      int j;

      if (code == SUBREG)
	{
	  i = REGNO (SUBREG_REG (x));
	  if (i >= FIRST_PSEUDO_REGISTER)
	    goto slow;
	  i += subreg_regno_offset (REGNO (SUBREG_REG (x)),
				    GET_MODE (SUBREG_REG (x)),
				    SUBREG_BYTE (x),
				    GET_MODE (x));
	}
      else
	i = REGNO (x);

      if (GET_CODE (y) == SUBREG)
	{
	  j = REGNO (SUBREG_REG (y));
	  if (j >= FIRST_PSEUDO_REGISTER)
	    goto slow;
	  j += subreg_regno_offset (REGNO (SUBREG_REG (y)),
				    GET_MODE (SUBREG_REG (y)),
				    SUBREG_BYTE (y),
				    GET_MODE (y));
	}
      else
	j = REGNO (y);

      /* On a WORDS_BIG_ENDIAN machine, point to the last register of a
	 multiple hard register group of scalar integer registers, so that
	 for example (reg:DI 0) and (reg:SI 1) will be considered the same
	 register.  */
      if (WORDS_BIG_ENDIAN && GET_MODE_SIZE (GET_MODE (x)) > UNITS_PER_WORD
	  && SCALAR_INT_MODE_P (GET_MODE (x))
	  && i < FIRST_PSEUDO_REGISTER)
	i += hard_regno_nregs[i][GET_MODE (x)] - 1;
      if (WORDS_BIG_ENDIAN && GET_MODE_SIZE (GET_MODE (y)) > UNITS_PER_WORD
	  && SCALAR_INT_MODE_P (GET_MODE (y))
	  && j < FIRST_PSEUDO_REGISTER)
	j += hard_regno_nregs[j][GET_MODE (y)] - 1;

      return i == j;
    }
  /* If two operands must match, because they are really a single
     operand of an assembler insn, then two postincrements are invalid
     because the assembler insn would increment only once.
     On the other hand, a postincrement matches ordinary indexing
     if the postincrement is the output operand.  */
  if (code == POST_DEC || code == POST_INC || code == POST_MODIFY)
    return operands_match_p (XEXP (x, 0), y);
  /* Two preincrements are invalid
     because the assembler insn would increment only once.
     On the other hand, a preincrement matches ordinary indexing
     if the preincrement is the input operand.
     In this case, return 2, since some callers need to do special
     things when this happens.  */
  if (GET_CODE (y) == PRE_DEC || GET_CODE (y) == PRE_INC
      || GET_CODE (y) == PRE_MODIFY)
    return operands_match_p (x, XEXP (y, 0)) ? 2 : 0;

 slow:

  /* Now we have disposed of all the cases in which different rtx codes
     can match.  */
  if (code != GET_CODE (y))
    return 0;

  /* (MULT:SI x y) and (MULT:HI x y) are NOT equivalent.  */
  if (GET_MODE (x) != GET_MODE (y))
    return 0;

  switch (code)
    {
    case CONST_INT:
    case CONST_DOUBLE:
      return 0;

    case LABEL_REF:
      return XEXP (x, 0) == XEXP (y, 0);
    case SYMBOL_REF:
      return XSTR (x, 0) == XSTR (y, 0);

    default:
      break;
    }

  /* Compare the elements.  If any pair of corresponding elements
     fail to match, return 0 for the whole things.  */

  success_2 = 0;
  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      int val, j;
      switch (fmt[i])
	{
	case 'w':
	  if (XWINT (x, i) != XWINT (y, i))
	    return 0;
	  break;

	case 'i':
	  if (XINT (x, i) != XINT (y, i))
	    return 0;
	  break;

	case 'e':
	  val = operands_match_p (XEXP (x, i), XEXP (y, i));
	  if (val == 0)
	    return 0;
	  /* If any subexpression returns 2,
	     we should return 2 if we are successful.  */
	  if (val == 2)
	    success_2 = 1;
	  break;

	case '0':
	  break;

	case 'E':
	  if (XVECLEN (x, i) != XVECLEN (y, i))
	    return 0;
	  for (j = XVECLEN (x, i) - 1; j >= 0; --j)
	    {
	      val = operands_match_p (XVECEXP (x, i, j), XVECEXP (y, i, j));
	      if (val == 0)
		return 0;
	      if (val == 2)
		success_2 = 1;
	    }
	  break;

	  /* It is believed that rtx's at this level will never
	     contain anything but integers and other rtx's,
	     except for within LABEL_REFs and SYMBOL_REFs.  */
	default:
	  gcc_unreachable ();
	}
    }
  return 1 + success_2;
}