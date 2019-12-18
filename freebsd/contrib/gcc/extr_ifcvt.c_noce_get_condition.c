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

/* Variables and functions */
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ JUMP_LABEL (scalar_t__) ; 
 scalar_t__ LABEL_REF ; 
 scalar_t__ MODE_INT ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  any_condjump_p (scalar_t__) ; 
 scalar_t__ canonicalize_condition (scalar_t__,scalar_t__,int,scalar_t__*,scalar_t__,int,int) ; 
 scalar_t__ gen_rtx_fmt_ee (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ pc_set (scalar_t__) ; 
 int /*<<< orphan*/  reverse_condition (scalar_t__) ; 

__attribute__((used)) static rtx
noce_get_condition (rtx jump, rtx *earliest)
{
  rtx cond, set, tmp;
  bool reverse;

  if (! any_condjump_p (jump))
    return NULL_RTX;

  set = pc_set (jump);

  /* If this branches to JUMP_LABEL when the condition is false,
     reverse the condition.  */
  reverse = (GET_CODE (XEXP (SET_SRC (set), 2)) == LABEL_REF
	     && XEXP (XEXP (SET_SRC (set), 2), 0) == JUMP_LABEL (jump));

  /* If the condition variable is a register and is MODE_INT, accept it.  */

  cond = XEXP (SET_SRC (set), 0);
  tmp = XEXP (cond, 0);
  if (REG_P (tmp) && GET_MODE_CLASS (GET_MODE (tmp)) == MODE_INT)
    {
      *earliest = jump;

      if (reverse)
	cond = gen_rtx_fmt_ee (reverse_condition (GET_CODE (cond)),
			       GET_MODE (cond), tmp, XEXP (cond, 1));
      return cond;
    }

  /* Otherwise, fall back on canonicalize_condition to do the dirty
     work of manipulating MODE_CC values and COMPARE rtx codes.  */
  return canonicalize_condition (jump, cond, reverse, earliest,
				 NULL_RTX, false, true);
}