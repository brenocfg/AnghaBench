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
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ coalitions_adopt_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_coalition ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,scalar_t__) ; 

kern_return_t
coalitions_adopt_init_task(task_t task)
{
	kern_return_t kr;
	kr = coalitions_adopt_task(init_coalition, task);
	if (kr != KERN_SUCCESS) {
		panic("failed to adopt task %p into default coalition: %d", task, kr);
	}
	return kr;
}