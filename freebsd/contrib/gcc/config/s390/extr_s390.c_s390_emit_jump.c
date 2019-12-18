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
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_jump_insn (scalar_t__) ; 
 scalar_t__ gen_rtx_IF_THEN_ELSE (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_LABEL_REF (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pc_rtx ; 

void
s390_emit_jump (rtx target, rtx cond)
{
  rtx insn;

  target = gen_rtx_LABEL_REF (VOIDmode, target);
  if (cond)
    target = gen_rtx_IF_THEN_ELSE (VOIDmode, cond, target, pc_rtx);

  insn = gen_rtx_SET (VOIDmode, pc_rtx, target);
  emit_jump_insn (insn);
}