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
typedef  int /*<<< orphan*/  thread_state_t ;
typedef  int thread_flavor_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_2__ {int /*<<< orphan*/ * cpu_int_state; } ;

/* Variables and functions */
#define  ARM_THREAD_STATE 130 
#define  ARM_THREAD_STATE32 129 
#define  ARM_THREAD_STATE64 128 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ current_thread () ; 
 TYPE_1__* getCpuDatap () ; 
 int /*<<< orphan*/  handle_get_arm32_thread_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_get_arm64_thread_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_get_arm_thread_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

kern_return_t
machine_thread_get_kern_state(
			      thread_t thread,
			      thread_flavor_t flavor,
			      thread_state_t tstate,
			      mach_msg_type_number_t * count)
{
	/*
	 * This works only for an interrupted kernel thread
	 */
	if (thread != current_thread() || getCpuDatap()->cpu_int_state == NULL)
		return KERN_FAILURE;

	switch (flavor) {
	case ARM_THREAD_STATE:
	{
		kern_return_t rn = handle_get_arm_thread_state(tstate, count, getCpuDatap()->cpu_int_state);
		if (rn) return rn;
		break;
	}
	case ARM_THREAD_STATE32:
	{
		kern_return_t rn = handle_get_arm32_thread_state(tstate, count, getCpuDatap()->cpu_int_state);
		if (rn) return rn;
		break;
	}
#if __arm64__
	case ARM_THREAD_STATE64:
	{
		kern_return_t rn = handle_get_arm64_thread_state(tstate, count, getCpuDatap()->cpu_int_state);
		if (rn) return rn;
		break;
	}
#endif
	default:
		return (KERN_INVALID_ARGUMENT);
	}
	return (KERN_SUCCESS);
}