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
typedef  scalar_t__ thread_state_t ;
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  arm_debug_state_t ;
struct TYPE_3__ {int /*<<< orphan*/ * task_debug; } ;

/* Variables and functions */
#define  ARM_DEBUG_STATE 129 
 int /*<<< orphan*/  ARM_DEBUG_STATE_COUNT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
#define  THREAD_STATE_NONE 128 
 int /*<<< orphan*/  ads_zone ; 
 int /*<<< orphan*/  copy_debug_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
machine_task_set_state(
		task_t task, 
		int flavor,
		thread_state_t state, 
		mach_msg_type_number_t state_count)
{
	switch (flavor) {
	case ARM_DEBUG_STATE:
	{
		arm_debug_state_t *tstate = (arm_debug_state_t *) state;
		
		if (state_count != ARM_DEBUG_STATE_COUNT) {
			return KERN_INVALID_ARGUMENT;
		}
		
		if (task->task_debug == NULL) {
			task->task_debug = zalloc(ads_zone);
			if (task->task_debug == NULL)
				return KERN_FAILURE;
		}
		
		copy_debug_state(tstate, (arm_debug_state_t*) task->task_debug, FALSE);
		
		return KERN_SUCCESS;
	}
	case THREAD_STATE_NONE:		/* Using this flavor to clear task_debug */
	{
		if (task->task_debug != NULL) {
			zfree(ads_zone, task->task_debug);
			task->task_debug = NULL;
			
			return KERN_SUCCESS;
		}
		return KERN_FAILURE;
	}
	default:
	  {
		return KERN_INVALID_ARGUMENT;
	  }
	}

	return KERN_FAILURE;
}