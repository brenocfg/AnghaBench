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
 scalar_t__ ASM_OPERANDS ; 
 scalar_t__ CC0 ; 
 scalar_t__ CLOBBER ; 
 scalar_t__ COMBINE_RTX_EQUAL_P (scalar_t__,scalar_t__) ; 
 scalar_t__ CONST_DOUBLE ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 int GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 int LO_SUM ; 
 int MEM ; 
 scalar_t__ MODES_TIEABLE_P (int,int) ; 
 scalar_t__ OBJECT_P (scalar_t__) ; 
 int PARALLEL ; 
 scalar_t__ PC ; 
 int REG ; 
 scalar_t__ REGNO (scalar_t__) ; 
 scalar_t__ REG_CANNOT_CHANGE_MODE_P (scalar_t__,int,int) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ SET ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 int STRICT_LOW_PART ; 
 int SUBREG ; 
 int /*<<< orphan*/  SUBREG_BYTE (scalar_t__) ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 int /*<<< orphan*/  SUBST (scalar_t__,scalar_t__) ; 
 int VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 scalar_t__ ZERO_EXTEND ; 
 int ZERO_EXTRACT ; 
 scalar_t__ cc0_rtx ; 
 scalar_t__ combine_simplify_rtx (scalar_t__,int,int) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ copy_rtx (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 scalar_t__ gen_rtx_CLOBBER (int,scalar_t__) ; 
 int n_occurrences ; 
 scalar_t__ simplify_subreg (int,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ simplify_unary_operation (scalar_t__,int,scalar_t__,int) ; 

__attribute__((used)) static rtx
subst (rtx x, rtx from, rtx to, int in_dest, int unique_copy)
{
  enum rtx_code code = GET_CODE (x);
  enum machine_mode op0_mode = VOIDmode;
  const char *fmt;
  int len, i;
  rtx new;

/* Two expressions are equal if they are identical copies of a shared
   RTX or if they are both registers with the same register number
   and mode.  */

#define COMBINE_RTX_EQUAL_P(X,Y)			\
  ((X) == (Y)						\
   || (REG_P (X) && REG_P (Y)	\
       && REGNO (X) == REGNO (Y) && GET_MODE (X) == GET_MODE (Y)))

  if (! in_dest && COMBINE_RTX_EQUAL_P (x, from))
    {
      n_occurrences++;
      return (unique_copy && n_occurrences > 1 ? copy_rtx (to) : to);
    }

  /* If X and FROM are the same register but different modes, they will
     not have been seen as equal above.  However, flow.c will make a
     LOG_LINKS entry for that case.  If we do nothing, we will try to
     rerecognize our original insn and, when it succeeds, we will
     delete the feeding insn, which is incorrect.

     So force this insn not to match in this (rare) case.  */
  if (! in_dest && code == REG && REG_P (from)
      && REGNO (x) == REGNO (from))
    return gen_rtx_CLOBBER (GET_MODE (x), const0_rtx);

  /* If this is an object, we are done unless it is a MEM or LO_SUM, both
     of which may contain things that can be combined.  */
  if (code != MEM && code != LO_SUM && OBJECT_P (x))
    return x;

  /* It is possible to have a subexpression appear twice in the insn.
     Suppose that FROM is a register that appears within TO.
     Then, after that subexpression has been scanned once by `subst',
     the second time it is scanned, TO may be found.  If we were
     to scan TO here, we would find FROM within it and create a
     self-referent rtl structure which is completely wrong.  */
  if (COMBINE_RTX_EQUAL_P (x, to))
    return to;

  /* Parallel asm_operands need special attention because all of the
     inputs are shared across the arms.  Furthermore, unsharing the
     rtl results in recognition failures.  Failure to handle this case
     specially can result in circular rtl.

     Solve this by doing a normal pass across the first entry of the
     parallel, and only processing the SET_DESTs of the subsequent
     entries.  Ug.  */

  if (code == PARALLEL
      && GET_CODE (XVECEXP (x, 0, 0)) == SET
      && GET_CODE (SET_SRC (XVECEXP (x, 0, 0))) == ASM_OPERANDS)
    {
      new = subst (XVECEXP (x, 0, 0), from, to, 0, unique_copy);

      /* If this substitution failed, this whole thing fails.  */
      if (GET_CODE (new) == CLOBBER
	  && XEXP (new, 0) == const0_rtx)
	return new;

      SUBST (XVECEXP (x, 0, 0), new);

      for (i = XVECLEN (x, 0) - 1; i >= 1; i--)
	{
	  rtx dest = SET_DEST (XVECEXP (x, 0, i));

	  if (!REG_P (dest)
	      && GET_CODE (dest) != CC0
	      && GET_CODE (dest) != PC)
	    {
	      new = subst (dest, from, to, 0, unique_copy);

	      /* If this substitution failed, this whole thing fails.  */
	      if (GET_CODE (new) == CLOBBER
		  && XEXP (new, 0) == const0_rtx)
		return new;

	      SUBST (SET_DEST (XVECEXP (x, 0, i)), new);
	    }
	}
    }
  else
    {
      len = GET_RTX_LENGTH (code);
      fmt = GET_RTX_FORMAT (code);

      /* We don't need to process a SET_DEST that is a register, CC0,
	 or PC, so set up to skip this common case.  All other cases
	 where we want to suppress replacing something inside a
	 SET_SRC are handled via the IN_DEST operand.  */
      if (code == SET
	  && (REG_P (SET_DEST (x))
	      || GET_CODE (SET_DEST (x)) == CC0
	      || GET_CODE (SET_DEST (x)) == PC))
	fmt = "ie";

      /* Get the mode of operand 0 in case X is now a SIGN_EXTEND of a
	 constant.  */
      if (fmt[0] == 'e')
	op0_mode = GET_MODE (XEXP (x, 0));

      for (i = 0; i < len; i++)
	{
	  if (fmt[i] == 'E')
	    {
	      int j;
	      for (j = XVECLEN (x, i) - 1; j >= 0; j--)
		{
		  if (COMBINE_RTX_EQUAL_P (XVECEXP (x, i, j), from))
		    {
		      new = (unique_copy && n_occurrences
			     ? copy_rtx (to) : to);
		      n_occurrences++;
		    }
		  else
		    {
		      new = subst (XVECEXP (x, i, j), from, to, 0,
				   unique_copy);

		      /* If this substitution failed, this whole thing
			 fails.  */
		      if (GET_CODE (new) == CLOBBER
			  && XEXP (new, 0) == const0_rtx)
			return new;
		    }

		  SUBST (XVECEXP (x, i, j), new);
		}
	    }
	  else if (fmt[i] == 'e')
	    {
	      /* If this is a register being set, ignore it.  */
	      new = XEXP (x, i);
	      if (in_dest
		  && i == 0
		  && (((code == SUBREG || code == ZERO_EXTRACT)
		       && REG_P (new))
		      || code == STRICT_LOW_PART))
		;

	      else if (COMBINE_RTX_EQUAL_P (XEXP (x, i), from))
		{
		  /* In general, don't install a subreg involving two
		     modes not tieable.  It can worsen register
		     allocation, and can even make invalid reload
		     insns, since the reg inside may need to be copied
		     from in the outside mode, and that may be invalid
		     if it is an fp reg copied in integer mode.

		     We allow two exceptions to this: It is valid if
		     it is inside another SUBREG and the mode of that
		     SUBREG and the mode of the inside of TO is
		     tieable and it is valid if X is a SET that copies
		     FROM to CC0.  */

		  if (GET_CODE (to) == SUBREG
		      && ! MODES_TIEABLE_P (GET_MODE (to),
					    GET_MODE (SUBREG_REG (to)))
		      && ! (code == SUBREG
			    && MODES_TIEABLE_P (GET_MODE (x),
						GET_MODE (SUBREG_REG (to))))
#ifdef HAVE_cc0
		      && ! (code == SET && i == 1 && XEXP (x, 0) == cc0_rtx)
#endif
		      )
		    return gen_rtx_CLOBBER (VOIDmode, const0_rtx);

#ifdef CANNOT_CHANGE_MODE_CLASS
		  if (code == SUBREG
		      && REG_P (to)
		      && REGNO (to) < FIRST_PSEUDO_REGISTER
		      && REG_CANNOT_CHANGE_MODE_P (REGNO (to),
						   GET_MODE (to),
						   GET_MODE (x)))
		    return gen_rtx_CLOBBER (VOIDmode, const0_rtx);
#endif

		  new = (unique_copy && n_occurrences ? copy_rtx (to) : to);
		  n_occurrences++;
		}
	      else
		/* If we are in a SET_DEST, suppress most cases unless we
		   have gone inside a MEM, in which case we want to
		   simplify the address.  We assume here that things that
		   are actually part of the destination have their inner
		   parts in the first expression.  This is true for SUBREG,
		   STRICT_LOW_PART, and ZERO_EXTRACT, which are the only
		   things aside from REG and MEM that should appear in a
		   SET_DEST.  */
		new = subst (XEXP (x, i), from, to,
			     (((in_dest
				&& (code == SUBREG || code == STRICT_LOW_PART
				    || code == ZERO_EXTRACT))
			       || code == SET)
			      && i == 0), unique_copy);

	      /* If we found that we will have to reject this combination,
		 indicate that by returning the CLOBBER ourselves, rather than
		 an expression containing it.  This will speed things up as
		 well as prevent accidents where two CLOBBERs are considered
		 to be equal, thus producing an incorrect simplification.  */

	      if (GET_CODE (new) == CLOBBER && XEXP (new, 0) == const0_rtx)
		return new;

	      if (GET_CODE (x) == SUBREG
		  && (GET_CODE (new) == CONST_INT
		      || GET_CODE (new) == CONST_DOUBLE))
		{
		  enum machine_mode mode = GET_MODE (x);

		  x = simplify_subreg (GET_MODE (x), new,
				       GET_MODE (SUBREG_REG (x)),
				       SUBREG_BYTE (x));
		  if (! x)
		    x = gen_rtx_CLOBBER (mode, const0_rtx);
		}
	      else if (GET_CODE (new) == CONST_INT
		       && GET_CODE (x) == ZERO_EXTEND)
		{
		  x = simplify_unary_operation (ZERO_EXTEND, GET_MODE (x),
						new, GET_MODE (XEXP (x, 0)));
		  gcc_assert (x);
		}
	      else
		SUBST (XEXP (x, i), new);
	    }
	}
    }

  /* Try to simplify X.  If the simplification changed the code, it is likely
     that further simplification will help, so loop, but limit the number
     of repetitions that will be performed.  */

  for (i = 0; i < 4; i++)
    {
      /* If X is sufficiently simple, don't bother trying to do anything
	 with it.  */
      if (code != CONST_INT && code != REG && code != CLOBBER)
	x = combine_simplify_rtx (x, op0_mode, in_dest);

      if (GET_CODE (x) == code)
	break;

      code = GET_CODE (x);

      /* We no longer know the original mode of operand 0 since we
	 have changed the form of X)  */
      op0_mode = VOIDmode;
    }

  return x;
}