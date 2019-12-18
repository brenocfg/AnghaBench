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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE_SIZE (int) ; 
 int INTVAL (scalar_t__) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ PLUS ; 
 int /*<<< orphan*/  SImode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ arm_tls_symbol_p (scalar_t__) ; 
 scalar_t__ flag_pic ; 
 scalar_t__ force_operand (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ force_reg (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_PLUS (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ legitimize_pic_address (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ legitimize_tls_address (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ optimize_size ; 
 scalar_t__ plus_constant (scalar_t__,int) ; 
 scalar_t__ s_register_operand (scalar_t__,int /*<<< orphan*/ ) ; 

rtx
thumb_legitimize_address (rtx x, rtx orig_x, enum machine_mode mode)
{
  if (arm_tls_symbol_p (x))
    return legitimize_tls_address (x, NULL_RTX);

  if (GET_CODE (x) == PLUS
      && GET_CODE (XEXP (x, 1)) == CONST_INT
      && (INTVAL (XEXP (x, 1)) >= 32 * GET_MODE_SIZE (mode)
	  || INTVAL (XEXP (x, 1)) < 0))
    {
      rtx xop0 = XEXP (x, 0);
      rtx xop1 = XEXP (x, 1);
      HOST_WIDE_INT offset = INTVAL (xop1);

      /* Try and fold the offset into a biasing of the base register and
	 then offsetting that.  Don't do this when optimizing for space
	 since it can cause too many CSEs.  */
      if (optimize_size && offset >= 0
	  && offset < 256 + 31 * GET_MODE_SIZE (mode))
	{
	  HOST_WIDE_INT delta;

	  if (offset >= 256)
	    delta = offset - (256 - GET_MODE_SIZE (mode));
	  else if (offset < 32 * GET_MODE_SIZE (mode) + 8)
	    delta = 31 * GET_MODE_SIZE (mode);
	  else
	    delta = offset & (~31 * GET_MODE_SIZE (mode));

	  xop0 = force_operand (plus_constant (xop0, offset - delta),
				NULL_RTX);
	  x = plus_constant (xop0, delta);
	}
      else if (offset < 0 && offset > -256)
	/* Small negative offsets are best done with a subtract before the
	   dereference, forcing these into a register normally takes two
	   instructions.  */
	x = force_operand (x, NULL_RTX);
      else
	{
	  /* For the remaining cases, force the constant into a register.  */
	  xop1 = force_reg (SImode, xop1);
	  x = gen_rtx_PLUS (SImode, xop0, xop1);
	}
    }
  else if (GET_CODE (x) == PLUS
	   && s_register_operand (XEXP (x, 1), SImode)
	   && !s_register_operand (XEXP (x, 0), SImode))
    {
      rtx xop0 = force_operand (XEXP (x, 0), NULL_RTX);

      x = gen_rtx_PLUS (SImode, xop0, XEXP (x, 1));
    }

  if (flag_pic)
    {
      /* We need to find and carefully transform any SYMBOL and LABEL
	 references; so go back to the original address expression.  */
      rtx new_x = legitimize_pic_address (orig_x, mode, NULL_RTX);

      if (new_x != orig_x)
	x = new_x;
    }

  return x;
}