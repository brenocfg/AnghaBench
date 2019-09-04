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
typedef  int /*<<< orphan*/  thread_state_t ;
struct TYPE_3__ {int /*<<< orphan*/  fs; int /*<<< orphan*/  es; int /*<<< orphan*/  ss; } ;
typedef  TYPE_1__ mcontext32_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  arm_thread_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_EXCEPTION_STATE ; 
 int /*<<< orphan*/  ARM_EXCEPTION_STATE_COUNT ; 
 int /*<<< orphan*/  ARM_THREAD_STATE ; 
 int /*<<< orphan*/  ARM_THREAD_STATE_COUNT ; 
 int /*<<< orphan*/  ARM_VFP_STATE ; 
 int /*<<< orphan*/  ARM_VFP_STATE_COUNT ; 
 int EINVAL ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_proc () ; 
 scalar_t__ machine_thread_state_convert_to_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_is64bit_data (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_getstatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ thread_getstatus_to_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sendsig_get_state32(thread_t th_act, arm_thread_state_t *ts, mcontext32_t *mcp)
{
	void *tstate;
	mach_msg_type_number_t state_count;

	assert(!proc_is64bit_data(current_proc()));

	tstate = (void *) ts;
	state_count = ARM_THREAD_STATE_COUNT;
	if (thread_getstatus(th_act, ARM_THREAD_STATE, (thread_state_t) tstate, &state_count) != KERN_SUCCESS)
		return EINVAL;

	mcp->ss = *ts;
	tstate = (void *) &mcp->ss;
	state_count = ARM_THREAD_STATE_COUNT;
	if (machine_thread_state_convert_to_user(th_act, ARM_THREAD_STATE, (thread_state_t) tstate, &state_count) != KERN_SUCCESS)
		return EINVAL;

	tstate = (void *) &mcp->es;
	state_count = ARM_EXCEPTION_STATE_COUNT;
	if (thread_getstatus(th_act, ARM_EXCEPTION_STATE, (thread_state_t) tstate, &state_count) != KERN_SUCCESS)
		return EINVAL;

	tstate = (void *) &mcp->fs;
	state_count = ARM_VFP_STATE_COUNT;
	if (thread_getstatus_to_user(th_act, ARM_VFP_STATE, (thread_state_t) tstate, &state_count) != KERN_SUCCESS)
		return EINVAL;

	return 0;
}