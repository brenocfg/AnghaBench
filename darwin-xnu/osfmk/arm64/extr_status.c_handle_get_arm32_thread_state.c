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
typedef  scalar_t__ thread_state_t ;
typedef  scalar_t__ mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  arm_thread_state32_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;

/* Variables and functions */
 scalar_t__ ARM_THREAD_STATE32_COUNT ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  is_saved_state32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  saved_state_to_thread_state32 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

kern_return_t
handle_get_arm32_thread_state(
			 thread_state_t tstate,
			 mach_msg_type_number_t * count,
			 const arm_saved_state_t *saved_state)
{
	if (*count < ARM_THREAD_STATE32_COUNT)
		return (KERN_INVALID_ARGUMENT);
	if (!is_saved_state32(saved_state))
		return (KERN_INVALID_ARGUMENT);

	(void)saved_state_to_thread_state32(saved_state, (arm_thread_state32_t *)tstate);
	*count = ARM_THREAD_STATE32_COUNT;
	return KERN_SUCCESS;
}