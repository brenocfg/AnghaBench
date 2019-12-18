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
typedef  size_t HvLpEvent_Type ;

/* Variables and functions */
 size_t HvLpEvent_Type_NumTypes ; 
 int /*<<< orphan*/ ** lpEventHandler ; 
 int /*<<< orphan*/ * lpEventHandlerPaths ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  synchronize_sched () ; 

int HvLpEvent_unregisterHandler(HvLpEvent_Type eventType)
{
	might_sleep();

	if (eventType < HvLpEvent_Type_NumTypes) {
		if (!lpEventHandlerPaths[eventType]) {
			lpEventHandler[eventType] = NULL;
			/*
			 * We now sleep until all other CPUs have scheduled.
			 * This ensures that the deletion is seen by all
			 * other CPUs, and that the deleted handler isn't
			 * still running on another CPU when we return.
			 */
			synchronize_sched();
			return 0;
		}
	}
	return 1;
}