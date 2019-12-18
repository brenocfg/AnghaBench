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

/* Variables and functions */
 size_t ARG_POINTER_REGNUM ; 
 int FIRST_PSEUDO_REGISTER ; 
 size_t FRAME_POINTER_REGNUM ; 
 scalar_t__ FUNCTION_ARG_REGNO_P (int /*<<< orphan*/ ) ; 
 size_t HARD_FRAME_POINTER_REGNUM ; 
 scalar_t__ HARD_REGNO_MODE_OK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTGOING_REGNO (int) ; 
 int /*<<< orphan*/  Pmode ; 
 size_t STACK_POINTER_REGNUM ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  arg_pointer_rtx ; 
 int /*<<< orphan*/  frame_pointer_rtx ; 
 int /*<<< orphan*/  gen_rtx_ADDRESS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hard_frame_pointer_rtx ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 
 int /*<<< orphan*/ * static_reg_base_value ; 

void
init_alias_once (void)
{
  int i;

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    /* Check whether this register can hold an incoming pointer
       argument.  FUNCTION_ARG_REGNO_P tests outgoing register
       numbers, so translate if necessary due to register windows.  */
    if (FUNCTION_ARG_REGNO_P (OUTGOING_REGNO (i))
	&& HARD_REGNO_MODE_OK (i, Pmode))
      static_reg_base_value[i]
	= gen_rtx_ADDRESS (VOIDmode, gen_rtx_REG (Pmode, i));

  static_reg_base_value[STACK_POINTER_REGNUM]
    = gen_rtx_ADDRESS (Pmode, stack_pointer_rtx);
  static_reg_base_value[ARG_POINTER_REGNUM]
    = gen_rtx_ADDRESS (Pmode, arg_pointer_rtx);
  static_reg_base_value[FRAME_POINTER_REGNUM]
    = gen_rtx_ADDRESS (Pmode, frame_pointer_rtx);
#if HARD_FRAME_POINTER_REGNUM != FRAME_POINTER_REGNUM
  static_reg_base_value[HARD_FRAME_POINTER_REGNUM]
    = gen_rtx_ADDRESS (Pmode, hard_frame_pointer_rtx);
#endif
}