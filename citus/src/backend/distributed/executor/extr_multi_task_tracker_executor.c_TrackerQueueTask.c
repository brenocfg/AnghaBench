#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * taskAssignmentQuery; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ TrackerTaskState ;
struct TYPE_9__ {int /*<<< orphan*/ * taskStateHash; } ;
typedef  TYPE_2__ TaskTracker ;
struct TYPE_10__ {int /*<<< orphan*/  taskId; int /*<<< orphan*/  jobId; int /*<<< orphan*/  queryString; } ;
typedef  TYPE_3__ Task ;
typedef  int /*<<< orphan*/ * StringInfo ;
typedef  int /*<<< orphan*/  HTAB ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_CLIENT_SIDE_QUEUED ; 
 int /*<<< orphan*/ * TaskAssignmentQuery (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TaskStateHashEnter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
TrackerQueueTask(TaskTracker *taskTracker, Task *task)
{
	HTAB *taskStateHash = taskTracker->taskStateHash;
	TrackerTaskState *taskState = NULL;
	StringInfo taskAssignmentQuery = NULL;

	/* wrap a task assignment query outside the original query */
	taskAssignmentQuery = TaskAssignmentQuery(task, task->queryString);

	taskState = TaskStateHashEnter(taskStateHash, task->jobId, task->taskId);
	taskState->status = TASK_CLIENT_SIDE_QUEUED;
	taskState->taskAssignmentQuery = taskAssignmentQuery;
}