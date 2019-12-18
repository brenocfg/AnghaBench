#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ taskStatus; } ;
typedef  TYPE_1__ WorkerTask ;
typedef  scalar_t__ TaskStatus ;

/* Variables and functions */
 scalar_t__ TASK_RUNNING ; 

__attribute__((used)) static bool
RunningTask(WorkerTask *workerTask)
{
	TaskStatus currentStatus = workerTask->taskStatus;
	if (currentStatus == TASK_RUNNING)
	{
		return true;
	}

	return false;
}