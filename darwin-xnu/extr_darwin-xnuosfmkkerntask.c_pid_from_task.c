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
struct TYPE_4__ {scalar_t__ bsd_info; } ;

/* Variables and functions */
 int proc_pid (scalar_t__) ; 
 int task_pid (TYPE_1__*) ; 

int pid_from_task(task_t task)
{
	int pid = -1;

	if (task->bsd_info) {
		pid = proc_pid(task->bsd_info);
	} else {
		pid = task_pid(task);
	}

	return pid;
}