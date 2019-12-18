#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_6__* thread_t ;
typedef  scalar_t__ task_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  cpu_data_t ;
struct TYPE_14__ {int /*<<< orphan*/  count; int /*<<< orphan*/  flavor; } ;
struct TYPE_16__ {TYPE_2__ nsh; } ;
struct TYPE_13__ {int /*<<< orphan*/  count; int /*<<< orphan*/  flavor; } ;
struct TYPE_15__ {TYPE_1__ ash; } ;
struct TYPE_19__ {TYPE_4__ ns; TYPE_3__ ss; } ;
typedef  TYPE_7__ arm_context_t ;
struct TYPE_17__ {TYPE_7__* contextData; TYPE_4__* uNeon; TYPE_3__* upcb; int /*<<< orphan*/  perfctrl_state; scalar_t__ cthread_data; scalar_t__ cthread_self; scalar_t__ preemption_count; int /*<<< orphan*/ * CpuDatap; } ;
struct TYPE_18__ {TYPE_5__ machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_NEON_SAVED_STATE32 ; 
 int /*<<< orphan*/  ARM_NEON_SAVED_STATE32_COUNT ; 
 int /*<<< orphan*/  ARM_NEON_SAVED_STATE64 ; 
 int /*<<< orphan*/  ARM_NEON_SAVED_STATE64_COUNT ; 
 int /*<<< orphan*/  ARM_SAVED_STATE32 ; 
 int /*<<< orphan*/  ARM_SAVED_STATE32_COUNT ; 
 int /*<<< orphan*/  ARM_SAVED_STATE64 ; 
 int /*<<< orphan*/  ARM_SAVED_STATE64_COUNT ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 TYPE_6__* current_thread () ; 
 scalar_t__ kernel_task ; 
 int /*<<< orphan*/  machine_thread_create_kprintf (char*,TYPE_6__*) ; 
 scalar_t__ machine_thread_state_initialize (TYPE_6__*) ; 
 scalar_t__ task_has_64Bit_data (scalar_t__) ; 
 int /*<<< orphan*/  user_ss_zone ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_7__*) ; 

kern_return_t
machine_thread_create(
		      thread_t thread,
		      task_t task)
{
	arm_context_t *thread_user_ss = NULL;
	kern_return_t result = KERN_SUCCESS;

#define machine_thread_create_kprintf(x...)	/* kprintf("machine_thread_create: " x) */

	machine_thread_create_kprintf("thread = %x\n", thread);

	if (current_thread() != thread) {
		thread->machine.CpuDatap = (cpu_data_t *)0;
	}
	thread->machine.preemption_count = 0;
	thread->machine.cthread_self = 0;
	thread->machine.cthread_data = 0;


	if (task != kernel_task) {
		/* If this isn't a kernel thread, we'll have userspace state. */
		thread->machine.contextData = (arm_context_t *)zalloc(user_ss_zone);

		if (!thread->machine.contextData) {
			return KERN_FAILURE;
		}

		thread->machine.upcb = &thread->machine.contextData->ss;
		thread->machine.uNeon = &thread->machine.contextData->ns;

		if (task_has_64Bit_data(task)) {
			thread->machine.upcb->ash.flavor = ARM_SAVED_STATE64;
			thread->machine.upcb->ash.count = ARM_SAVED_STATE64_COUNT;
			thread->machine.uNeon->nsh.flavor = ARM_NEON_SAVED_STATE64;
			thread->machine.uNeon->nsh.count = ARM_NEON_SAVED_STATE64_COUNT;
		} else {
			thread->machine.upcb->ash.flavor = ARM_SAVED_STATE32;
			thread->machine.upcb->ash.count = ARM_SAVED_STATE32_COUNT;
			thread->machine.uNeon->nsh.flavor = ARM_NEON_SAVED_STATE32;
			thread->machine.uNeon->nsh.count = ARM_NEON_SAVED_STATE32_COUNT;
		}
	} else {
		thread->machine.upcb = NULL;
		thread->machine.uNeon = NULL;
		thread->machine.contextData = NULL;
	}

	bzero(&thread->machine.perfctrl_state, sizeof(thread->machine.perfctrl_state));

	result = machine_thread_state_initialize(thread);

	if (result != KERN_SUCCESS) {
		thread_user_ss = thread->machine.contextData;
		thread->machine.upcb = NULL;
		thread->machine.uNeon = NULL;
		thread->machine.contextData = NULL;
		zfree(user_ss_zone, thread_user_ss);
	}

	return result;
}