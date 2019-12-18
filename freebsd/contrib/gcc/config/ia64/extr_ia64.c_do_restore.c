#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int next_iter; int /*<<< orphan*/ * prev_insn; } ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 TYPE_1__ spill_fill_data ; 
 int /*<<< orphan*/  spill_restore_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_restore (rtx (*move_fn) (rtx, rtx, rtx), rtx reg, HOST_WIDE_INT cfa_off)
{
  int iter = spill_fill_data.next_iter;
  rtx insn;

  insn = emit_insn ((*move_fn) (reg, spill_restore_mem (reg, cfa_off),
				GEN_INT (cfa_off)));
  spill_fill_data.prev_insn[iter] = insn;
}