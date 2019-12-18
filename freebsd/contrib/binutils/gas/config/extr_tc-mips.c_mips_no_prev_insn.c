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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOP_INSN ; 
 int /*<<< orphan*/  history ; 
 int /*<<< orphan*/  insert_into_history (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_clear_insn_labels () ; 
 int /*<<< orphan*/ * prev_nop_frag ; 

__attribute__((used)) static void
mips_no_prev_insn (void)
{
  prev_nop_frag = NULL;
  insert_into_history (0, ARRAY_SIZE (history), NOP_INSN);
  mips_clear_insn_labels ();
}