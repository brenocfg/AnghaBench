#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_13__ {void* status; } ;
typedef  TYPE_1__ TrackerTaskState ;
struct TYPE_14__ {int connectionBusy; int /*<<< orphan*/ * connectionBusyOnTaskList; int /*<<< orphan*/  connectionId; int /*<<< orphan*/ * assignedTaskList; } ;
typedef  TYPE_2__ TaskTracker ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__* StringInfo ;
typedef  scalar_t__ ResultStatus ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * AssignQueuedTasks (TYPE_2__*) ; 
 scalar_t__ CLIENT_INVALID_RESULT_STATUS ; 
 scalar_t__ CLIENT_RESULT_BUSY ; 
 scalar_t__ CLIENT_RESULT_READY ; 
 scalar_t__ CLIENT_RESULT_UNAVAILABLE ; 
 scalar_t__ MultiClientResultStatus (int /*<<< orphan*/ ) ; 
 int MultiClientSendQuery (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* NIL ; 
 int /*<<< orphan*/  ReceiveTaskStatusBatchQueryResponse (TYPE_2__*) ; 
 void* TASK_CLIENT_SIDE_STATUS_FAILED ; 
 int /*<<< orphan*/ * TaskStatusBatchList (TYPE_2__*) ; 
 TYPE_3__* TaskStatusBatchQuery (int /*<<< orphan*/ *) ; 
 int TrackerConnectionUp (TYPE_2__*) ; 
 int TrackerHealthy (TYPE_2__*) ; 
 int /*<<< orphan*/  TrackerReconnectPoll (TYPE_2__*) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 

__attribute__((used)) static void
ManageTaskTracker(TaskTracker *taskTracker)
{
	bool trackerConnectionUp = false;
	bool trackerHealthy = false;

	trackerHealthy = TrackerHealthy(taskTracker);
	if (!trackerHealthy)
	{
		return;
	}

	trackerConnectionUp = TrackerConnectionUp(taskTracker);
	if (!trackerConnectionUp)
	{
		TrackerReconnectPoll(taskTracker);  /* try an async reconnect */
		return;
	}

	/*
	 * (1) We first synchronously assign any pending new tasks. We also make
	 * sure not to block execution on one task tracker for a long time.
	 */
	if (!taskTracker->connectionBusy)
	{
		List *previousTaskList = taskTracker->assignedTaskList;
		List *newTaskList = AssignQueuedTasks(taskTracker);

		taskTracker->assignedTaskList = list_concat(previousTaskList, newTaskList);
	}

	/*
	 * (2) We find assigned tasks. We then send an asynchronous query to check
	 * the tasks' statuses.
	 */
	if (!taskTracker->connectionBusy)
	{
		List *taskStatusBatchList = TaskStatusBatchList(taskTracker);

		/* if we have running tasks, check their status */
		if (taskStatusBatchList)
		{
			int32 connectionId = taskTracker->connectionId;
			StringInfo taskStatusBatchQuery = NULL;
			bool querySent = false;

			taskStatusBatchQuery = TaskStatusBatchQuery(taskStatusBatchList);

			querySent = MultiClientSendQuery(connectionId, taskStatusBatchQuery->data);
			if (querySent)
			{
				taskTracker->connectionBusy = true;
				taskTracker->connectionBusyOnTaskList = taskStatusBatchList;
			}
			else
			{
				/* mark only first task in list as failed */
				TrackerTaskState *taskState = (TrackerTaskState *) linitial(
					taskStatusBatchList);
				taskState->status = TASK_CLIENT_SIDE_STATUS_FAILED;

				list_free(taskStatusBatchList);

				taskTracker->connectionBusy = false;
				taskTracker->connectionBusyOnTaskList = NIL;
			}

			pfree(taskStatusBatchQuery);
		}
	}

	/*
	 * (3) check if results are ready for previously issued task status query
	 */
	if (taskTracker->connectionBusy)
	{
		int32 connectionId = taskTracker->connectionId;
		ResultStatus resultStatus = CLIENT_INVALID_RESULT_STATUS;

		/* if connection is available, update task status accordingly */
		resultStatus = MultiClientResultStatus(connectionId);
		if (resultStatus == CLIENT_RESULT_READY)
		{
			ReceiveTaskStatusBatchQueryResponse(taskTracker);
		}
		else if (resultStatus == CLIENT_RESULT_UNAVAILABLE)
		{
			TrackerTaskState *taskState = (TrackerTaskState *) linitial(
				taskTracker->connectionBusyOnTaskList);
			Assert(taskState != NULL);
			taskState->status = TASK_CLIENT_SIDE_STATUS_FAILED;
		}

		/* if connection is available, give it back to the task tracker */
		if (resultStatus != CLIENT_RESULT_BUSY)
		{
			list_free(taskTracker->connectionBusyOnTaskList);

			taskTracker->connectionBusy = false;
			taskTracker->connectionBusyOnTaskList = NIL;
		}
	}
}