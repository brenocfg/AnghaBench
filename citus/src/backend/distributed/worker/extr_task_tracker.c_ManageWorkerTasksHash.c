#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ taskStatus; } ;
typedef  TYPE_1__ WorkerTask ;
struct TYPE_6__ {int /*<<< orphan*/  taskHashLock; int /*<<< orphan*/  conninfosValid; } ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidateConnParamsHashEntries () ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  ManageWorkerTask (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  RemoveWorkerTask (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SchedulableTaskList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScheduleWorkerTasks (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TASK_TO_REMOVE ; 
 TYPE_2__* WorkerTasksSharedState ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_free_deep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ManageWorkerTasksHash(HTAB *WorkerTasksHash)
{
	HASH_SEQ_STATUS status;
	List *schedulableTaskList = NIL;
	WorkerTask *currentTask = NULL;

	/* ask the scheduler if we have new tasks to schedule */
	LWLockAcquire(&WorkerTasksSharedState->taskHashLock, LW_SHARED);
	schedulableTaskList = SchedulableTaskList(WorkerTasksHash);
	LWLockRelease(&WorkerTasksSharedState->taskHashLock);

	LWLockAcquire(&WorkerTasksSharedState->taskHashLock, LW_EXCLUSIVE);

	if (!WorkerTasksSharedState->conninfosValid)
	{
		InvalidateConnParamsHashEntries();
	}

	/* schedule new tasks if we have any */
	if (schedulableTaskList != NIL)
	{
		ScheduleWorkerTasks(WorkerTasksHash, schedulableTaskList);
		list_free_deep(schedulableTaskList);
	}

	/* now iterate over all tasks, and manage them */
	hash_seq_init(&status, WorkerTasksHash);

	currentTask = (WorkerTask *) hash_seq_search(&status);
	while (currentTask != NULL)
	{
		ManageWorkerTask(currentTask, WorkerTasksHash);

		/*
		 * Typically, we delete worker tasks in the task tracker protocol
		 * process. This task however was canceled mid-query, and the protocol
		 * process asked us to remove it from the shared hash.
		 */
		if (currentTask->taskStatus == TASK_TO_REMOVE)
		{
			RemoveWorkerTask(currentTask, WorkerTasksHash);
		}

		currentTask = (WorkerTask *) hash_seq_search(&status);
	}

	LWLockRelease(&WorkerTasksSharedState->taskHashLock);
}