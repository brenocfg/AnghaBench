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
 int /*<<< orphan*/  do_pending_stack_adjust () ; 
 int /*<<< orphan*/  emit_barrier () ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_jump (int /*<<< orphan*/ ) ; 

void
emit_jump (rtx label)
{
  do_pending_stack_adjust ();
  emit_jump_insn (gen_jump (label));
  emit_barrier ();
}