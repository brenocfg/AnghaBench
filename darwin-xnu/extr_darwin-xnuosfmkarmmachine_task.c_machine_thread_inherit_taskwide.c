#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_3__ {scalar_t__ task_debug; } ;

/* Variables and functions */
 int ARM_DEBUG_STATE ; 
 int /*<<< orphan*/  ARM_DEBUG_STATE_COUNT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  machine_thread_set_state (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 

kern_return_t
machine_thread_inherit_taskwide(
				thread_t thread,
				task_t parent_task)
{
	if (parent_task->task_debug) {
		int flavor;
		mach_msg_type_number_t count;

		flavor = ARM_DEBUG_STATE;
		count = ARM_DEBUG_STATE_COUNT;

		return machine_thread_set_state(thread, flavor, parent_task->task_debug, count);
	}

	return KERN_SUCCESS;
}