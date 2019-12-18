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
 size_t ARG_POINTER_REGNUM ; 
 int CONST_INT ; 
 int /*<<< orphan*/  FIRST_VIRTUAL_REGISTER ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAST_VIRTUAL_REGISTER ; 
#define  PLUS 129 
#define  REG 128 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arg_pointer_rtx ; 
 int /*<<< orphan*/ * fixed_regs ; 
 int /*<<< orphan*/  frame_pointer_rtx ; 
 int /*<<< orphan*/  hard_frame_pointer_rtx ; 

__attribute__((used)) static bool
fixed_base_plus_p (rtx x)
{
  switch (GET_CODE (x))
    {
    case REG:
      if (x == frame_pointer_rtx || x == hard_frame_pointer_rtx)
	return true;
      if (x == arg_pointer_rtx && fixed_regs[ARG_POINTER_REGNUM])
	return true;
      if (REGNO (x) >= FIRST_VIRTUAL_REGISTER
	  && REGNO (x) <= LAST_VIRTUAL_REGISTER)
	return true;
      return false;

    case PLUS:
      if (GET_CODE (XEXP (x, 1)) != CONST_INT)
	return false;
      return fixed_base_plus_p (XEXP (x, 0));

    default:
      return false;
    }
}