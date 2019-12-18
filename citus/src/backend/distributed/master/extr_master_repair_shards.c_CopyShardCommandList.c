#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_8__ {int /*<<< orphan*/  relationId; int /*<<< orphan*/  shardId; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  TYPE_2__ ShardInterval ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 char* ConstructQualifiedShardName (TYPE_2__*) ; 
 int /*<<< orphan*/ * GetTableIndexAndConstraintCommands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * RecreateTableDDLCommandList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WORKER_APPEND_TABLE_TO_SHARD ; 
 int /*<<< orphan*/ * WorkerApplyShardDDLCommandList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* makeStringInfo () ; 
 int /*<<< orphan*/  quote_literal_cstr (char*) ; 

List *
CopyShardCommandList(ShardInterval *shardInterval, char *sourceNodeName,
					 int32 sourceNodePort, bool includeDataCopy)
{
	int64 shardId = shardInterval->shardId;
	char *shardName = ConstructQualifiedShardName(shardInterval);
	List *tableRecreationCommandList = NIL;
	List *indexCommandList = NIL;
	List *copyShardToNodeCommandsList = NIL;
	StringInfo copyShardDataCommand = makeStringInfo();
	Oid relationId = shardInterval->relationId;

	tableRecreationCommandList = RecreateTableDDLCommandList(relationId);
	tableRecreationCommandList =
		WorkerApplyShardDDLCommandList(tableRecreationCommandList, shardId);

	copyShardToNodeCommandsList = list_concat(copyShardToNodeCommandsList,
											  tableRecreationCommandList);

	/*
	 * The caller doesn't want to include the COPY command, perhaps using
	 * logical replication to copy the data.
	 */
	if (includeDataCopy)
	{
		appendStringInfo(copyShardDataCommand, WORKER_APPEND_TABLE_TO_SHARD,
						 quote_literal_cstr(shardName), /* table to append */
						 quote_literal_cstr(shardName), /* remote table name */
						 quote_literal_cstr(sourceNodeName), /* remote host */
						 sourceNodePort); /* remote port */

		copyShardToNodeCommandsList = lappend(copyShardToNodeCommandsList,
											  copyShardDataCommand->data);
	}

	indexCommandList = GetTableIndexAndConstraintCommands(relationId);
	indexCommandList = WorkerApplyShardDDLCommandList(indexCommandList, shardId);

	copyShardToNodeCommandsList = list_concat(copyShardToNodeCommandsList,
											  indexCommandList);

	return copyShardToNodeCommandsList;
}