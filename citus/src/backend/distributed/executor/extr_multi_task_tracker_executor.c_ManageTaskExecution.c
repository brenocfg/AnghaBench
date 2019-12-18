#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
typedef  int /*<<< orphan*/  TaskType ;
struct TYPE_20__ {int /*<<< orphan*/  trackerFailureCount; } ;
typedef  TYPE_1__ TaskTracker ;
typedef  int /*<<< orphan*/  TaskStatus ;
struct TYPE_21__ {int* taskStatusArray; size_t currentNodeIndex; size_t querySourceNodeIndex; } ;
typedef  TYPE_2__ TaskExecution ;
typedef  int TaskExecStatus ;
struct TYPE_22__ {int /*<<< orphan*/  taskType; TYPE_2__* taskExecution; int /*<<< orphan*/  dependedTaskList; int /*<<< orphan*/  queryString; } ;
typedef  TYPE_3__ Task ;
struct TYPE_23__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_4__* StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
#define  EXEC_SOURCE_TASK_TRACKER_FAILED 134 
#define  EXEC_SOURCE_TASK_TRACKER_RETRY 133 
#define  EXEC_TASK_DONE 132 
 int EXEC_TASK_INVALID_FIRST ; 
#define  EXEC_TASK_QUEUED 131 
#define  EXEC_TASK_TRACKER_FAILED 130 
#define  EXEC_TASK_TRACKER_RETRY 129 
#define  EXEC_TASK_UNASSIGNED 128 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  MAP_OUTPUT_FETCH_TASK ; 
 TYPE_4__* MapFetchTaskQueryString (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  SQL_TASK ; 
 int /*<<< orphan*/  TASK_CLIENT_SIDE_ASSIGN_FAILED ; 
 int /*<<< orphan*/  TASK_CLIENT_SIDE_STATUS_FAILED ; 
 int /*<<< orphan*/  TASK_PERMANENTLY_FAILED ; 
 int /*<<< orphan*/  TASK_STATUS_INVALID_FIRST ; 
 int /*<<< orphan*/  TASK_SUCCEEDED ; 
 int /*<<< orphan*/  TASK_TYPE_INVALID_FIRST ; 
 int TaskExecutionsCompleted (int /*<<< orphan*/ ) ; 
 int TrackerConnectionUp (TYPE_1__*) ; 
 int TrackerHealthy (TYPE_1__*) ; 
 int /*<<< orphan*/  TrackerQueueSqlTask (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  TrackerQueueTask (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  TrackerTaskStatus (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 
 scalar_t__ linitial (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TaskExecStatus
ManageTaskExecution(TaskTracker *taskTracker, TaskTracker *sourceTaskTracker,
					Task *task, TaskExecution *taskExecution)
{
	TaskExecStatus *taskStatusArray = taskExecution->taskStatusArray;
	uint32 currentNodeIndex = taskExecution->currentNodeIndex;
	uint32 nextNodeIndex = 0;

	TaskExecStatus currentExecutionStatus = taskStatusArray[currentNodeIndex];
	TaskExecStatus nextExecutionStatus = EXEC_TASK_INVALID_FIRST;

	switch (currentExecutionStatus)
	{
		case EXEC_TASK_UNASSIGNED:
		{
			bool taskExecutionsCompleted = true;
			TaskType taskType = TASK_TYPE_INVALID_FIRST;

			bool trackerHealthy = TrackerHealthy(taskTracker);
			if (!trackerHealthy)
			{
				nextExecutionStatus = EXEC_TASK_TRACKER_FAILED;
				break;
			}

			/*
			 * We first retrieve this task's downstream dependencies, and then check
			 * if these dependencies' executions have completed.
			 */
			taskExecutionsCompleted = TaskExecutionsCompleted(task->dependedTaskList);
			if (!taskExecutionsCompleted)
			{
				nextExecutionStatus = EXEC_TASK_UNASSIGNED;
				break;
			}

			/* if map fetch task, create query string from completed map task */
			taskType = task->taskType;
			if (taskType == MAP_OUTPUT_FETCH_TASK)
			{
				StringInfo mapFetchTaskQueryString = NULL;
				Task *mapTask = (Task *) linitial(task->dependedTaskList);
				TaskExecution *mapTaskExecution = mapTask->taskExecution;

				mapFetchTaskQueryString = MapFetchTaskQueryString(task, mapTask);
				task->queryString = mapFetchTaskQueryString->data;
				taskExecution->querySourceNodeIndex = mapTaskExecution->currentNodeIndex;
			}

			/*
			 * We finally queue this task for execution. Note that we queue sql and
			 * other tasks slightly differently.
			 */
			if (taskType == SQL_TASK)
			{
				TrackerQueueSqlTask(taskTracker, task);
			}
			else
			{
				TrackerQueueTask(taskTracker, task);
			}

			nextExecutionStatus = EXEC_TASK_QUEUED;
			break;
		}

		case EXEC_TASK_QUEUED:
		{
			TaskStatus remoteTaskStatus = TASK_STATUS_INVALID_FIRST;

			bool trackerHealthy = TrackerHealthy(taskTracker);
			if (!trackerHealthy)
			{
				nextExecutionStatus = EXEC_TASK_TRACKER_FAILED;
				break;
			}

			remoteTaskStatus = TrackerTaskStatus(taskTracker, task);
			if (remoteTaskStatus == TASK_SUCCEEDED)
			{
				nextExecutionStatus = EXEC_TASK_DONE;
			}
			else if (remoteTaskStatus == TASK_CLIENT_SIDE_ASSIGN_FAILED ||
					 remoteTaskStatus == TASK_CLIENT_SIDE_STATUS_FAILED)
			{
				nextExecutionStatus = EXEC_TASK_TRACKER_RETRY;
			}
			else if (remoteTaskStatus == TASK_PERMANENTLY_FAILED)
			{
				/*
				 * If a map output fetch task failed, we assume the problem lies with
				 * the map task (and the source task tracker it runs on). Otherwise,
				 * we assume the task tracker crashed, and fail over to the next task
				 * tracker.
				 */
				if (task->taskType == MAP_OUTPUT_FETCH_TASK)
				{
					nextExecutionStatus = EXEC_SOURCE_TASK_TRACKER_RETRY;
				}
				else
				{
					nextExecutionStatus = EXEC_TASK_TRACKER_FAILED;
				}
			}
			else
			{
				/* assume task is still in progress */
				nextExecutionStatus = EXEC_TASK_QUEUED;
			}

			break;
		}

		case EXEC_TASK_TRACKER_RETRY:
		{
			bool trackerHealthy = false;
			bool trackerConnectionUp = false;

			/*
			 * This case statement usually handles connection related issues. Some
			 * edge cases however, like a user sending a SIGTERM to the worker node,
			 * keep the connection open but disallow task assignments. We therefore
			 * need to track those as intermittent tracker failures here.
			 */
			trackerConnectionUp = TrackerConnectionUp(taskTracker);
			if (trackerConnectionUp)
			{
				taskTracker->trackerFailureCount++;
			}

			trackerHealthy = TrackerHealthy(taskTracker);
			if (trackerHealthy)
			{
				TaskStatus remoteTaskStatus = TrackerTaskStatus(taskTracker, task);
				if (remoteTaskStatus == TASK_CLIENT_SIDE_ASSIGN_FAILED)
				{
					nextExecutionStatus = EXEC_TASK_UNASSIGNED;
				}
				else if (remoteTaskStatus == TASK_CLIENT_SIDE_STATUS_FAILED)
				{
					nextExecutionStatus = EXEC_TASK_QUEUED;
				}
			}
			else
			{
				nextExecutionStatus = EXEC_TASK_TRACKER_FAILED;
			}

			break;
		}

		case EXEC_SOURCE_TASK_TRACKER_RETRY:
		{
			Task *mapTask = (Task *) linitial(task->dependedTaskList);
			TaskExecution *mapTaskExecution = mapTask->taskExecution;
			uint32 sourceNodeIndex = mapTaskExecution->currentNodeIndex;

			bool sourceTrackerHealthy = false;
			Assert(sourceTaskTracker != NULL);
			Assert(task->taskType == MAP_OUTPUT_FETCH_TASK);

			/*
			 * As this map fetch task was running, another map fetch that depends on
			 * another map task might have failed. We would have then reassigned the
			 * map task and potentially other map tasks in its constraint group. So
			 * this map fetch's source node might have changed underneath us. If it
			 * did, we don't want to record a failure for the new source tracker.
			 */
			if (taskExecution->querySourceNodeIndex == sourceNodeIndex)
			{
				bool sourceTrackerConnectionUp = TrackerConnectionUp(sourceTaskTracker);
				if (sourceTrackerConnectionUp)
				{
					sourceTaskTracker->trackerFailureCount++;
				}
			}

			sourceTrackerHealthy = TrackerHealthy(sourceTaskTracker);
			if (sourceTrackerHealthy)
			{
				/*
				 * We change our status to unassigned. In that status, we queue an
				 * "update map fetch task" on the task tracker, and retry fetching
				 * the map task's output from the same source node.
				 */
				nextExecutionStatus = EXEC_TASK_UNASSIGNED;
			}
			else
			{
				nextExecutionStatus = EXEC_SOURCE_TASK_TRACKER_FAILED;
			}

			break;
		}

		case EXEC_TASK_TRACKER_FAILED:
		case EXEC_SOURCE_TASK_TRACKER_FAILED:
		{
			/*
			 * These two cases exist to signal to the caller that we failed. In both
			 * cases, the caller is responsible for reassigning task(s) and running
			 * the appropriate recovery logic.
			 */
			nextExecutionStatus = EXEC_TASK_UNASSIGNED;
			break;
		}

		case EXEC_TASK_DONE:
		{
			/* we are done with this task's execution */
			nextExecutionStatus = EXEC_TASK_DONE;
			break;
		}

		default:
		{
			/* we fatal here to avoid leaking client-side resources */
			ereport(FATAL, (errmsg("invalid execution status: %d",
								   currentExecutionStatus)));
			break;
		}
	}

	/* update task execution's status for most recent task tracker */
	nextNodeIndex = taskExecution->currentNodeIndex;
	taskStatusArray[nextNodeIndex] = nextExecutionStatus;

	return nextExecutionStatus;
}