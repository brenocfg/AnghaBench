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
struct temp_slot {scalar_t__ slot; scalar_t__ address; scalar_t__ base_offset; scalar_t__ full_size; struct temp_slot* next; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 scalar_t__ EXPR_LIST ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ INTVAL (scalar_t__) ; 
 scalar_t__ PLUS ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int max_slot_level () ; 
 struct temp_slot** temp_slots_at_level (int) ; 
 scalar_t__ virtual_stack_vars_rtx ; 

__attribute__((used)) static struct temp_slot *
find_temp_slot_from_address (rtx x)
{
  struct temp_slot *p;
  rtx next;
  int i;

  for (i = max_slot_level (); i >= 0; i--)
    for (p = *temp_slots_at_level (i); p; p = p->next)
      {
	if (XEXP (p->slot, 0) == x
	    || p->address == x
	    || (GET_CODE (x) == PLUS
		&& XEXP (x, 0) == virtual_stack_vars_rtx
		&& GET_CODE (XEXP (x, 1)) == CONST_INT
		&& INTVAL (XEXP (x, 1)) >= p->base_offset
		&& INTVAL (XEXP (x, 1)) < p->base_offset + p->full_size))
	  return p;

	else if (p->address != 0 && GET_CODE (p->address) == EXPR_LIST)
	  for (next = p->address; next; next = XEXP (next, 1))
	    if (XEXP (next, 0) == x)
	      return p;
      }

  /* If we have a sum involving a register, see if it points to a temp
     slot.  */
  if (GET_CODE (x) == PLUS && REG_P (XEXP (x, 0))
      && (p = find_temp_slot_from_address (XEXP (x, 0))) != 0)
    return p;
  else if (GET_CODE (x) == PLUS && REG_P (XEXP (x, 1))
	   && (p = find_temp_slot_from_address (XEXP (x, 1))) != 0)
    return p;

  return 0;
}