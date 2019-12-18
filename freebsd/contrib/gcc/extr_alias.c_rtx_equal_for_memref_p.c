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
 scalar_t__ COMMUTATIVE_P (scalar_t__) ; 
#define  CONST_DOUBLE 133 
#define  CONST_INT 132 
 int GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  LABEL_REF 131 
 scalar_t__ NON_COMMUTATIVE_P (scalar_t__) ; 
 int PLUS ; 
#define  REG 130 
 int /*<<< orphan*/  REGNO (scalar_t__) ; 
#define  SYMBOL_REF 129 
 scalar_t__ UNARY_P (scalar_t__) ; 
#define  VALUE 128 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  XINT (scalar_t__,int) ; 
 int /*<<< orphan*/  XSTR (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 scalar_t__ canon_rtx (scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rtx_equal_for_memref_p (rtx x, rtx y)
{
  int i;
  int j;
  enum rtx_code code;
  const char *fmt;

  if (x == 0 && y == 0)
    return 1;
  if (x == 0 || y == 0)
    return 0;

  if (x == y)
    return 1;

  code = GET_CODE (x);
  /* Rtx's of different codes cannot be equal.  */
  if (code != GET_CODE (y))
    return 0;

  /* (MULT:SI x y) and (MULT:HI x y) are NOT equivalent.
     (REG:SI x) and (REG:HI x) are NOT equivalent.  */

  if (GET_MODE (x) != GET_MODE (y))
    return 0;

  /* Some RTL can be compared without a recursive examination.  */
  switch (code)
    {
    case REG:
      return REGNO (x) == REGNO (y);

    case LABEL_REF:
      return XEXP (x, 0) == XEXP (y, 0);

    case SYMBOL_REF:
      return XSTR (x, 0) == XSTR (y, 0);

    case VALUE:
    case CONST_INT:
    case CONST_DOUBLE:
      /* There's no need to compare the contents of CONST_DOUBLEs or
	 CONST_INTs because pointer equality is a good enough
	 comparison for these nodes.  */
      return 0;

    default:
      break;
    }

  /* canon_rtx knows how to handle plus.  No need to canonicalize.  */
  if (code == PLUS)
    return ((rtx_equal_for_memref_p (XEXP (x, 0), XEXP (y, 0))
	     && rtx_equal_for_memref_p (XEXP (x, 1), XEXP (y, 1)))
	    || (rtx_equal_for_memref_p (XEXP (x, 0), XEXP (y, 1))
		&& rtx_equal_for_memref_p (XEXP (x, 1), XEXP (y, 0))));
  /* For commutative operations, the RTX match if the operand match in any
     order.  Also handle the simple binary and unary cases without a loop.  */
  if (COMMUTATIVE_P (x))
    {
      rtx xop0 = canon_rtx (XEXP (x, 0));
      rtx yop0 = canon_rtx (XEXP (y, 0));
      rtx yop1 = canon_rtx (XEXP (y, 1));

      return ((rtx_equal_for_memref_p (xop0, yop0)
	       && rtx_equal_for_memref_p (canon_rtx (XEXP (x, 1)), yop1))
	      || (rtx_equal_for_memref_p (xop0, yop1)
		  && rtx_equal_for_memref_p (canon_rtx (XEXP (x, 1)), yop0)));
    }
  else if (NON_COMMUTATIVE_P (x))
    {
      return (rtx_equal_for_memref_p (canon_rtx (XEXP (x, 0)),
				      canon_rtx (XEXP (y, 0)))
	      && rtx_equal_for_memref_p (canon_rtx (XEXP (x, 1)),
					 canon_rtx (XEXP (y, 1))));
    }
  else if (UNARY_P (x))
    return rtx_equal_for_memref_p (canon_rtx (XEXP (x, 0)),
				   canon_rtx (XEXP (y, 0)));

  /* Compare the elements.  If any pair of corresponding elements
     fail to match, return 0 for the whole things.

     Limit cases to types which actually appear in addresses.  */

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      switch (fmt[i])
	{
	case 'i':
	  if (XINT (x, i) != XINT (y, i))
	    return 0;
	  break;

	case 'E':
	  /* Two vectors must have the same length.  */
	  if (XVECLEN (x, i) != XVECLEN (y, i))
	    return 0;

	  /* And the corresponding elements must match.  */
	  for (j = 0; j < XVECLEN (x, i); j++)
	    if (rtx_equal_for_memref_p (canon_rtx (XVECEXP (x, i, j)),
					canon_rtx (XVECEXP (y, i, j))) == 0)
	      return 0;
	  break;

	case 'e':
	  if (rtx_equal_for_memref_p (canon_rtx (XEXP (x, i)),
				      canon_rtx (XEXP (y, i))) == 0)
	    return 0;
	  break;

	  /* This can happen for asm operands.  */
	case 's':
	  if (strcmp (XSTR (x, i), XSTR (y, i)))
	    return 0;
	  break;

	/* This can happen for an asm which clobbers memory.  */
	case '0':
	  break;

	  /* It is believed that rtx's at this level will never
	     contain anything but integers and other rtx's,
	     except for within LABEL_REFs and SYMBOL_REFs.  */
	default:
	  gcc_unreachable ();
	}
    }
  return 1;
}