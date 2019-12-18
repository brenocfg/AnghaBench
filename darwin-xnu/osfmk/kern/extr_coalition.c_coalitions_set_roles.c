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
typedef  int /*<<< orphan*/  coalition_t ;

/* Variables and functions */
 int COALITION_NUM_TYPES ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ coal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  coalition_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coalition_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_taskrole ; 

kern_return_t coalitions_set_roles(coalition_t coalitions[COALITION_NUM_TYPES],
				   task_t task, int roles[COALITION_NUM_TYPES])
{
	kern_return_t kr = KERN_SUCCESS;
	int i;

	for (i = 0; i < COALITION_NUM_TYPES; i++) {
		if (!coalitions[i])
			continue;
		coalition_lock(coalitions[i]);
		kr = coal_call(coalitions[i], set_taskrole, task, roles[i]);
		coalition_unlock(coalitions[i]);
		assert(kr == KERN_SUCCESS);
	}

	return kr;
}