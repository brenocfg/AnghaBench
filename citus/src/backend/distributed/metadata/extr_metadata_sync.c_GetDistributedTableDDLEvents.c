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
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  DistTableCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/ * DistributedTableCacheEntry (int /*<<< orphan*/ ) ; 
 char* DistributionCreateCommand (int /*<<< orphan*/ *) ; 
 char* GenerateAlterTableAttachPartitionCommand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetTableDDLEvents (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * GetTableForeignConstraintCommands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LoadShardIntervalList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ PartitionTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SequenceDDLCommandsForTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ShardListInsertCommand (int /*<<< orphan*/ *) ; 
 char* TableOwnerResetCommand (int /*<<< orphan*/ ) ; 
 char* TruncateTriggerCreateCommand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

List *
GetDistributedTableDDLEvents(Oid relationId)
{
	DistTableCacheEntry *cacheEntry = DistributedTableCacheEntry(relationId);

	List *shardIntervalList = NIL;
	List *commandList = NIL;
	List *foreignConstraintCommands = NIL;
	List *shardMetadataInsertCommandList = NIL;
	List *sequenceDDLCommands = NIL;
	List *tableDDLCommands = NIL;
	char *tableOwnerResetCommand = NULL;
	char *metadataCommand = NULL;
	char *truncateTriggerCreateCommand = NULL;
	bool includeSequenceDefaults = true;

	/* commands to create sequences */
	sequenceDDLCommands = SequenceDDLCommandsForTable(relationId);
	commandList = list_concat(commandList, sequenceDDLCommands);

	/* commands to create the table */
	tableDDLCommands = GetTableDDLEvents(relationId, includeSequenceDefaults);
	commandList = list_concat(commandList, tableDDLCommands);

	/* command to reset the table owner */
	tableOwnerResetCommand = TableOwnerResetCommand(relationId);
	commandList = lappend(commandList, tableOwnerResetCommand);

	/* command to insert pg_dist_partition entry */
	metadataCommand = DistributionCreateCommand(cacheEntry);
	commandList = lappend(commandList, metadataCommand);

	/* commands to create the truncate trigger of the table */
	truncateTriggerCreateCommand = TruncateTriggerCreateCommand(relationId);
	commandList = lappend(commandList, truncateTriggerCreateCommand);

	/* commands to insert pg_dist_shard & pg_dist_placement entries */
	shardIntervalList = LoadShardIntervalList(relationId);
	shardMetadataInsertCommandList = ShardListInsertCommand(shardIntervalList);
	commandList = list_concat(commandList, shardMetadataInsertCommandList);

	/* commands to create foreign key constraints */
	foreignConstraintCommands = GetTableForeignConstraintCommands(relationId);
	commandList = list_concat(commandList, foreignConstraintCommands);

	/* commands to create partitioning hierarchy */
	if (PartitionTable(relationId))
	{
		char *alterTableAttachPartitionCommands =
			GenerateAlterTableAttachPartitionCommand(relationId);
		commandList = lappend(commandList, alterTableAttachPartitionCommands);
	}

	return commandList;
}