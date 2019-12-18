#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
struct TYPE_2__ {scalar_t__ (* commutative_p ) (scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  ADDR_DIFF_VEC 136 
#define  ADDR_VEC 135 
#define  CC0 134 
#define  CODE_LABEL 133 
#define  CONST_DOUBLE 132 
#define  CONST_INT 131 
 int GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  LABEL_REF 130 
 int /*<<< orphan*/  LABEL_REF_NONLOCAL_P (scalar_t__) ; 
 scalar_t__ NON_COMMUTATIVE_P (scalar_t__) ; 
#define  PC 129 
 int REG ; 
 int REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int SUBREG ; 
 int SUBREG_BYTE (scalar_t__) ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
#define  SYMBOL_REF 128 
 scalar_t__ UNARY_P (scalar_t__) ; 
 int /*<<< orphan*/  UNKNOWN ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  XINT (scalar_t__,int) ; 
 int /*<<< orphan*/  XSTR (scalar_t__,int) ; 
 int /*<<< orphan*/  XTREE (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int /*<<< orphan*/  XVECLEN (scalar_t__,int) ; 
 int /*<<< orphan*/  XWINT (scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  next_real_insn (scalar_t__) ; 
 int* reg_renumber ; 
 int rtx_equal_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (scalar_t__,int /*<<< orphan*/ ) ; 
 int subreg_regno_offset (int,scalar_t__,int,scalar_t__) ; 
 TYPE_1__ targetm ; 

int
rtx_renumbered_equal_p (rtx x, rtx y)
{
  int i;
  enum rtx_code code = GET_CODE (x);
  const char *fmt;

  if (x == y)
    return 1;

  if ((code == REG || (code == SUBREG && REG_P (SUBREG_REG (x))))
      && (REG_P (y) || (GET_CODE (y) == SUBREG
				  && REG_P (SUBREG_REG (y)))))
    {
      int reg_x = -1, reg_y = -1;
      int byte_x = 0, byte_y = 0;

      if (GET_MODE (x) != GET_MODE (y))
	return 0;

      /* If we haven't done any renumbering, don't
	 make any assumptions.  */
      if (reg_renumber == 0)
	return rtx_equal_p (x, y);

      if (code == SUBREG)
	{
	  reg_x = REGNO (SUBREG_REG (x));
	  byte_x = SUBREG_BYTE (x);

	  if (reg_renumber[reg_x] >= 0)
	    {
	      reg_x = subreg_regno_offset (reg_renumber[reg_x],
					   GET_MODE (SUBREG_REG (x)),
					   byte_x,
					   GET_MODE (x));
	      byte_x = 0;
	    }
	}
      else
	{
	  reg_x = REGNO (x);
	  if (reg_renumber[reg_x] >= 0)
	    reg_x = reg_renumber[reg_x];
	}

      if (GET_CODE (y) == SUBREG)
	{
	  reg_y = REGNO (SUBREG_REG (y));
	  byte_y = SUBREG_BYTE (y);

	  if (reg_renumber[reg_y] >= 0)
	    {
	      reg_y = subreg_regno_offset (reg_renumber[reg_y],
					   GET_MODE (SUBREG_REG (y)),
					   byte_y,
					   GET_MODE (y));
	      byte_y = 0;
	    }
	}
      else
	{
	  reg_y = REGNO (y);
	  if (reg_renumber[reg_y] >= 0)
	    reg_y = reg_renumber[reg_y];
	}

      return reg_x >= 0 && reg_x == reg_y && byte_x == byte_y;
    }

  /* Now we have disposed of all the cases
     in which different rtx codes can match.  */
  if (code != GET_CODE (y))
    return 0;

  switch (code)
    {
    case PC:
    case CC0:
    case ADDR_VEC:
    case ADDR_DIFF_VEC:
    case CONST_INT:
    case CONST_DOUBLE:
      return 0;

    case LABEL_REF:
      /* We can't assume nonlocal labels have their following insns yet.  */
      if (LABEL_REF_NONLOCAL_P (x) || LABEL_REF_NONLOCAL_P (y))
	return XEXP (x, 0) == XEXP (y, 0);

      /* Two label-refs are equivalent if they point at labels
	 in the same position in the instruction stream.  */
      return (next_real_insn (XEXP (x, 0))
	      == next_real_insn (XEXP (y, 0)));

    case SYMBOL_REF:
      return XSTR (x, 0) == XSTR (y, 0);

    case CODE_LABEL:
      /* If we didn't match EQ equality above, they aren't the same.  */
      return 0;

    default:
      break;
    }

  /* (MULT:SI x y) and (MULT:HI x y) are NOT equivalent.  */

  if (GET_MODE (x) != GET_MODE (y))
    return 0;

  /* For commutative operations, the RTX match if the operand match in any
     order.  Also handle the simple binary and unary cases without a loop.  */
  if (targetm.commutative_p (x, UNKNOWN))
    return ((rtx_renumbered_equal_p (XEXP (x, 0), XEXP (y, 0))
	     && rtx_renumbered_equal_p (XEXP (x, 1), XEXP (y, 1)))
	    || (rtx_renumbered_equal_p (XEXP (x, 0), XEXP (y, 1))
		&& rtx_renumbered_equal_p (XEXP (x, 1), XEXP (y, 0))));
  else if (NON_COMMUTATIVE_P (x))
    return (rtx_renumbered_equal_p (XEXP (x, 0), XEXP (y, 0))
	    && rtx_renumbered_equal_p (XEXP (x, 1), XEXP (y, 1)));
  else if (UNARY_P (x))
    return rtx_renumbered_equal_p (XEXP (x, 0), XEXP (y, 0));

  /* Compare the elements.  If any pair of corresponding elements
     fail to match, return 0 for the whole things.  */

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      int j;
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

	case 't':
	  if (XTREE (x, i) != XTREE (y, i))
	    return 0;
	  break;

	case 's':
	  if (strcmp (XSTR (x, i), XSTR (y, i)))
	    return 0;
	  break;

	case 'e':
	  if (! rtx_renumbered_equal_p (XEXP (x, i), XEXP (y, i)))
	    return 0;
	  break;

	case 'u':
	  if (XEXP (x, i) != XEXP (y, i))
	    return 0;
	  /* Fall through.  */
	case '0':
	  break;

	case 'E':
	  if (XVECLEN (x, i) != XVECLEN (y, i))
	    return 0;
	  for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	    if (!rtx_renumbered_equal_p (XVECEXP (x, i, j), XVECEXP (y, i, j)))
	      return 0;
	  break;

	default:
	  gcc_unreachable ();
	}
    }
  return 1;
}