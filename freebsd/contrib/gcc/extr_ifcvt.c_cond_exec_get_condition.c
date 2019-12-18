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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 scalar_t__ JUMP_LABEL (scalar_t__) ; 
 scalar_t__ LABEL_REF ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ SET_SRC (int /*<<< orphan*/ ) ; 
 int UNKNOWN ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ any_condjump_p (scalar_t__) ; 
 scalar_t__ gen_rtx_fmt_ee (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pc_set (scalar_t__) ; 
 int reversed_comparison_code (scalar_t__,scalar_t__) ; 

__attribute__((used)) static rtx
cond_exec_get_condition (rtx jump)
{
  rtx test_if, cond;

  if (any_condjump_p (jump))
    test_if = SET_SRC (pc_set (jump));
  else
    return NULL_RTX;
  cond = XEXP (test_if, 0);

  /* If this branches to JUMP_LABEL when the condition is false,
     reverse the condition.  */
  if (GET_CODE (XEXP (test_if, 2)) == LABEL_REF
      && XEXP (XEXP (test_if, 2), 0) == JUMP_LABEL (jump))
    {
      enum rtx_code rev = reversed_comparison_code (cond, jump);
      if (rev == UNKNOWN)
	return NULL_RTX;

      cond = gen_rtx_fmt_ee (rev, GET_MODE (cond), XEXP (cond, 0),
			     XEXP (cond, 1));
    }

  return cond;
}