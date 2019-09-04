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
typedef  int /*<<< orphan*/  task_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int COALITION_NUM_TYPES ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ coalition_remove_task_internal (int /*<<< orphan*/ ,int) ; 

kern_return_t
coalitions_remove_task(task_t task)
{
	kern_return_t kr;
	int i;

	for (i = 0; i < COALITION_NUM_TYPES; i++) {
		kr = coalition_remove_task_internal(task, i);
		assert(kr == KERN_SUCCESS);
	}

	return kr;
}