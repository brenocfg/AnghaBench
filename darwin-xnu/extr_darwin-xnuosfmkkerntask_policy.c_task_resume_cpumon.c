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
typedef  int kern_return_t ;

/* Variables and functions */
 int EINVAL ; 
 int task_enable_cpumon_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_unlock (int /*<<< orphan*/ ) ; 

int
task_resume_cpumon(task_t task)
{
	kern_return_t kret;

	if (!task) {
		return EINVAL;
	}

	task_lock(task);
	kret = task_enable_cpumon_locked(task);
	task_unlock(task);

	return kret;
}