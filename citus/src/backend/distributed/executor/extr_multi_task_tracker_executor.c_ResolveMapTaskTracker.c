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
typedef  int /*<<< orphan*/  TaskTracker ;
typedef  int /*<<< orphan*/  TaskExecution ;
struct TYPE_4__ {scalar_t__ taskType; scalar_t__ dependedTaskList; int /*<<< orphan*/ * taskExecution; } ;
typedef  TYPE_1__ Task ;
typedef  int /*<<< orphan*/  HTAB ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ MAP_OUTPUT_FETCH_TASK ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/ * ResolveTaskTracker (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ linitial (scalar_t__) ; 

__attribute__((used)) static TaskTracker *
ResolveMapTaskTracker(HTAB *trackerHash, Task *task, TaskExecution *taskExecution)
{
	TaskTracker *mapTaskTracker = NULL;
	Task *mapTask = NULL;
	TaskExecution *mapTaskExecution = NULL;

	/* we only resolve source (map) task tracker for map output fetch tasks */
	if (task->taskType != MAP_OUTPUT_FETCH_TASK)
	{
		return NULL;
	}

	Assert(task->dependedTaskList != NIL);
	mapTask = (Task *) linitial(task->dependedTaskList);
	mapTaskExecution = mapTask->taskExecution;

	mapTaskTracker = ResolveTaskTracker(trackerHash, mapTask, mapTaskExecution);
	Assert(mapTaskTracker != NULL);

	return mapTaskTracker;
}