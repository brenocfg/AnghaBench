#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ thread_state_t ;
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  arm_legacy_debug_state_t ;
typedef  int /*<<< orphan*/  arm_debug_state64_t ;
typedef  int /*<<< orphan*/  arm_debug_state32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * task_debug; } ;

/* Variables and functions */
#define  ARM_DEBUG_STATE 130 
#define  ARM_DEBUG_STATE32 129 
 int /*<<< orphan*/  ARM_DEBUG_STATE32_COUNT ; 
#define  ARM_DEBUG_STATE64 128 
 int /*<<< orphan*/  ARM_DEBUG_STATE64_COUNT ; 
 int /*<<< orphan*/  ARM_LEGACY_DEBUG_STATE_COUNT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  bzero (scalar_t__,int) ; 
 int /*<<< orphan*/  copy_debug_state32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_debug_state64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_legacy_debug_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_has_64Bit_data (TYPE_1__*) ; 

kern_return_t 	
machine_task_get_state(task_t task, 
		int flavor, 
		thread_state_t state,
		mach_msg_type_number_t *state_count)
{
	switch (flavor) {
	case ARM_DEBUG_STATE:
	{
		arm_legacy_debug_state_t *tstate = (arm_legacy_debug_state_t *) state;
		
		if (task_has_64Bit_data(task) || (*state_count != ARM_LEGACY_DEBUG_STATE_COUNT)) {
			return KERN_INVALID_ARGUMENT;
		}
		
		if (task->task_debug == NULL) {
			bzero(state, sizeof(*tstate));		
		} else {
			copy_legacy_debug_state((arm_legacy_debug_state_t*) task->task_debug, tstate, FALSE); /* FALSE OR TRUE doesn't matter since we are ignoring it for arm */
		} 
		
		return KERN_SUCCESS;
	}
	case ARM_DEBUG_STATE32:
	{
		arm_debug_state32_t *tstate = (arm_debug_state32_t *) state;
		
		if (task_has_64Bit_data(task) || (*state_count != ARM_DEBUG_STATE32_COUNT)) {
			return KERN_INVALID_ARGUMENT;
		}
		
		if (task->task_debug == NULL) {
			bzero(state, sizeof(*tstate));		
		} else {
			copy_debug_state32((arm_debug_state32_t*) task->task_debug, tstate, FALSE); /* FALSE OR TRUE doesn't matter since we are ignoring it for arm */
		} 
		
		return KERN_SUCCESS;
	}
	case ARM_DEBUG_STATE64:
	{
		arm_debug_state64_t *tstate = (arm_debug_state64_t *) state;
		
		if ((!task_has_64Bit_data(task)) || (*state_count != ARM_DEBUG_STATE64_COUNT)) {
			return KERN_INVALID_ARGUMENT;
		}
		
		if (task->task_debug == NULL) {
			bzero(state, sizeof(*tstate));		
		} else {
			copy_debug_state64((arm_debug_state64_t*) task->task_debug, tstate, FALSE); /* FALSE OR TRUE doesn't matter since we are ignoring it for arm */
		} 
		
		return KERN_SUCCESS;
	}
	default:
	  {
		return KERN_INVALID_ARGUMENT;
	  }

	}
	return KERN_FAILURE;
}