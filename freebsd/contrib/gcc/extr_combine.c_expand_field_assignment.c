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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ AND ; 
 scalar_t__ ASHIFT ; 
 scalar_t__ BITS_BIG_ENDIAN ; 
 int BLKmode ; 
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  FLOAT_MODE_P (int) ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_BITSIZE (int) ; 
 int GET_MODE_SIZE (int) ; 
 int HOST_BITS_PER_WIDE_INT ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ IOR ; 
 scalar_t__ MINUS ; 
 int /*<<< orphan*/  MODE_INT ; 
 int /*<<< orphan*/  NOT ; 
 int /*<<< orphan*/  SCALAR_INT_MODE_P (int) ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ STRICT_LOW_PART ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int UNITS_PER_WORD ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ZERO_EXTRACT ; 
 int /*<<< orphan*/  copy_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_lowpart (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mode_for_size (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nonzero_sign_valid ; 
 int /*<<< orphan*/  simplify_gen_binary (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_gen_unary (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ subreg_lowpart_p (int /*<<< orphan*/ ) ; 
 int subreg_lsb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_field_assignment (rtx x)
{
  rtx inner;
  rtx pos;			/* Always counts from low bit.  */
  int len;
  rtx mask, cleared, masked;
  enum machine_mode compute_mode;

  /* Loop until we find something we can't simplify.  */
  while (1)
    {
      if (GET_CODE (SET_DEST (x)) == STRICT_LOW_PART
	  && GET_CODE (XEXP (SET_DEST (x), 0)) == SUBREG)
	{
	  inner = SUBREG_REG (XEXP (SET_DEST (x), 0));
	  len = GET_MODE_BITSIZE (GET_MODE (XEXP (SET_DEST (x), 0)));
	  pos = GEN_INT (subreg_lsb (XEXP (SET_DEST (x), 0)));
	}
      else if (GET_CODE (SET_DEST (x)) == ZERO_EXTRACT
	       && GET_CODE (XEXP (SET_DEST (x), 1)) == CONST_INT)
	{
	  inner = XEXP (SET_DEST (x), 0);
	  len = INTVAL (XEXP (SET_DEST (x), 1));
	  pos = XEXP (SET_DEST (x), 2);

	  /* A constant position should stay within the width of INNER.  */
	  if (GET_CODE (pos) == CONST_INT
	      && INTVAL (pos) + len > GET_MODE_BITSIZE (GET_MODE (inner)))
	    break;

	  if (BITS_BIG_ENDIAN)
	    {
	      if (GET_CODE (pos) == CONST_INT)
		pos = GEN_INT (GET_MODE_BITSIZE (GET_MODE (inner)) - len
			       - INTVAL (pos));
	      else if (GET_CODE (pos) == MINUS
		       && GET_CODE (XEXP (pos, 1)) == CONST_INT
		       && (INTVAL (XEXP (pos, 1))
			   == GET_MODE_BITSIZE (GET_MODE (inner)) - len))
		/* If position is ADJUST - X, new position is X.  */
		pos = XEXP (pos, 0);
	      else
		pos = simplify_gen_binary (MINUS, GET_MODE (pos),
					   GEN_INT (GET_MODE_BITSIZE (
						    GET_MODE (inner))
						    - len),
					   pos);
	    }
	}

      /* A SUBREG between two modes that occupy the same numbers of words
	 can be done by moving the SUBREG to the source.  */
      else if (GET_CODE (SET_DEST (x)) == SUBREG
	       /* We need SUBREGs to compute nonzero_bits properly.  */
	       && nonzero_sign_valid
	       && (((GET_MODE_SIZE (GET_MODE (SET_DEST (x)))
		     + (UNITS_PER_WORD - 1)) / UNITS_PER_WORD)
		   == ((GET_MODE_SIZE (GET_MODE (SUBREG_REG (SET_DEST (x))))
			+ (UNITS_PER_WORD - 1)) / UNITS_PER_WORD)))
	{
	  x = gen_rtx_SET (VOIDmode, SUBREG_REG (SET_DEST (x)),
			   gen_lowpart
			   (GET_MODE (SUBREG_REG (SET_DEST (x))),
			    SET_SRC (x)));
	  continue;
	}
      else
	break;

      while (GET_CODE (inner) == SUBREG && subreg_lowpart_p (inner))
	inner = SUBREG_REG (inner);

      compute_mode = GET_MODE (inner);

      /* Don't attempt bitwise arithmetic on non scalar integer modes.  */
      if (! SCALAR_INT_MODE_P (compute_mode))
	{
	  enum machine_mode imode;

	  /* Don't do anything for vector or complex integral types.  */
	  if (! FLOAT_MODE_P (compute_mode))
	    break;

	  /* Try to find an integral mode to pun with.  */
	  imode = mode_for_size (GET_MODE_BITSIZE (compute_mode), MODE_INT, 0);
	  if (imode == BLKmode)
	    break;

	  compute_mode = imode;
	  inner = gen_lowpart (imode, inner);
	}

      /* Compute a mask of LEN bits, if we can do this on the host machine.  */
      if (len >= HOST_BITS_PER_WIDE_INT)
	break;

      /* Now compute the equivalent expression.  Make a copy of INNER
	 for the SET_DEST in case it is a MEM into which we will substitute;
	 we don't want shared RTL in that case.  */
      mask = GEN_INT (((HOST_WIDE_INT) 1 << len) - 1);
      cleared = simplify_gen_binary (AND, compute_mode,
				     simplify_gen_unary (NOT, compute_mode,
				       simplify_gen_binary (ASHIFT,
							    compute_mode,
							    mask, pos),
				       compute_mode),
				     inner);
      masked = simplify_gen_binary (ASHIFT, compute_mode,
				    simplify_gen_binary (
				      AND, compute_mode,
				      gen_lowpart (compute_mode, SET_SRC (x)),
				      mask),
				    pos);

      x = gen_rtx_SET (VOIDmode, copy_rtx (inner),
		       simplify_gen_binary (IOR, compute_mode,
					    cleared, masked));
    }

  return x;
}