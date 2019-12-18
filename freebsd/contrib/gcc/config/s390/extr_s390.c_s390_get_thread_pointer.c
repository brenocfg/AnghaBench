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
 int /*<<< orphan*/  BITS_PER_WORD ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  TP_REGNUM ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_reg_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
s390_get_thread_pointer (void)
{
  rtx tp = gen_reg_rtx (Pmode);

  emit_move_insn (tp, gen_rtx_REG (Pmode, TP_REGNUM));
  mark_reg_pointer (tp, BITS_PER_WORD);

  return tp;
}