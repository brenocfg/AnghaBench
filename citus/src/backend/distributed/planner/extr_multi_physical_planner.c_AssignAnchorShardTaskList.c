#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * FirstReplicaAssignTaskList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GreedyAssignTaskList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * RoundRobinAssignTaskList (int /*<<< orphan*/ *) ; 
 scalar_t__ TASK_ASSIGNMENT_FIRST_REPLICA ; 
 scalar_t__ TASK_ASSIGNMENT_GREEDY ; 
 scalar_t__ TASK_ASSIGNMENT_ROUND_ROBIN ; 
 scalar_t__ TaskAssignmentPolicy ; 

List *
AssignAnchorShardTaskList(List *taskList)
{
	List *assignedTaskList = NIL;

	/* choose task assignment policy based on config value */
	if (TaskAssignmentPolicy == TASK_ASSIGNMENT_GREEDY)
	{
		assignedTaskList = GreedyAssignTaskList(taskList);
	}
	else if (TaskAssignmentPolicy == TASK_ASSIGNMENT_FIRST_REPLICA)
	{
		assignedTaskList = FirstReplicaAssignTaskList(taskList);
	}
	else if (TaskAssignmentPolicy == TASK_ASSIGNMENT_ROUND_ROBIN)
	{
		assignedTaskList = RoundRobinAssignTaskList(taskList);
	}

	Assert(assignedTaskList != NIL);
	return assignedTaskList;
}