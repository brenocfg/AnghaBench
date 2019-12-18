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
struct TYPE_6__ {int errorOnAnyFailure; int targetPoolSize; int /*<<< orphan*/  isTransaction; int /*<<< orphan*/ * tasksToExecute; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ DistributedExecution ;

/* Variables and functions */
 int /*<<< orphan*/  AcquireExecutorShardLocksForExecution (TYPE_1__*) ; 
 int /*<<< orphan*/  BeginOrContinueCoordinatedTransaction () ; 
 scalar_t__ COMMIT_PROTOCOL_2PC ; 
 scalar_t__ COMMIT_PROTOCOL_BARE ; 
 int /*<<< orphan*/  CoordinatedTransactionUse2PC () ; 
 scalar_t__ DistributedExecutionModifiesDatabase (TYPE_1__*) ; 
 scalar_t__ DistributedExecutionRequiresRollback (TYPE_1__*) ; 
 int /*<<< orphan*/  InCoordinatedTransaction () ; 
 scalar_t__ LocalExecutionHappened ; 
 scalar_t__ MultiShardCommitProtocol ; 
 int /*<<< orphan*/  RecordParallelRelationAccessForTaskList (int /*<<< orphan*/ *) ; 
 scalar_t__ TaskListRequires2PC (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 

void
StartDistributedExecution(DistributedExecution *execution)
{
	List *taskList = execution->tasksToExecute;

	if (MultiShardCommitProtocol != COMMIT_PROTOCOL_BARE)
	{
		/*
		 * In case localExecutionHappened, we simply force the executor to use 2PC.
		 * The primary motivation is that at this point we're definitely expanding
		 * the nodes participated in the transaction. And, by re-generating the
		 * remote task lists during local query execution, we might prevent the adaptive
		 * executor to kick-in 2PC (or even start coordinated transaction, that's why
		 * we prefer adding this check here instead of
		 * Activate2PCIfModifyingTransactionExpandsToNewNode()).
		 */
		if (DistributedExecutionRequiresRollback(execution) || LocalExecutionHappened)
		{
			BeginOrContinueCoordinatedTransaction();

			if (TaskListRequires2PC(taskList) || LocalExecutionHappened)
			{
				/*
				 * Although using two phase commit protocol is an independent decision than
				 * failing on any error, we prefer to couple them. Our motivation is that
				 * the failures are rare, and we prefer to avoid marking placements invalid
				 * in case of failures.
				 */
				CoordinatedTransactionUse2PC();

				execution->errorOnAnyFailure = true;
			}
			else if (MultiShardCommitProtocol != COMMIT_PROTOCOL_2PC &&
					 list_length(taskList) > 1 &&
					 DistributedExecutionModifiesDatabase(execution))
			{
				/*
				 * Even if we're not using 2PC, we prefer to error out
				 * on any failures during multi shard modifications/DDLs.
				 */
				execution->errorOnAnyFailure = true;
			}
		}
	}
	else
	{
		/*
		 * We prefer to error on any failures for CREATE INDEX
		 * CONCURRENTLY or VACUUM//VACUUM ANALYZE (e.g., COMMIT_PROTOCOL_BARE).
		 */
		execution->errorOnAnyFailure = true;
	}

	/*
	 * Prevent unsafe concurrent modifications of replicated shards by taking
	 * locks.
	 *
	 * When modifying a reference tables in MX mode, we take the lock via RPC
	 * to the first worker in a transaction block, which activates a coordinated
	 * transaction. We need to do this before determining whether the execution
	 * should use transaction blocks (see below).
	 */
	AcquireExecutorShardLocksForExecution(execution);

	/*
	 * If the current or previous execution in the current transaction requires
	 * rollback then we should use transaction blocks.
	 */
	execution->isTransaction = InCoordinatedTransaction();

	/*
	 * We should not record parallel access if the target pool size is less than 2.
	 * The reason is that we define parallel access as at least two connections
	 * accessing established to worker node.
	 *
	 * It is not ideal to have this check here, it'd have been better if we simply passed
	 * DistributedExecution directly to the RecordParallelAccess*() function. However,
	 * since we have two other executors that rely on the function, we had to only pass
	 * the tasklist to have a common API.
	 */
	if (execution->targetPoolSize > 1)
	{
		RecordParallelRelationAccessForTaskList(taskList);
	}
}