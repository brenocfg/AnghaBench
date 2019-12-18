#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
typedef  scalar_t__ thread_state_t ;
struct arm_saved_state {int /*<<< orphan*/  cpsr; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  arm_thread_state_t ;
struct TYPE_7__ {struct arm_saved_state PcbData; } ;
struct TYPE_8__ {TYPE_1__ machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  PSR_USERDFLT ; 
 TYPE_2__* current_thread () ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_state32_to_saved_state (int /*<<< orphan*/ *,struct arm_saved_state*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_2__*) ; 

kern_return_t
thread_set_wq_state32(thread_t thread, thread_state_t tstate)
{
	arm_thread_state_t *state;
	struct arm_saved_state *saved_state;
	thread_t curth = current_thread();
	spl_t s=0;

	saved_state = &thread->machine.PcbData;
	state = (arm_thread_state_t *)tstate;

	if (curth != thread) {
		s = splsched();
		thread_lock(thread);
	}

	/*
	 * do not zero saved_state, it can be concurrently accessed
	 * and zero is not a valid state for some of the registers,
	 * like sp.
	 */
	thread_state32_to_saved_state(state, saved_state);
	saved_state->cpsr = PSR_USERDFLT;

	if (curth != thread) {
		thread_unlock(thread);
		splx(s);
	}

	return KERN_SUCCESS;
}