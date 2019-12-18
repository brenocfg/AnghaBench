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

/* Variables and functions */
 scalar_t__ CONST ; 
 scalar_t__ CONST_INT ; 
 int FALSE ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_REF ; 
 scalar_t__ MEM ; 
 scalar_t__ PLUS ; 
 scalar_t__ POST_DEC ; 
 scalar_t__ POST_INC ; 
 scalar_t__ POST_MODIFY ; 
 scalar_t__ PRE_DEC ; 
 scalar_t__ PRE_INC ; 
 scalar_t__ PRE_MODIFY ; 
 scalar_t__ REG ; 
 scalar_t__ REG_MODE_OK_FOR_BASE_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arg_pointer_rtx ; 
 int arm_address_register_rtx_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_pointer_rtx ; 
 scalar_t__ reg_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ reload_completed ; 
 scalar_t__ reload_in_progress ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtual_incoming_args_rtx ; 
 int /*<<< orphan*/  virtual_outgoing_args_rtx ; 
 int /*<<< orphan*/  virtual_stack_dynamic_rtx ; 
 int /*<<< orphan*/  virtual_stack_vars_rtx ; 

int
arm_coproc_mem_operand (rtx op, bool wb)
{
  rtx ind;

  /* Reject eliminable registers.  */
  if (! (reload_in_progress || reload_completed)
      && (   reg_mentioned_p (frame_pointer_rtx, op)
	  || reg_mentioned_p (arg_pointer_rtx, op)
	  || reg_mentioned_p (virtual_incoming_args_rtx, op)
	  || reg_mentioned_p (virtual_outgoing_args_rtx, op)
	  || reg_mentioned_p (virtual_stack_dynamic_rtx, op)
	  || reg_mentioned_p (virtual_stack_vars_rtx, op)))
    return FALSE;

  /* Constants are converted into offsets from labels.  */
  if (GET_CODE (op) != MEM)
    return FALSE;

  ind = XEXP (op, 0);

  if (reload_completed
      && (GET_CODE (ind) == LABEL_REF
	  || (GET_CODE (ind) == CONST
	      && GET_CODE (XEXP (ind, 0)) == PLUS
	      && GET_CODE (XEXP (XEXP (ind, 0), 0)) == LABEL_REF
	      && GET_CODE (XEXP (XEXP (ind, 0), 1)) == CONST_INT)))
    return TRUE;

  /* Match: (mem (reg)).  */
  if (GET_CODE (ind) == REG)
    return arm_address_register_rtx_p (ind, 0);

  /* Autoincremment addressing modes.  */
  if (wb
      && (GET_CODE (ind) == PRE_INC
	  || GET_CODE (ind) == POST_INC
	  || GET_CODE (ind) == PRE_DEC
	  || GET_CODE (ind) == POST_DEC))
    return arm_address_register_rtx_p (XEXP (ind, 0), 0);

  if (wb
      && (GET_CODE (ind) == POST_MODIFY || GET_CODE (ind) == PRE_MODIFY)
      && arm_address_register_rtx_p (XEXP (ind, 0), 0)
      && GET_CODE (XEXP (ind, 1)) == PLUS
      && rtx_equal_p (XEXP (XEXP (ind, 1), 0), XEXP (ind, 0)))
    ind = XEXP (ind, 1);

  /* Match:
     (plus (reg)
	   (const)).  */
  if (GET_CODE (ind) == PLUS
      && GET_CODE (XEXP (ind, 0)) == REG
      && REG_MODE_OK_FOR_BASE_P (XEXP (ind, 0), VOIDmode)
      && GET_CODE (XEXP (ind, 1)) == CONST_INT
      && INTVAL (XEXP (ind, 1)) > -1024
      && INTVAL (XEXP (ind, 1)) <  1024
      && (INTVAL (XEXP (ind, 1)) & 3) == 0)
    return TRUE;

  return FALSE;
}