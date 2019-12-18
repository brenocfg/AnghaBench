#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ thread_state_t ;
typedef  scalar_t__ mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {int /*<<< orphan*/  count; int /*<<< orphan*/  flavor; } ;
struct TYPE_7__ {TYPE_1__ ash; } ;
typedef  TYPE_2__ arm_unified_thread_state_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_THREAD_STATE32 ; 
 int /*<<< orphan*/  ARM_THREAD_STATE32_COUNT ; 
 int /*<<< orphan*/  ARM_THREAD_STATE64 ; 
 int /*<<< orphan*/  ARM_THREAD_STATE64_COUNT ; 
 scalar_t__ ARM_UNIFIED_THREAD_STATE_COUNT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  handle_get_arm32_thread_state (scalar_t__,scalar_t__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ is_saved_state64 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  saved_state_to_thread_state32 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saved_state_to_thread_state64 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_state32 (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_state64 (TYPE_2__*) ; 

kern_return_t
handle_get_arm_thread_state(
			 thread_state_t tstate,
			 mach_msg_type_number_t * count,
			 const arm_saved_state_t *saved_state)
{
	/* In an arm64 world, this flavor can be used to retrieve the thread
	 * state of a 32-bit or 64-bit thread into a unified structure, but we
	 * need to support legacy clients who are only aware of 32-bit, so
	 * check the count to see what the client is expecting.
	 */
	if (*count < ARM_UNIFIED_THREAD_STATE_COUNT) {
		return handle_get_arm32_thread_state(tstate, count, saved_state);
	}

	arm_unified_thread_state_t *unified_state = (arm_unified_thread_state_t *) tstate;
	bzero(unified_state, sizeof(*unified_state));
#if __arm64__
	if (is_saved_state64(saved_state)) {
		unified_state->ash.flavor = ARM_THREAD_STATE64;
		unified_state->ash.count = ARM_THREAD_STATE64_COUNT;
		(void)saved_state_to_thread_state64(saved_state, thread_state64(unified_state));
	} else
#endif
	{
		unified_state->ash.flavor = ARM_THREAD_STATE32;
		unified_state->ash.count = ARM_THREAD_STATE32_COUNT;
		(void)saved_state_to_thread_state32(saved_state, thread_state32(unified_state));
	}
	*count = ARM_UNIFIED_THREAD_STATE_COUNT;
	return (KERN_SUCCESS);
}