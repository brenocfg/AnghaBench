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
 int /*<<< orphan*/  BITS_PER_UNIT ; 
 scalar_t__ CONSTANT_ADDRESS_P (scalar_t__) ; 
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  LEGITIMIZE_ADDRESS (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ MINUS ; 
 scalar_t__ MULT ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ PLUS ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ break_out_memory_refs (scalar_t__) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ convert_memory_address (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ copy_to_reg (scalar_t__) ; 
 int /*<<< orphan*/  cse_not_expected ; 
 scalar_t__ eliminate_constant_term (scalar_t__,scalar_t__*) ; 
 scalar_t__ flag_force_addr ; 
 scalar_t__ force_operand (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ force_reg (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_PLUS (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mark_reg_pointer (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ memory_address_p (int,scalar_t__) ; 
 int /*<<< orphan*/  update_temp_slot_address (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  win ; 

rtx
memory_address (enum machine_mode mode, rtx x)
{
  rtx oldx = x;

  x = convert_memory_address (Pmode, x);

  /* By passing constant addresses through registers
     we get a chance to cse them.  */
  if (! cse_not_expected && CONSTANT_P (x) && CONSTANT_ADDRESS_P (x))
    x = force_reg (Pmode, x);

  /* We get better cse by rejecting indirect addressing at this stage.
     Let the combiner create indirect addresses where appropriate.
     For now, generate the code so that the subexpressions useful to share
     are visible.  But not if cse won't be done!  */
  else
    {
      if (! cse_not_expected && !REG_P (x))
	x = break_out_memory_refs (x);

      /* At this point, any valid address is accepted.  */
      if (memory_address_p (mode, x))
	goto win;

      /* If it was valid before but breaking out memory refs invalidated it,
	 use it the old way.  */
      if (memory_address_p (mode, oldx))
	goto win2;

      /* Perform machine-dependent transformations on X
	 in certain cases.  This is not necessary since the code
	 below can handle all possible cases, but machine-dependent
	 transformations can make better code.  */
      LEGITIMIZE_ADDRESS (x, oldx, mode, win);

      /* PLUS and MULT can appear in special ways
	 as the result of attempts to make an address usable for indexing.
	 Usually they are dealt with by calling force_operand, below.
	 But a sum containing constant terms is special
	 if removing them makes the sum a valid address:
	 then we generate that address in a register
	 and index off of it.  We do this because it often makes
	 shorter code, and because the addresses thus generated
	 in registers often become common subexpressions.  */
      if (GET_CODE (x) == PLUS)
	{
	  rtx constant_term = const0_rtx;
	  rtx y = eliminate_constant_term (x, &constant_term);
	  if (constant_term == const0_rtx
	      || ! memory_address_p (mode, y))
	    x = force_operand (x, NULL_RTX);
	  else
	    {
	      y = gen_rtx_PLUS (GET_MODE (x), copy_to_reg (y), constant_term);
	      if (! memory_address_p (mode, y))
		x = force_operand (x, NULL_RTX);
	      else
		x = y;
	    }
	}

      else if (GET_CODE (x) == MULT || GET_CODE (x) == MINUS)
	x = force_operand (x, NULL_RTX);

      /* If we have a register that's an invalid address,
	 it must be a hard reg of the wrong class.  Copy it to a pseudo.  */
      else if (REG_P (x))
	x = copy_to_reg (x);

      /* Last resort: copy the value to a register, since
	 the register is a valid address.  */
      else
	x = force_reg (Pmode, x);

      goto done;

    win2:
      x = oldx;
    win:
      if (flag_force_addr && ! cse_not_expected && !REG_P (x))
	{
	  x = force_operand (x, NULL_RTX);
	  x = force_reg (Pmode, x);
	}
    }

 done:

  /* If we didn't change the address, we are done.  Otherwise, mark
     a reg as a pointer if we have REG or REG + CONST_INT.  */
  if (oldx == x)
    return x;
  else if (REG_P (x))
    mark_reg_pointer (x, BITS_PER_UNIT);
  else if (GET_CODE (x) == PLUS
	   && REG_P (XEXP (x, 0))
	   && GET_CODE (XEXP (x, 1)) == CONST_INT)
    mark_reg_pointer (XEXP (x, 0), BITS_PER_UNIT);

  /* OLDX may have been the address on a temporary.  Update the address
     to indicate that X is now used.  */
  update_temp_slot_address (oldx, x);

  return x;
}