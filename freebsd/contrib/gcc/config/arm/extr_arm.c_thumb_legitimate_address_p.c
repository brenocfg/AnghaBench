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
 scalar_t__ CONST ; 
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 scalar_t__ CONSTANT_POOL_ADDRESS_P (scalar_t__) ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ FRAME_POINTER_REGNUM ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 int GET_MODE_SIZE (int) ; 
 int INTVAL (scalar_t__) ; 
 scalar_t__ LABEL_REF ; 
 scalar_t__ MODE_FLOAT ; 
 scalar_t__ PLUS ; 
 scalar_t__ POST_INC ; 
 scalar_t__ REG ; 
 scalar_t__ REGNO (scalar_t__) ; 
 scalar_t__ STACK_POINTER_REGNUM ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ arg_pointer_rtx ; 
 scalar_t__ flag_pic ; 
 scalar_t__ frame_pointer_rtx ; 
 int /*<<< orphan*/  get_pool_constant (scalar_t__) ; 
 int /*<<< orphan*/  pcrel_constant_p (int /*<<< orphan*/ ) ; 
 scalar_t__ reg_mentioned_p (scalar_t__,scalar_t__) ; 
 scalar_t__ reload_completed ; 
 scalar_t__ reload_in_progress ; 
 scalar_t__ symbol_mentioned_p (int /*<<< orphan*/ ) ; 
 scalar_t__ thumb_base_register_rtx_p (scalar_t__,int,int) ; 
 scalar_t__ thumb_index_register_rtx_p (scalar_t__,int) ; 
 scalar_t__ thumb_legitimate_offset_p (int,int) ; 
 scalar_t__ virtual_incoming_args_rtx ; 
 scalar_t__ virtual_outgoing_args_rtx ; 
 scalar_t__ virtual_stack_dynamic_rtx ; 
 scalar_t__ virtual_stack_vars_rtx ; 

int
thumb_legitimate_address_p (enum machine_mode mode, rtx x, int strict_p)
{
  /* ??? Not clear if this is right.  Experiment.  */
  if (GET_MODE_SIZE (mode) < 4
      && !(reload_in_progress || reload_completed)
      && (reg_mentioned_p (frame_pointer_rtx, x)
	  || reg_mentioned_p (arg_pointer_rtx, x)
	  || reg_mentioned_p (virtual_incoming_args_rtx, x)
	  || reg_mentioned_p (virtual_outgoing_args_rtx, x)
	  || reg_mentioned_p (virtual_stack_dynamic_rtx, x)
	  || reg_mentioned_p (virtual_stack_vars_rtx, x)))
    return 0;

  /* Accept any base register.  SP only in SImode or larger.  */
  else if (thumb_base_register_rtx_p (x, mode, strict_p))
    return 1;

  /* This is PC relative data before arm_reorg runs.  */
  else if (GET_MODE_SIZE (mode) >= 4 && CONSTANT_P (x)
	   && GET_CODE (x) == SYMBOL_REF
           && CONSTANT_POOL_ADDRESS_P (x) && !flag_pic)
    return 1;

  /* This is PC relative data after arm_reorg runs.  */
  else if (GET_MODE_SIZE (mode) >= 4 && reload_completed
	   && (GET_CODE (x) == LABEL_REF
	       || (GET_CODE (x) == CONST
		   && GET_CODE (XEXP (x, 0)) == PLUS
		   && GET_CODE (XEXP (XEXP (x, 0), 0)) == LABEL_REF
		   && GET_CODE (XEXP (XEXP (x, 0), 1)) == CONST_INT)))
    return 1;

  /* Post-inc indexing only supported for SImode and larger.  */
  else if (GET_CODE (x) == POST_INC && GET_MODE_SIZE (mode) >= 4
	   && thumb_index_register_rtx_p (XEXP (x, 0), strict_p))
    return 1;

  else if (GET_CODE (x) == PLUS)
    {
      /* REG+REG address can be any two index registers.  */
      /* We disallow FRAME+REG addressing since we know that FRAME
	 will be replaced with STACK, and SP relative addressing only
	 permits SP+OFFSET.  */
      if (GET_MODE_SIZE (mode) <= 4
	  && XEXP (x, 0) != frame_pointer_rtx
	  && XEXP (x, 1) != frame_pointer_rtx
	  && thumb_index_register_rtx_p (XEXP (x, 0), strict_p)
	  && thumb_index_register_rtx_p (XEXP (x, 1), strict_p))
	return 1;

      /* REG+const has 5-7 bit offset for non-SP registers.  */
      else if ((thumb_index_register_rtx_p (XEXP (x, 0), strict_p)
		|| XEXP (x, 0) == arg_pointer_rtx)
	       && GET_CODE (XEXP (x, 1)) == CONST_INT
	       && thumb_legitimate_offset_p (mode, INTVAL (XEXP (x, 1))))
	return 1;

      /* REG+const has 10 bit offset for SP, but only SImode and
	 larger is supported.  */
      /* ??? Should probably check for DI/DFmode overflow here
	 just like GO_IF_LEGITIMATE_OFFSET does.  */
      else if (GET_CODE (XEXP (x, 0)) == REG
	       && REGNO (XEXP (x, 0)) == STACK_POINTER_REGNUM
	       && GET_MODE_SIZE (mode) >= 4
	       && GET_CODE (XEXP (x, 1)) == CONST_INT
	       && INTVAL (XEXP (x, 1)) >= 0
	       && INTVAL (XEXP (x, 1)) + GET_MODE_SIZE (mode) <= 1024
	       && (INTVAL (XEXP (x, 1)) & 3) == 0)
	return 1;

      else if (GET_CODE (XEXP (x, 0)) == REG
	       && REGNO (XEXP (x, 0)) == FRAME_POINTER_REGNUM
	       && GET_MODE_SIZE (mode) >= 4
	       && GET_CODE (XEXP (x, 1)) == CONST_INT
	       && (INTVAL (XEXP (x, 1)) & 3) == 0)
	return 1;
    }

  else if (GET_MODE_CLASS (mode) != MODE_FLOAT
	   && GET_MODE_SIZE (mode) == 4
	   && GET_CODE (x) == SYMBOL_REF
	   && CONSTANT_POOL_ADDRESS_P (x)
	   && ! (flag_pic
		 && symbol_mentioned_p (get_pool_constant (x))
		 && ! pcrel_constant_p (get_pool_constant (x))))
    return 1;

  return 0;
}