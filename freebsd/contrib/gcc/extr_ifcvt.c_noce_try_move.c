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
struct noce_if_info {int /*<<< orphan*/  insn_a; int /*<<< orphan*/  jump; int /*<<< orphan*/  x; int /*<<< orphan*/  b; int /*<<< orphan*/  a; int /*<<< orphan*/  cond; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 int EQ ; 
 int FALSE ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ HONOR_NANS (int /*<<< orphan*/ ) ; 
 scalar_t__ HONOR_SIGNED_ZEROS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_LOCATOR (int /*<<< orphan*/ ) ; 
 int NE ; 
 int TRUE ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_insn_before_setloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_ifcvt_sequence (struct noce_if_info*) ; 
 int /*<<< orphan*/  noce_emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static int
noce_try_move (struct noce_if_info *if_info)
{
  rtx cond = if_info->cond;
  enum rtx_code code = GET_CODE (cond);
  rtx y, seq;

  if (code != NE && code != EQ)
    return FALSE;

  /* This optimization isn't valid if either A or B could be a NaN
     or a signed zero.  */
  if (HONOR_NANS (GET_MODE (if_info->x))
      || HONOR_SIGNED_ZEROS (GET_MODE (if_info->x)))
    return FALSE;

  /* Check whether the operands of the comparison are A and in
     either order.  */
  if ((rtx_equal_p (if_info->a, XEXP (cond, 0))
       && rtx_equal_p (if_info->b, XEXP (cond, 1)))
      || (rtx_equal_p (if_info->a, XEXP (cond, 1))
	  && rtx_equal_p (if_info->b, XEXP (cond, 0))))
    {
      y = (code == EQ) ? if_info->a : if_info->b;

      /* Avoid generating the move if the source is the destination.  */
      if (! rtx_equal_p (if_info->x, y))
	{
	  start_sequence ();
	  noce_emit_move_insn (if_info->x, y);
	  seq = end_ifcvt_sequence (if_info);
	  if (!seq)
	    return FALSE;

	  emit_insn_before_setloc (seq, if_info->jump,
				   INSN_LOCATOR (if_info->insn_a));
	}
      return TRUE;
    }
  return FALSE;
}