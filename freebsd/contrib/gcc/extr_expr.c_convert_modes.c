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
 scalar_t__ CONST_DOUBLE ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_BITSIZE (int) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 int /*<<< orphan*/  HARD_REGISTER_P (int /*<<< orphan*/ ) ; 
 scalar_t__ HARD_REGNO_MODE_OK (int /*<<< orphan*/ ,int) ; 
 int HOST_BITS_PER_WIDE_INT ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MODE_INT ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int SUBREG_PROMOTED_UNSIGNED_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG_PROMOTED_VAR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ TRULY_NOOP_TRUNCATION (int,int) ; 
 scalar_t__ VECTOR_MODE_P (int) ; 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  convert_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__* direct_load ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_int_mode (int,int) ; 
 int /*<<< orphan*/  gen_lowpart (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  immed_double_const (int,int,int) ; 
 int /*<<< orphan*/  simplify_gen_subreg (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

rtx
convert_modes (enum machine_mode mode, enum machine_mode oldmode, rtx x, int unsignedp)
{
  rtx temp;

  /* If FROM is a SUBREG that indicates that we have already done at least
     the required extension, strip it.  */

  if (GET_CODE (x) == SUBREG && SUBREG_PROMOTED_VAR_P (x)
      && GET_MODE_SIZE (GET_MODE (SUBREG_REG (x))) >= GET_MODE_SIZE (mode)
      && SUBREG_PROMOTED_UNSIGNED_P (x) == unsignedp)
    x = gen_lowpart (mode, x);

  if (GET_MODE (x) != VOIDmode)
    oldmode = GET_MODE (x);

  if (mode == oldmode)
    return x;

  /* There is one case that we must handle specially: If we are converting
     a CONST_INT into a mode whose size is twice HOST_BITS_PER_WIDE_INT and
     we are to interpret the constant as unsigned, gen_lowpart will do
     the wrong if the constant appears negative.  What we want to do is
     make the high-order word of the constant zero, not all ones.  */

  if (unsignedp && GET_MODE_CLASS (mode) == MODE_INT
      && GET_MODE_BITSIZE (mode) == 2 * HOST_BITS_PER_WIDE_INT
      && GET_CODE (x) == CONST_INT && INTVAL (x) < 0)
    {
      HOST_WIDE_INT val = INTVAL (x);

      if (oldmode != VOIDmode
	  && HOST_BITS_PER_WIDE_INT > GET_MODE_BITSIZE (oldmode))
	{
	  int width = GET_MODE_BITSIZE (oldmode);

	  /* We need to zero extend VAL.  */
	  val &= ((HOST_WIDE_INT) 1 << width) - 1;
	}

      return immed_double_const (val, (HOST_WIDE_INT) 0, mode);
    }

  /* We can do this with a gen_lowpart if both desired and current modes
     are integer, and this is either a constant integer, a register, or a
     non-volatile MEM.  Except for the constant case where MODE is no
     wider than HOST_BITS_PER_WIDE_INT, we must be narrowing the operand.  */

  if ((GET_CODE (x) == CONST_INT
       && GET_MODE_BITSIZE (mode) <= HOST_BITS_PER_WIDE_INT)
      || (GET_MODE_CLASS (mode) == MODE_INT
	  && GET_MODE_CLASS (oldmode) == MODE_INT
	  && (GET_CODE (x) == CONST_DOUBLE
	      || (GET_MODE_SIZE (mode) <= GET_MODE_SIZE (oldmode)
		  && ((MEM_P (x) && ! MEM_VOLATILE_P (x)
		       && direct_load[(int) mode])
		      || (REG_P (x)
			  && (! HARD_REGISTER_P (x)
			      || HARD_REGNO_MODE_OK (REGNO (x), mode))
			  && TRULY_NOOP_TRUNCATION (GET_MODE_BITSIZE (mode),
						    GET_MODE_BITSIZE (GET_MODE (x)))))))))
    {
      /* ?? If we don't know OLDMODE, we have to assume here that
	 X does not need sign- or zero-extension.   This may not be
	 the case, but it's the best we can do.  */
      if (GET_CODE (x) == CONST_INT && oldmode != VOIDmode
	  && GET_MODE_SIZE (mode) > GET_MODE_SIZE (oldmode))
	{
	  HOST_WIDE_INT val = INTVAL (x);
	  int width = GET_MODE_BITSIZE (oldmode);

	  /* We must sign or zero-extend in this case.  Start by
	     zero-extending, then sign extend if we need to.  */
	  val &= ((HOST_WIDE_INT) 1 << width) - 1;
	  if (! unsignedp
	      && (val & ((HOST_WIDE_INT) 1 << (width - 1))))
	    val |= (HOST_WIDE_INT) (-1) << width;

	  return gen_int_mode (val, mode);
	}

      return gen_lowpart (mode, x);
    }

  /* Converting from integer constant into mode is always equivalent to an
     subreg operation.  */
  if (VECTOR_MODE_P (mode) && GET_MODE (x) == VOIDmode)
    {
      gcc_assert (GET_MODE_BITSIZE (mode) == GET_MODE_BITSIZE (oldmode));
      return simplify_gen_subreg (mode, x, oldmode, 0);
    }

  temp = gen_reg_rtx (mode);
  convert_move (temp, x, unsignedp);
  return temp;
}