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
 scalar_t__ DImode ; 
 int /*<<< orphan*/  EQ ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_anddi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_andsi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_label_rtx () ; 
 int /*<<< orphan*/  gen_reg_rtx (scalar_t__) ; 

__attribute__((used)) static rtx
ix86_expand_aligntest (rtx variable, int value)
{
  rtx label = gen_label_rtx ();
  rtx tmpcount = gen_reg_rtx (GET_MODE (variable));
  if (GET_MODE (variable) == DImode)
    emit_insn (gen_anddi3 (tmpcount, variable, GEN_INT (value)));
  else
    emit_insn (gen_andsi3 (tmpcount, variable, GEN_INT (value)));
  emit_cmp_and_jump_insns (tmpcount, const0_rtx, EQ, 0, GET_MODE (variable),
			   1, label);
  return label;
}