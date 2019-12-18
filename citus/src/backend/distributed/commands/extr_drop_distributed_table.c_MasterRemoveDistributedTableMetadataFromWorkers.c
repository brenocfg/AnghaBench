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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 char* DistributionDeleteCommand (char*,char*) ; 
 int /*<<< orphan*/  EnableDDLPropagation ; 
 int /*<<< orphan*/  EnsureCoordinator () ; 
 int /*<<< orphan*/  IsDistributedTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendCommandToWorkers (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ShouldSyncTableMetadata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WORKERS_WITH_METADATA ; 

__attribute__((used)) static void
MasterRemoveDistributedTableMetadataFromWorkers(Oid relationId, char *schemaName,
												char *tableName)
{
	char *deleteDistributionCommand = NULL;

	/*
	 * The SQL_DROP trigger calls this function even for tables that are
	 * not distributed. In that case, silently ignore. This is not very
	 * user-friendly, but this function is really only meant to be called
	 * from the trigger.
	 */
	if (!IsDistributedTable(relationId) || !EnableDDLPropagation)
	{
		return;
	}

	EnsureCoordinator();

	if (!ShouldSyncTableMetadata(relationId))
	{
		return;
	}

	/* drop the distributed table metadata on the workers */
	deleteDistributionCommand = DistributionDeleteCommand(schemaName, tableName);
	SendCommandToWorkers(WORKERS_WITH_METADATA, deleteDistributionCommand);
}