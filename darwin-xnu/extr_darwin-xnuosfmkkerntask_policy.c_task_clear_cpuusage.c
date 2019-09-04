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

/* Variables and functions */
 int task_clear_cpuusage_locked (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  task_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_unlock (int /*<<< orphan*/ ) ; 

int
task_clear_cpuusage(task_t task, int cpumon_entitled)
{
	int retval = 0;

	task_lock(task);
	retval = task_clear_cpuusage_locked(task, cpumon_entitled);
	task_unlock(task);

	return(retval);
}