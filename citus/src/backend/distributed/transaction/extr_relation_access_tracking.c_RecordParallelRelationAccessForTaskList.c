#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ taskType; scalar_t__ rowValuesLists; } ;
typedef  TYPE_1__ Task ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ MODIFY_TASK ; 
 scalar_t__ MultiShardConnectionType ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  RecordRelationParallelDDLAccessForTask (TYPE_1__*) ; 
 int /*<<< orphan*/  RecordRelationParallelModifyAccessForTask (TYPE_1__*) ; 
 int /*<<< orphan*/  RecordRelationParallelSelectAccessForTask (TYPE_1__*) ; 
 scalar_t__ SEQUENTIAL_CONNECTION ; 
 scalar_t__ SQL_TASK ; 
 TYPE_1__* linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 

void
RecordParallelRelationAccessForTaskList(List *taskList)
{
	Task *firstTask = NULL;

	if (MultiShardConnectionType == SEQUENTIAL_CONNECTION)
	{
		/* sequential mode prevents parallel access */
		return;
	}

	if (list_length(taskList) < 2)
	{
		/* single shard task doesn't mean parallel access in our definition */
		return;
	}

	/*
	 * Since all the tasks in a task list is expected to operate on the same
	 * distributed table(s), we only need to process the first task.
	 */
	firstTask = linitial(taskList);

	if (firstTask->taskType == SQL_TASK)
	{
		RecordRelationParallelSelectAccessForTask(firstTask);
	}
	else if (firstTask->taskType == MODIFY_TASK)
	{
		if (firstTask->rowValuesLists != NIL)
		{
			/*
			 * We always run multi-row INSERTs in a sequential
			 * mode (hard-coded). Thus, we do not mark as parallel
			 * access even if the prerequisites hold.
			 */
		}
		else
		{
			/*
			 * We prefer to mark with all remaining multi-shard modifications
			 * with both modify and select accesses.
			 */
			RecordRelationParallelModifyAccessForTask(firstTask);
			RecordRelationParallelSelectAccessForTask(firstTask);
		}
	}
	else
	{
		RecordRelationParallelDDLAccessForTask(firstTask);
	}
}