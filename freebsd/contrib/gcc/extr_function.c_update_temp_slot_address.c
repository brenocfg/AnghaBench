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
struct temp_slot {scalar_t__ address; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ EXPR_LIST ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PLUS ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 struct temp_slot* find_temp_slot_from_address (scalar_t__) ; 
 void* gen_rtx_EXPR_LIST (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 

void
update_temp_slot_address (rtx old, rtx new)
{
  struct temp_slot *p;

  if (rtx_equal_p (old, new))
    return;

  p = find_temp_slot_from_address (old);

  /* If we didn't find one, see if both OLD is a PLUS.  If so, and NEW
     is a register, see if one operand of the PLUS is a temporary
     location.  If so, NEW points into it.  Otherwise, if both OLD and
     NEW are a PLUS and if there is a register in common between them.
     If so, try a recursive call on those values.  */
  if (p == 0)
    {
      if (GET_CODE (old) != PLUS)
	return;

      if (REG_P (new))
	{
	  update_temp_slot_address (XEXP (old, 0), new);
	  update_temp_slot_address (XEXP (old, 1), new);
	  return;
	}
      else if (GET_CODE (new) != PLUS)
	return;

      if (rtx_equal_p (XEXP (old, 0), XEXP (new, 0)))
	update_temp_slot_address (XEXP (old, 1), XEXP (new, 1));
      else if (rtx_equal_p (XEXP (old, 1), XEXP (new, 0)))
	update_temp_slot_address (XEXP (old, 0), XEXP (new, 1));
      else if (rtx_equal_p (XEXP (old, 0), XEXP (new, 1)))
	update_temp_slot_address (XEXP (old, 1), XEXP (new, 0));
      else if (rtx_equal_p (XEXP (old, 1), XEXP (new, 1)))
	update_temp_slot_address (XEXP (old, 0), XEXP (new, 0));

      return;
    }

  /* Otherwise add an alias for the temp's address.  */
  else if (p->address == 0)
    p->address = new;
  else
    {
      if (GET_CODE (p->address) != EXPR_LIST)
	p->address = gen_rtx_EXPR_LIST (VOIDmode, p->address, NULL_RTX);

      p->address = gen_rtx_EXPR_LIST (VOIDmode, new, p->address);
    }
}