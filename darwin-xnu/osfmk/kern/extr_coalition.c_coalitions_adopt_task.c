#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* task_t ;
typedef  scalar_t__ kern_return_t ;
typedef  TYPE_2__* coalition_t ;
struct TYPE_10__ {scalar_t__ type; } ;
struct TYPE_9__ {scalar_t__* coalition; } ;

/* Variables and functions */
 TYPE_2__* COALITION_NULL ; 
 int COALITION_NUM_TYPES ; 
 size_t COALITION_TYPE_RESOURCE ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ coalition_adopt_task_internal (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  coalition_remove_task_internal (TYPE_1__*,int) ; 

kern_return_t
coalitions_adopt_task(coalition_t *coals, task_t task)
{
	int i;
	kern_return_t kr;

	if (!coals || coals[COALITION_TYPE_RESOURCE] == COALITION_NULL)
		return KERN_INVALID_ARGUMENT;

	/* verify that the incoming coalitions are what they say they are */
	for (i = 0; i < COALITION_NUM_TYPES; i++)
		if (coals[i] && coals[i]->type != (uint32_t)i)
			return KERN_INVALID_ARGUMENT;

	for (i = 0; i < COALITION_NUM_TYPES; i++) {
		kr = KERN_SUCCESS;
		if (coals[i])
			kr = coalition_adopt_task_internal(coals[i], task);
		if (kr != KERN_SUCCESS) {
			/* dis-associate any coalitions that just adopted this task */
			while (--i >= 0) {
				if (task->coalition[i])
					coalition_remove_task_internal(task, i);
			}
			break;
		}
	}
	return kr;
}