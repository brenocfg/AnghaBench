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
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM ; 
 scalar_t__ PLUS ; 
 scalar_t__ REG ; 
 scalar_t__ REG_MODE_OK_FOR_BASE_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arg_pointer_rtx ; 
 int /*<<< orphan*/  frame_pointer_rtx ; 
 scalar_t__ reg_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ reload_completed ; 
 scalar_t__ reload_in_progress ; 
 int /*<<< orphan*/  virtual_incoming_args_rtx ; 
 int /*<<< orphan*/  virtual_outgoing_args_rtx ; 
 int /*<<< orphan*/  virtual_stack_dynamic_rtx ; 
 int /*<<< orphan*/  virtual_stack_vars_rtx ; 

int
cirrus_memory_offset (rtx op)
{
  /* Reject eliminable registers.  */
  if (! (reload_in_progress || reload_completed)
      && (   reg_mentioned_p (frame_pointer_rtx, op)
	  || reg_mentioned_p (arg_pointer_rtx, op)
	  || reg_mentioned_p (virtual_incoming_args_rtx, op)
	  || reg_mentioned_p (virtual_outgoing_args_rtx, op)
	  || reg_mentioned_p (virtual_stack_dynamic_rtx, op)
	  || reg_mentioned_p (virtual_stack_vars_rtx, op)))
    return 0;

  if (GET_CODE (op) == MEM)
    {
      rtx ind;

      ind = XEXP (op, 0);

      /* Match: (mem (reg)).  */
      if (GET_CODE (ind) == REG)
	return 1;

      /* Match:
	 (mem (plus (reg)
	            (const))).  */
      if (GET_CODE (ind) == PLUS
	  && GET_CODE (XEXP (ind, 0)) == REG
	  && REG_MODE_OK_FOR_BASE_P (XEXP (ind, 0), VOIDmode)
	  && GET_CODE (XEXP (ind, 1)) == CONST_INT)
	return 1;
    }

  return 0;
}