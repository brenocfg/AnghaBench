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
struct TYPE_3__ {scalar_t__ taskStatus; scalar_t__ failureCount; int /*<<< orphan*/  taskCallString; } ;
typedef  TYPE_1__ WorkerTask ;
typedef  scalar_t__ TaskStatus ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MaxTaskStringSize ; 
 scalar_t__ TASK_ASSIGNED ; 
 scalar_t__ TASK_CANCELED ; 
 scalar_t__ TASK_CANCEL_REQUESTED ; 
 scalar_t__ TASK_PERMANENTLY_FAILED ; 
 scalar_t__ TASK_STATUS_INVALID_FIRST ; 
 scalar_t__ TASK_SUCCEEDED ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
UpdateTask(WorkerTask *workerTask, char *taskCallString)
{
	TaskStatus taskStatus = TASK_STATUS_INVALID_FIRST;

	taskStatus = workerTask->taskStatus;
	Assert(taskStatus != TASK_STATUS_INVALID_FIRST);

	/*
	 * 1. If the task has succeeded or has been canceled, we don't do anything.
	 * 2. If the task has permanently failed, we update the task call string,
	 * reset the failure count, and change the task's status to schedulable.
	 * 3. If the task is in conduit, we update the task call string, and reset
	 * the failure count.
	 */
	if (taskStatus == TASK_SUCCEEDED || taskStatus == TASK_CANCEL_REQUESTED ||
		taskStatus == TASK_CANCELED)
	{
		/* nothing to do */
	}
	else if (taskStatus == TASK_PERMANENTLY_FAILED)
	{
		strlcpy(workerTask->taskCallString, taskCallString, MaxTaskStringSize);
		workerTask->failureCount = 0;
		workerTask->taskStatus = TASK_ASSIGNED;
	}
	else
	{
		strlcpy(workerTask->taskCallString, taskCallString, MaxTaskStringSize);
		workerTask->failureCount = 0;
	}
}