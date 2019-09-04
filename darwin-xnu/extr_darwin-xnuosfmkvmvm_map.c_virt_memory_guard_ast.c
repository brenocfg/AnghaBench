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
typedef  int uint32_t ;
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* task_t ;
typedef  int /*<<< orphan*/  mach_exception_data_type_t ;
struct TYPE_8__ {int task_exc_guard; } ;
struct TYPE_7__ {TYPE_2__* task; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXC_GUARD ; 
 scalar_t__ OSCompareAndSwap (int,int,int*) ; 
 int TASK_EXC_GUARD_VM_CORPSE ; 
 int TASK_EXC_GUARD_VM_DELIVER ; 
 int TASK_EXC_GUARD_VM_FATAL ; 
 int TASK_EXC_GUARD_VM_ONCE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* current_task () ; 
 TYPE_2__* kernel_task ; 
 int /*<<< orphan*/  task_bsdtask_kill (TYPE_2__*) ; 
 int /*<<< orphan*/  task_exception_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_violated_guard (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
virt_memory_guard_ast(
	thread_t thread,
	mach_exception_data_type_t code,
	mach_exception_data_type_t subcode)
{
	task_t task = thread->task;
	assert(task != kernel_task);
	assert(task == current_task());
	uint32_t behavior;

	behavior = task->task_exc_guard;

	/* Is delivery enabled */
	if ((behavior & TASK_EXC_GUARD_VM_DELIVER) == 0) {
		return;
	}

	/* If only once, make sure we're that once */
	while (behavior & TASK_EXC_GUARD_VM_ONCE) {
		uint32_t new_behavior = behavior & ~TASK_EXC_GUARD_VM_DELIVER;

		if (OSCompareAndSwap(behavior, new_behavior, &task->task_exc_guard)) {
			break;
		}
		behavior = task->task_exc_guard;
		if ((behavior & TASK_EXC_GUARD_VM_DELIVER) == 0) {
			return;
		}
	}

	/* Raise exception via corpse fork or synchronously */
	if ((task->task_exc_guard & TASK_EXC_GUARD_VM_CORPSE) &&
	    (task->task_exc_guard & TASK_EXC_GUARD_VM_FATAL) == 0) {
		task_violated_guard(code, subcode, NULL);
	} else {
		task_exception_notify(EXC_GUARD, code, subcode);
	}

	/* Terminate the task if desired */
	if (task->task_exc_guard & TASK_EXC_GUARD_VM_FATAL) {
		task_bsdtask_kill(current_task());
	}
}