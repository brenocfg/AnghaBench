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
struct noce_if_info {scalar_t__ x; int /*<<< orphan*/  insn_a; int /*<<< orphan*/  jump; int /*<<< orphan*/  b; int /*<<< orphan*/  a; int /*<<< orphan*/  cond; } ;
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_LOCATOR (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_insn_before_setloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ end_ifcvt_sequence (struct noce_if_info*) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ noce_emit_cmove (struct noce_if_info*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noce_emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ register_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static int
noce_try_cmove (struct noce_if_info *if_info)
{
  enum rtx_code code;
  rtx target, seq;

  if ((CONSTANT_P (if_info->a) || register_operand (if_info->a, VOIDmode))
      && (CONSTANT_P (if_info->b) || register_operand (if_info->b, VOIDmode)))
    {
      start_sequence ();

      code = GET_CODE (if_info->cond);
      target = noce_emit_cmove (if_info, if_info->x, code,
				XEXP (if_info->cond, 0),
				XEXP (if_info->cond, 1),
				if_info->a, if_info->b);

      if (target)
	{
	  if (target != if_info->x)
	    noce_emit_move_insn (if_info->x, target);

	  seq = end_ifcvt_sequence (if_info);
	  if (!seq)
	    return FALSE;

	  emit_insn_before_setloc (seq, if_info->jump,
				   INSN_LOCATOR (if_info->insn_a));
	  return TRUE;
	}
      else
	{
	  end_sequence ();
	  return FALSE;
	}
    }

  return FALSE;
}