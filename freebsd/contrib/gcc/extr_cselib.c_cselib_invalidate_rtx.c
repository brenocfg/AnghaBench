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
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ STRICT_LOW_PART ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ZERO_EXTRACT ; 
 int /*<<< orphan*/  cselib_invalidate_mem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cselib_invalidate_regno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ push_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

void
cselib_invalidate_rtx (rtx dest)
{
  while (GET_CODE (dest) == SUBREG
	 || GET_CODE (dest) == ZERO_EXTRACT
	 || GET_CODE (dest) == STRICT_LOW_PART)
    dest = XEXP (dest, 0);

  if (REG_P (dest))
    cselib_invalidate_regno (REGNO (dest), GET_MODE (dest));
  else if (MEM_P (dest))
    cselib_invalidate_mem (dest);

  /* Some machines don't define AUTO_INC_DEC, but they still use push
     instructions.  We need to catch that case here in order to
     invalidate the stack pointer correctly.  Note that invalidating
     the stack pointer is different from invalidating DEST.  */
  if (push_operand (dest, GET_MODE (dest)))
    cselib_invalidate_rtx (stack_pointer_rtx);
}