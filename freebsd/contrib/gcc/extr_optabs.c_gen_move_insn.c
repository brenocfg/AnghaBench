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
 int /*<<< orphan*/  emit_move_insn_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  start_sequence () ; 

rtx
gen_move_insn (rtx x, rtx y)
{
  rtx seq;

  start_sequence ();
  emit_move_insn_1 (x, y);
  seq = get_insns ();
  end_sequence ();
  return seq;
}