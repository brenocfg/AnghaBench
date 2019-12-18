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
typedef  scalar_t__ thread_t ;
typedef  scalar_t__ thread_state_t ;
typedef  int thread_flavor_t ;
struct arm_thread_state {int /*<<< orphan*/  sp; int /*<<< orphan*/ * r; int /*<<< orphan*/  pc; int /*<<< orphan*/  cpsr; int /*<<< orphan*/  lr; } ;
struct arm_saved_state {int /*<<< orphan*/ * r; int /*<<< orphan*/  cpsr; int /*<<< orphan*/  pc; int /*<<< orphan*/  lr; int /*<<< orphan*/  sp; } ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_2__ {struct arm_saved_state* cpu_int_state; } ;

/* Variables and functions */
#define  ARM_THREAD_STATE 128 
 int /*<<< orphan*/  ARM_THREAD_STATE_COUNT ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ current_thread () ; 
 TYPE_1__* getCpuDatap () ; 
 int /*<<< orphan*/  machine_thread_get_kern_state_kprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
machine_thread_get_kern_state(
			      thread_t thread,
			      thread_flavor_t flavor,
			      thread_state_t tstate,
			      mach_msg_type_number_t * count)
{

#define machine_thread_get_kern_state_kprintf(x...)	/* kprintf("machine_threa
							 * d_get_kern_state: "
							 * x) */

	/*
	 * This works only for an interrupted kernel thread
	 */
	if (thread != current_thread() || getCpuDatap()->cpu_int_state == NULL)
		return KERN_FAILURE;

	switch (flavor) {
	case ARM_THREAD_STATE:{
			struct arm_thread_state *state;
			struct arm_saved_state *saved_state;
			unsigned int    i;
			if (*count < ARM_THREAD_STATE_COUNT)
				return (KERN_INVALID_ARGUMENT);

			state = (struct arm_thread_state *) tstate;
			saved_state = getCpuDatap()->cpu_int_state;

			state->sp = saved_state->sp;
			state->lr = saved_state->lr;
			state->pc = saved_state->pc;
			state->cpsr = saved_state->cpsr;
			for (i = 0; i < 13; i++)
				state->r[i] = saved_state->r[i];
			machine_thread_get_kern_state_kprintf("machine_thread_get_state: pc 0x%x r0 0x%x sp  0x%x\n",
					 state->pc, state->r[0], state->sp);
			*count = ARM_THREAD_STATE_COUNT;
			break;
		}
	default:
		return (KERN_INVALID_ARGUMENT);
	}
	return (KERN_SUCCESS);
}