#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_7__ {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  act_machine_switch_pcb (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  disable_preemption () ; 
 int /*<<< orphan*/  enable_preemption () ; 
 int /*<<< orphan*/  fpu_switch_addrmode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_thread_create (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_has_64Bit_addr (int /*<<< orphan*/ ) ; 

void
machine_thread_switch_addrmode(thread_t thread)
{
	/*
	 * We don't want to be preempted until we're done
	 * - particularly if we're switching the current thread
	 */
	disable_preemption();

	/*
	 * Reset the state saveareas. As we're resetting, we anticipate no
	 * memory allocations in this path.
	 */
	machine_thread_create(thread, thread->task);

	/* Adjust FPU state */
	fpu_switch_addrmode(thread, task_has_64Bit_addr(thread->task));

	/* If we're switching ourselves, reset the pcb addresses etc. */
	if (thread == current_thread()) {
		boolean_t istate = ml_set_interrupts_enabled(FALSE);
		act_machine_switch_pcb(NULL, thread);
		ml_set_interrupts_enabled(istate);
	}
	enable_preemption();
}