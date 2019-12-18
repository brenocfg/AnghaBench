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
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 unsigned int GET_MODE_SIZE (int) ; 
 int INTVAL (scalar_t__) ; 
 int /*<<< orphan*/  MEM_P (scalar_t__) ; 
 scalar_t__ PLUS ; 
 scalar_t__ PRE_MODIFY ; 
 unsigned int PUSH_ROUNDING (unsigned int) ; 
 scalar_t__ STACK_PUSH_CODE ; 
 int VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ stack_pointer_rtx ; 

int
push_operand (rtx op, enum machine_mode mode)
{
  unsigned int rounded_size = GET_MODE_SIZE (mode);

#ifdef PUSH_ROUNDING
  rounded_size = PUSH_ROUNDING (rounded_size);
#endif

  if (!MEM_P (op))
    return 0;

  if (mode != VOIDmode && GET_MODE (op) != mode)
    return 0;

  op = XEXP (op, 0);

  if (rounded_size == GET_MODE_SIZE (mode))
    {
      if (GET_CODE (op) != STACK_PUSH_CODE)
	return 0;
    }
  else
    {
      if (GET_CODE (op) != PRE_MODIFY
	  || GET_CODE (XEXP (op, 1)) != PLUS
	  || XEXP (XEXP (op, 1), 0) != XEXP (op, 0)
	  || GET_CODE (XEXP (XEXP (op, 1), 1)) != CONST_INT
#ifdef STACK_GROWS_DOWNWARD
	  || INTVAL (XEXP (XEXP (op, 1), 1)) != - (int) rounded_size
#else
	  || INTVAL (XEXP (XEXP (op, 1), 1)) != (int) rounded_size
#endif
	  )
	return 0;
    }

  return XEXP (op, 0) == stack_pointer_rtx;
}