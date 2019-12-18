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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  const1_rtx ; 
 int /*<<< orphan*/  do_compare_rtx_and_jump (scalar_t__,scalar_t__,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_label (scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ emit_store_flag (scalar_t__,int,scalar_t__,scalar_t__,int,int,int) ; 
 scalar_t__ gen_label_rtx () ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 scalar_t__ reg_mentioned_p (scalar_t__,scalar_t__) ; 

rtx
emit_store_flag_force (rtx target, enum rtx_code code, rtx op0, rtx op1,
		       enum machine_mode mode, int unsignedp, int normalizep)
{
  rtx tem, label;

  /* First see if emit_store_flag can do the job.  */
  tem = emit_store_flag (target, code, op0, op1, mode, unsignedp, normalizep);
  if (tem != 0)
    return tem;

  if (normalizep == 0)
    normalizep = 1;

  /* If this failed, we have to do this with set/compare/jump/set code.  */

  if (!REG_P (target)
      || reg_mentioned_p (target, op0) || reg_mentioned_p (target, op1))
    target = gen_reg_rtx (GET_MODE (target));

  emit_move_insn (target, const1_rtx);
  label = gen_label_rtx ();
  do_compare_rtx_and_jump (op0, op1, code, unsignedp, mode, NULL_RTX,
			   NULL_RTX, label);

  emit_move_insn (target, const0_rtx);
  emit_label (label);

  return target;
}