#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
struct TYPE_5__ {scalar_t__ rusage_cpu_perthr_interval; scalar_t__ rusage_cpu_perthr_percentage; } ;

/* Variables and functions */
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  task_lock_assert_owned (TYPE_1__*) ; 
 int task_suspend_cpumon (TYPE_1__*) ; 

int
task_disable_cpumon(task_t task)
{
	int kret;

	task_lock_assert_owned(task);

	kret = task_suspend_cpumon(task);
	if (kret)		return kret;

	/* Once we clear these values, the monitor can't be resumed */
	task->rusage_cpu_perthr_percentage = 0;
	task->rusage_cpu_perthr_interval = 0;

	return (KERN_SUCCESS);
}