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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ BYTES_BIG_ENDIAN ; 
 scalar_t__ COMPARISON_P (scalar_t__) ; 
 scalar_t__ CONST ; 
 scalar_t__ CONST_DOUBLE ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 unsigned int GET_MODE_SIZE (int) ; 
 scalar_t__ LABEL_REF ; 
 int MAX (unsigned int,unsigned int) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ MEM_VOLATILE_P (scalar_t__) ; 
 scalar_t__ MIN (unsigned int,unsigned int) ; 
 int Pmode ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 scalar_t__ SYMBOL_REF ; 
 unsigned int UNITS_PER_WORD ; 
 int VOIDmode ; 
 scalar_t__ WORDS_BIG_ENDIAN ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int) ; 
 scalar_t__ adjust_address_nv (scalar_t__,int,int) ; 
 int /*<<< orphan*/  const0_rtx ; 
 scalar_t__ gen_lowpart_common (int,scalar_t__) ; 
 scalar_t__ gen_rtx_CLOBBER (int,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_SUBREG (int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_fmt_ee (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int int_mode_for_mode (int) ; 
 scalar_t__ mode_dependent_address_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  record_subregs_of_mode (scalar_t__) ; 
 scalar_t__ simplify_gen_subreg (int,scalar_t__,int,int) ; 
 int subreg_lowpart_offset (int,int) ; 

__attribute__((used)) static rtx
gen_lowpart_for_combine (enum machine_mode omode, rtx x)
{
  enum machine_mode imode = GET_MODE (x);
  unsigned int osize = GET_MODE_SIZE (omode);
  unsigned int isize = GET_MODE_SIZE (imode);
  rtx result;

  if (omode == imode)
    return x;

  /* Return identity if this is a CONST or symbolic reference.  */
  if (omode == Pmode
      && (GET_CODE (x) == CONST
	  || GET_CODE (x) == SYMBOL_REF
	  || GET_CODE (x) == LABEL_REF))
    return x;

  /* We can only support MODE being wider than a word if X is a
     constant integer or has a mode the same size.  */
  if (GET_MODE_SIZE (omode) > UNITS_PER_WORD
      && ! ((imode == VOIDmode
	     && (GET_CODE (x) == CONST_INT
		 || GET_CODE (x) == CONST_DOUBLE))
	    || isize == osize))
    goto fail;

  /* X might be a paradoxical (subreg (mem)).  In that case, gen_lowpart
     won't know what to do.  So we will strip off the SUBREG here and
     process normally.  */
  if (GET_CODE (x) == SUBREG && MEM_P (SUBREG_REG (x)))
    {
      x = SUBREG_REG (x);

      /* For use in case we fall down into the address adjustments
	 further below, we need to adjust the known mode and size of
	 x; imode and isize, since we just adjusted x.  */
      imode = GET_MODE (x);

      if (imode == omode)
	return x;

      isize = GET_MODE_SIZE (imode);
    }

  result = gen_lowpart_common (omode, x);

#ifdef CANNOT_CHANGE_MODE_CLASS
  if (result != 0 && GET_CODE (result) == SUBREG)
    record_subregs_of_mode (result);
#endif

  if (result)
    return result;

  if (MEM_P (x))
    {
      int offset = 0;

      /* Refuse to work on a volatile memory ref or one with a mode-dependent
	 address.  */
      if (MEM_VOLATILE_P (x) || mode_dependent_address_p (XEXP (x, 0)))
	goto fail;

      /* If we want to refer to something bigger than the original memref,
	 generate a paradoxical subreg instead.  That will force a reload
	 of the original memref X.  */
      if (isize < osize)
	return gen_rtx_SUBREG (omode, x, 0);

      if (WORDS_BIG_ENDIAN)
	offset = MAX (isize, UNITS_PER_WORD) - MAX (osize, UNITS_PER_WORD);

      /* Adjust the address so that the address-after-the-data is
	 unchanged.  */
      if (BYTES_BIG_ENDIAN)
	offset -= MIN (UNITS_PER_WORD, osize) - MIN (UNITS_PER_WORD, isize);

      return adjust_address_nv (x, omode, offset);
    }

  /* If X is a comparison operator, rewrite it in a new mode.  This
     probably won't match, but may allow further simplifications.  */
  else if (COMPARISON_P (x))
    return gen_rtx_fmt_ee (GET_CODE (x), omode, XEXP (x, 0), XEXP (x, 1));

  /* If we couldn't simplify X any other way, just enclose it in a
     SUBREG.  Normally, this SUBREG won't match, but some patterns may
     include an explicit SUBREG or we may simplify it further in combine.  */
  else
    {
      int offset = 0;
      rtx res;

      offset = subreg_lowpart_offset (omode, imode);
      if (imode == VOIDmode)
	{
	  imode = int_mode_for_mode (omode);
	  x = gen_lowpart_common (imode, x);
	  if (x == NULL)
	    goto fail;
	}
      res = simplify_gen_subreg (omode, x, imode, offset);
      if (res)
	return res;
    }

 fail:
  return gen_rtx_CLOBBER (imode, const0_rtx);
}