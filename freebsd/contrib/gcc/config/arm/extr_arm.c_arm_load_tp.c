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
 int /*<<< orphan*/  SImode ; 
 scalar_t__ TARGET_HARD_TP ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_load_tp_hard (scalar_t__) ; 
 int /*<<< orphan*/  gen_load_tp_soft () ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
arm_load_tp (rtx target)
{
  if (!target)
    target = gen_reg_rtx (SImode);

  if (TARGET_HARD_TP)
    {
      /* Can return in any reg.  */
      emit_insn (gen_load_tp_hard (target));
    }
  else
    {
      /* Always returned in r0.  Immediately copy the result into a pseudo,
	 otherwise other uses of r0 (e.g. setting up function arguments) may
	 clobber the value.  */

      rtx tmp;

      emit_insn (gen_load_tp_soft ());

      tmp = gen_rtx_REG (SImode, 0);
      emit_move_insn (target, tmp);
    }
  return target;
}