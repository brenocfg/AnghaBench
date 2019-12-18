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
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  roles ;
struct TYPE_4__ {scalar_t__* coalition; } ;

/* Variables and functions */
 int COALITION_NUM_TYPES ; 
 int COALITION_TASKROLE_NONE ; 
 int coal_call (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  coalition_lock (scalar_t__) ; 
 int /*<<< orphan*/  coalition_unlock (scalar_t__) ; 
 int /*<<< orphan*/  get_taskrole ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void
task_coalition_roles(task_t task, int roles[COALITION_NUM_TYPES])
{
	int i;
	memset(roles, 0, COALITION_NUM_TYPES * sizeof(roles[0]));

	for (i = 0; i < COALITION_NUM_TYPES; i++) {
		if (task->coalition[i]) {
			coalition_lock(task->coalition[i]);
			roles[i] = coal_call(task->coalition[i],
					     get_taskrole, task);
			coalition_unlock(task->coalition[i]);
		} else {
			roles[i] = COALITION_TASKROLE_NONE;
		}
	}
}