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
typedef  int /*<<< orphan*/  uint64 ;
typedef  scalar_t__ uint32 ;
struct TYPE_3__ {int /*<<< orphan*/  userName; int /*<<< orphan*/  databaseName; scalar_t__ failureCount; int /*<<< orphan*/  connectionId; int /*<<< orphan*/  taskStatus; int /*<<< orphan*/  taskCallString; scalar_t__ assignedAt; } ;
typedef  TYPE_1__ WorkerTask ;

/* Variables and functions */
 char* CurrentDatabaseName () ; 
 char* CurrentUserName () ; 
 scalar_t__ HIGH_PRIORITY_TASK_TIME ; 
 int /*<<< orphan*/  INVALID_CONNECTION_ID ; 
 scalar_t__ JOB_CLEANUP_TASK_ID ; 
 int /*<<< orphan*/  MaxTaskStringSize ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  TASK_ASSIGNED ; 
 TYPE_1__* WorkerTasksHashEnter (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
CreateTask(uint64 jobId, uint32 taskId, char *taskCallString)
{
	WorkerTask *workerTask = NULL;
	uint32 assignmentTime = 0;
	char *databaseName = CurrentDatabaseName();
	char *userName = CurrentUserName();

	/* increase task priority for cleanup tasks */
	assignmentTime = (uint32) time(NULL);
	if (taskId == JOB_CLEANUP_TASK_ID)
	{
		assignmentTime = HIGH_PRIORITY_TASK_TIME;
	}

	/* enter the worker task into shared hash and initialize the task */
	workerTask = WorkerTasksHashEnter(jobId, taskId);
	workerTask->assignedAt = assignmentTime;
	strlcpy(workerTask->taskCallString, taskCallString, MaxTaskStringSize);

	workerTask->taskStatus = TASK_ASSIGNED;
	workerTask->connectionId = INVALID_CONNECTION_ID;
	workerTask->failureCount = 0;
	strlcpy(workerTask->databaseName, databaseName, NAMEDATALEN);
	strlcpy(workerTask->userName, userName, NAMEDATALEN);
}