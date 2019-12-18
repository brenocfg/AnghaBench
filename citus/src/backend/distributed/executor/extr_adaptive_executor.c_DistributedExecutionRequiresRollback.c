#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ relationRowLockList; scalar_t__ anchorShardId; int /*<<< orphan*/ * taskPlacementList; int /*<<< orphan*/  taskType; } ;
typedef  TYPE_1__ Task ;
struct TYPE_5__ {int /*<<< orphan*/ * tasksToExecute; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ DistributedExecution ;

/* Variables and functions */
 scalar_t__ COMMIT_PROTOCOL_2PC ; 
 scalar_t__ COMMIT_PROTOCOL_BARE ; 
 scalar_t__ INVALID_SHARD_ID ; 
 scalar_t__ IsMultiStatementTransaction () ; 
 int IsTransactionBlock () ; 
 scalar_t__ MultiShardCommitProtocol ; 
 scalar_t__ NIL ; 
 scalar_t__ ReadOnlyTask (int /*<<< orphan*/ ) ; 
 scalar_t__ ReferenceTableShardId (scalar_t__) ; 
 scalar_t__ SelectOpensTransactionBlock ; 
 scalar_t__ SingleShardCommitProtocol ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
DistributedExecutionRequiresRollback(DistributedExecution *execution)
{
	List *taskList = execution->tasksToExecute;
	int taskCount = list_length(taskList);
	Task *task = NULL;
	bool selectForUpdate = false;

	if (MultiShardCommitProtocol == COMMIT_PROTOCOL_BARE)
	{
		return false;
	}

	if (taskCount == 0)
	{
		return false;
	}

	task = (Task *) linitial(taskList);

	selectForUpdate = task->relationRowLockList != NIL;
	if (selectForUpdate)
	{
		/*
		 * Do not check SelectOpensTransactionBlock, always open transaction block
		 * if SELECT FOR UPDATE is executed inside a distributed transaction.
		 */
		return IsTransactionBlock();
	}

	if (ReadOnlyTask(task->taskType))
	{
		return SelectOpensTransactionBlock && IsTransactionBlock();
	}

	if (IsMultiStatementTransaction())
	{
		return true;
	}

	if (list_length(taskList) > 1)
	{
		return true;
	}

	if (list_length(task->taskPlacementList) > 1)
	{
		if (SingleShardCommitProtocol == COMMIT_PROTOCOL_2PC)
		{
			/*
			 * Adaptive executor opts to error out on queries if a placement is unhealthy,
			 * not marking the placement itself unhealthy in the process.
			 * Use 2PC to rollback placements before the unhealthy replica failed.
			 */
			return true;
		}

		/*
		 * Some tasks don't set replicationModel thus we only
		 * rely on the anchorShardId, not replicationModel.
		 *
		 * TODO: Do we ever need replicationModel in the Task structure?
		 * Can't we always rely on anchorShardId?
		 */
		if (task->anchorShardId != INVALID_SHARD_ID && ReferenceTableShardId(
				task->anchorShardId))
		{
			return true;
		}

		/*
		 * Single DML/DDL tasks with replicated tables (non-reference)
		 * should not require BEGIN/COMMIT/ROLLBACK.
		 */
		return false;
	}

	return false;
}