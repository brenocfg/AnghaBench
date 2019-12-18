#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ TaskAssignmentPolicyType ;
struct TYPE_6__ {int /*<<< orphan*/  taskId; int /*<<< orphan*/ * taskPlacementList; int /*<<< orphan*/  taskType; } ;
typedef  TYPE_1__ Task ;
struct TYPE_8__ {int /*<<< orphan*/ * taskList; } ;
struct TYPE_7__ {int /*<<< orphan*/  nodePort; int /*<<< orphan*/  nodeName; } ;
typedef  TYPE_2__ ShardPlacement ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEBUG3 ; 
 int /*<<< orphan*/ * NIL ; 
 int ReadOnlyTask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RemoveCoordinatorPlacement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RoundRobinReorder (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ TASK_ASSIGNMENT_ROUND_ROBIN ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ReorderTaskPlacementsByTaskAssignmentPolicy(Job *job,
											TaskAssignmentPolicyType taskAssignmentPolicy,
											List *placementList)
{
	if (taskAssignmentPolicy == TASK_ASSIGNMENT_ROUND_ROBIN)
	{
		Task *task = NULL;
		List *reorderedPlacementList = NIL;
		ShardPlacement *primaryPlacement = NULL;

		/*
		 * We hit a single shard on router plans, and there should be only
		 * one task in the task list
		 */
		Assert(list_length(job->taskList) == 1);
		task = (Task *) linitial(job->taskList);

		/*
		 * For round-robin SELECT queries, we don't want to include the coordinator
		 * because the user is trying to distributed the load across nodes via
		 * round-robin policy. Otherwise, the local execution would prioritize
		 * executing the local tasks and especially for reference tables on the
		 * coordinator this would prevent load balancing accross nodes.
		 *
		 * For other worker nodes in Citus MX, we let the local execution to kick-in
		 * even for round-robin policy, that's because we expect the clients to evenly
		 * connect to the worker nodes.
		 */
		Assert(ReadOnlyTask(task->taskType));
		placementList = RemoveCoordinatorPlacement(placementList);

		/* reorder the placement list */
		reorderedPlacementList = RoundRobinReorder(task, placementList);
		task->taskPlacementList = reorderedPlacementList;

		primaryPlacement = (ShardPlacement *) linitial(reorderedPlacementList);
		ereport(DEBUG3, (errmsg("assigned task %u to node %s:%u", task->taskId,
								primaryPlacement->nodeName,
								primaryPlacement->nodePort)));
	}
}