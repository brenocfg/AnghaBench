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
 int AND ; 
 int /*<<< orphan*/  CCmode ; 
 int /*<<< orphan*/  CR0_REGNO ; 
 int GET_MODE (scalar_t__) ; 
 int NOT ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  UNSPEC_AND ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 scalar_t__ copy_rtx (scalar_t__) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (scalar_t__) ; 
 int /*<<< orphan*/  emit_load_locked (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_store_conditional (int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_unlikely_jump (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_isync () ; 
 scalar_t__ gen_label_rtx () ; 
 int /*<<< orphan*/  gen_memory_barrier () ; 
 int /*<<< orphan*/  gen_rtvec (int,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_AND (int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_LABEL_REF (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_NE (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_NOT (int,scalar_t__) ; 
 scalar_t__ gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_UNSPEC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_fmt_ee (int,int,scalar_t__,scalar_t__) ; 

void
rs6000_split_atomic_op (enum rtx_code code, rtx mem, rtx val,
                       rtx before, rtx after, rtx scratch)
{
  enum machine_mode mode = GET_MODE (mem);
  rtx label, x, cond = gen_rtx_REG (CCmode, CR0_REGNO);

  emit_insn (gen_memory_barrier ());

  label = gen_label_rtx ();
  emit_label (label);
  label = gen_rtx_LABEL_REF (VOIDmode, label);

  if (before == NULL_RTX)
    before = scratch;
  emit_load_locked (mode, before, mem);

  if (code == NOT)
    x = gen_rtx_AND (mode, gen_rtx_NOT (mode, before), val);
  else if (code == AND)
    x = gen_rtx_UNSPEC (mode, gen_rtvec (2, before, val), UNSPEC_AND);
  else
    x = gen_rtx_fmt_ee (code, mode, before, val);

  if (after != NULL_RTX)
    emit_insn (gen_rtx_SET (VOIDmode, after, copy_rtx (x)));
  emit_insn (gen_rtx_SET (VOIDmode, scratch, x));

  emit_store_conditional (mode, cond, mem, scratch);

  x = gen_rtx_NE (VOIDmode, cond, const0_rtx);
  emit_unlikely_jump (x, label);

  emit_insn (gen_isync ());
}