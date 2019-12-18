#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ targetRelationId; scalar_t__ commandString; int /*<<< orphan*/  taskList; int /*<<< orphan*/  concurrentIndexCmd; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ DDLJob ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ COMMIT_PROTOCOL_BARE ; 
 char* DISABLE_DDL_PROPAGATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnsureCoordinator () ; 
 int /*<<< orphan*/  EnsurePartitionTableNotReplicated (scalar_t__) ; 
 int /*<<< orphan*/  ExecuteUtilityTaskListWithoutResults (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ MultiShardCommitProtocol ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 scalar_t__ SavedMultiShardCommitProtocol ; 
 int /*<<< orphan*/  SendBareCommandListToWorkers (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendCommandToWorkers (int /*<<< orphan*/ ,char*) ; 
 char* SetSearchPathToCurrentSearchPathCommand () ; 
 int ShouldSyncTableMetadata (scalar_t__) ; 
 int /*<<< orphan*/  WORKERS_WITH_METADATA ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * list_make1 (char*) ; 

__attribute__((used)) static void
ExecuteDistributedDDLJob(DDLJob *ddlJob)
{
	bool shouldSyncMetadata = false;

	EnsureCoordinator();

	if (ddlJob->targetRelationId != InvalidOid)
	{
		/*
		 * Only for ddlJobs that are targetting a relation (table) we want to sync its
		 * metadata and verify some properties around the table.
		 */
		shouldSyncMetadata = ShouldSyncTableMetadata(ddlJob->targetRelationId);
		EnsurePartitionTableNotReplicated(ddlJob->targetRelationId);
	}


	if (!ddlJob->concurrentIndexCmd)
	{
		if (shouldSyncMetadata)
		{
			char *setSearchPathCommand = SetSearchPathToCurrentSearchPathCommand();

			SendCommandToWorkers(WORKERS_WITH_METADATA, DISABLE_DDL_PROPAGATION);

			/*
			 * Given that we're relaying the query to the worker nodes directly,
			 * we should set the search path exactly the same when necessary.
			 */
			if (setSearchPathCommand != NULL)
			{
				SendCommandToWorkers(WORKERS_WITH_METADATA, setSearchPathCommand);
			}

			SendCommandToWorkers(WORKERS_WITH_METADATA, (char *) ddlJob->commandString);
		}

		/* use adaptive executor when enabled */
		ExecuteUtilityTaskListWithoutResults(ddlJob->taskList);
	}
	else
	{
		/* save old commit protocol to restore at xact end */
		Assert(SavedMultiShardCommitProtocol == COMMIT_PROTOCOL_BARE);
		SavedMultiShardCommitProtocol = MultiShardCommitProtocol;
		MultiShardCommitProtocol = COMMIT_PROTOCOL_BARE;

		PG_TRY();
		{
			/* use adaptive executor when enabled */
			ExecuteUtilityTaskListWithoutResults(ddlJob->taskList);

			if (shouldSyncMetadata)
			{
				List *commandList = list_make1(DISABLE_DDL_PROPAGATION);
				char *setSearchPathCommand = SetSearchPathToCurrentSearchPathCommand();

				/*
				 * Given that we're relaying the query to the worker nodes directly,
				 * we should set the search path exactly the same when necessary.
				 */
				if (setSearchPathCommand != NULL)
				{
					commandList = lappend(commandList, setSearchPathCommand);
				}

				commandList = lappend(commandList, (char *) ddlJob->commandString);

				SendBareCommandListToWorkers(WORKERS_WITH_METADATA, commandList);
			}
		}
		PG_CATCH();
		{
			ereport(ERROR,
					(errmsg("CONCURRENTLY-enabled index command failed"),
					 errdetail("CONCURRENTLY-enabled index commands can fail partially, "
							   "leaving behind an INVALID index."),
					 errhint("Use DROP INDEX CONCURRENTLY IF EXISTS to remove the "
							 "invalid index, then retry the original command.")));
		}
		PG_END_TRY();
	}
}