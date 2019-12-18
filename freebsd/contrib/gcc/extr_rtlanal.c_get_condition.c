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
 scalar_t__ JUMP_LABEL (scalar_t__) ; 
 int /*<<< orphan*/  JUMP_P (scalar_t__) ; 
 scalar_t__ LABEL_REF ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  any_condjump_p (scalar_t__) ; 
 scalar_t__ canonicalize_condition (scalar_t__,scalar_t__,int,scalar_t__*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ pc_set (scalar_t__) ; 

rtx
get_condition (rtx jump, rtx *earliest, int allow_cc_mode, int valid_at_insn_p)
{
  rtx cond;
  int reverse;
  rtx set;

  /* If this is not a standard conditional jump, we can't parse it.  */
  if (!JUMP_P (jump)
      || ! any_condjump_p (jump))
    return 0;
  set = pc_set (jump);

  cond = XEXP (SET_SRC (set), 0);

  /* If this branches to JUMP_LABEL when the condition is false, reverse
     the condition.  */
  reverse
    = GET_CODE (XEXP (SET_SRC (set), 2)) == LABEL_REF
      && XEXP (XEXP (SET_SRC (set), 2), 0) == JUMP_LABEL (jump);

  return canonicalize_condition (jump, cond, reverse, earliest, NULL_RTX,
				 allow_cc_mode, valid_at_insn_p);
}