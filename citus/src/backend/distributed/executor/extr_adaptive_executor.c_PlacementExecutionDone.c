#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_5__* distributedExecution; } ;
typedef  TYPE_1__ WorkerPool ;
struct TYPE_11__ {scalar_t__ executionState; TYPE_3__* shardPlacement; TYPE_4__* shardCommandExecution; TYPE_1__* workerPool; } ;
typedef  TYPE_2__ TaskPlacementExecution ;
typedef  scalar_t__ TaskExecutionState ;
struct TYPE_14__ {int failed; int /*<<< orphan*/  unfinishedTaskCount; } ;
struct TYPE_13__ {scalar_t__ executionState; } ;
struct TYPE_12__ {scalar_t__ shardState; int /*<<< orphan*/  placementId; } ;
typedef  TYPE_3__ ShardPlacement ;
typedef  TYPE_4__ ShardCommandExecution ;
typedef  TYPE_5__ DistributedExecution ;

/* Variables and functions */
 scalar_t__ FILE_FINALIZED ; 
 int /*<<< orphan*/  FILE_INACTIVE ; 
 scalar_t__ PLACEMENT_EXECUTION_FAILED ; 
 scalar_t__ PLACEMENT_EXECUTION_FINISHED ; 
 scalar_t__ PLACEMENT_EXECUTION_NOT_READY ; 
 int /*<<< orphan*/  ScheduleNextPlacementExecution (TYPE_2__*,int) ; 
 scalar_t__ ShouldMarkPlacementsInvalidOnFailure (TYPE_5__*) ; 
 scalar_t__ TASK_EXECUTION_FAILED ; 
 scalar_t__ TASK_EXECUTION_FINISHED ; 
 scalar_t__ TASK_EXECUTION_NOT_FINISHED ; 
 scalar_t__ TaskExecutionStateMachine (TYPE_4__*) ; 
 int /*<<< orphan*/  UpdateShardPlacementState (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
PlacementExecutionDone(TaskPlacementExecution *placementExecution, bool succeeded)
{
	WorkerPool *workerPool = placementExecution->workerPool;
	DistributedExecution *execution = workerPool->distributedExecution;
	ShardCommandExecution *shardCommandExecution =
		placementExecution->shardCommandExecution;
	TaskExecutionState executionState = shardCommandExecution->executionState;
	TaskExecutionState newExecutionState = TASK_EXECUTION_NOT_FINISHED;
	bool failedPlacementExecutionIsOnPendingQueue = false;

	/* mark the placement execution as finished */
	if (succeeded)
	{
		placementExecution->executionState = PLACEMENT_EXECUTION_FINISHED;
	}
	else
	{
		if (ShouldMarkPlacementsInvalidOnFailure(execution))
		{
			ShardPlacement *shardPlacement = placementExecution->shardPlacement;

			/*
			 * We only set shard state if its current state is FILE_FINALIZED, which
			 * prevents overwriting shard state if it is already set at somewhere else.
			 */
			if (shardPlacement->shardState == FILE_FINALIZED)
			{
				UpdateShardPlacementState(shardPlacement->placementId, FILE_INACTIVE);
			}
		}

		if (placementExecution->executionState == PLACEMENT_EXECUTION_NOT_READY)
		{
			/*
			 * If the placement is in NOT_READY state, it means that the placement
			 * execution is assigned to the pending queue of a failed pool or
			 * session. So, we should not schedule the next placement execution based
			 * on this failure.
			 */
			failedPlacementExecutionIsOnPendingQueue = true;
		}

		placementExecution->executionState = PLACEMENT_EXECUTION_FAILED;
	}

	if (executionState != TASK_EXECUTION_NOT_FINISHED)
	{
		/*
		 * Task execution has already been finished, no need to continue the
		 * next placement.
		 */
		return;
	}

	/*
	 * Update unfinishedTaskCount only when state changes from not finished to
	 * finished or failed state.
	 */
	newExecutionState = TaskExecutionStateMachine(shardCommandExecution);
	if (newExecutionState == TASK_EXECUTION_FINISHED)
	{
		execution->unfinishedTaskCount--;
		return;
	}
	else if (newExecutionState == TASK_EXECUTION_FAILED)
	{
		execution->unfinishedTaskCount--;

		/*
		 * Even if a single task execution fails, there is no way to
		 * successfully finish the execution.
		 */
		execution->failed = true;
		return;
	}
	else if (!failedPlacementExecutionIsOnPendingQueue)
	{
		ScheduleNextPlacementExecution(placementExecution, succeeded);
	}
}