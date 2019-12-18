#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_14__ {int /*<<< orphan*/  relationId; } ;
struct TYPE_13__ {int /*<<< orphan*/  placementId; } ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  TYPE_2__ ShardPlacement ;
typedef  TYPE_3__ ShardInterval ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 char* ConstructQualifiedShardName (TYPE_3__*) ; 
 int /*<<< orphan*/ * CopyPartitionShardsCommandList (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CopyShardCommandList (TYPE_3__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CopyShardForeignConstraintCommandList (TYPE_3__*) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnsureNoModificationsHaveBeenDone () ; 
 int /*<<< orphan*/  EnsurePartitionTableNotReplicated (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnsureShardCanBeRepaired (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnsureTableOwner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  FILE_FINALIZED ; 
 TYPE_3__* LoadShardInterval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockReferencedReferenceShardDistributionMetadata (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockShardDistributionMetadata (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int PartitionedTableNoLock (int /*<<< orphan*/ ) ; 
 char RELKIND_FOREIGN_TABLE ; 
 TYPE_2__* SearchShardPlacementInList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SendCommandListToWorkerInSingleTransaction (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ShardPlacementList (int /*<<< orphan*/ ) ; 
 char* TableOwner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateShardPlacementState (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WORKER_APPEND_TABLE_TO_SHARD ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 char get_rel_relkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* makeStringInfo () ; 
 int /*<<< orphan*/  quote_literal_cstr (char*) ; 

__attribute__((used)) static void
RepairShardPlacement(int64 shardId, char *sourceNodeName, int32 sourceNodePort,
					 char *targetNodeName, int32 targetNodePort)
{
	ShardInterval *shardInterval = LoadShardInterval(shardId);
	Oid distributedTableId = shardInterval->relationId;

	char relationKind = get_rel_relkind(distributedTableId);
	char *tableOwner = TableOwner(shardInterval->relationId);
	bool missingOk = false;
	bool includeData = false;
	bool partitionedTable = false;

	List *ddlCommandList = NIL;
	List *foreignConstraintCommandList = NIL;
	List *placementList = NIL;
	ShardPlacement *placement = NULL;

	/* prevent table from being dropped */
	LockRelationOid(distributedTableId, AccessShareLock);

	EnsureTableOwner(distributedTableId);

	if (relationKind == RELKIND_FOREIGN_TABLE)
	{
		char *relationName = get_rel_name(distributedTableId);
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("cannot repair shard"),
						errdetail("Table %s is a foreign table. Repairing "
								  "shards backed by foreign tables is "
								  "not supported.", relationName)));
	}

	/*
	 * Let's not allow repairing partitions to prevent any edge cases.
	 * We're already not allowing any kind of modifications on the partitions
	 * so their placements are not likely to to be marked as INVALID. The only
	 * possible case to mark placement of a partition as invalid is
	 * "ALTER TABLE parent_table DETACH PARTITION partition_table". But,
	 * given that the table would become a regular distributed table if the
	 * command succeeds, we're OK since the regular distributed tables can
	 * be repaired later on.
	 */
	EnsurePartitionTableNotReplicated(distributedTableId);

	/*
	 * We take a lock on the referenced table if there is a foreign constraint
	 * during the copy procedure. If we do not block DMLs on the referenced
	 * table, we cannot avoid the inconsistency between the two copies of the
	 * data. Currently, we do not support replication factor > 1 on the tables
	 * with foreign constraints, so this command will fail for this case anyway.
	 * However, it is taken as a precaution in case we support it one day.
	 */
	LockReferencedReferenceShardDistributionMetadata(shardId, ExclusiveLock);

	/*
	 * We plan to move the placement to the healthy state, so we need to grab a shard
	 * metadata lock (in exclusive mode).
	 */
	LockShardDistributionMetadata(shardId, ExclusiveLock);

	/*
	 * For shard repair, there should be healthy placement in source node and unhealthy
	 * placement in the target node.
	 */
	EnsureShardCanBeRepaired(shardId, sourceNodeName, sourceNodePort, targetNodeName,
							 targetNodePort);

	/*
	 * If the shard belongs to a partitioned table, we need to load the data after
	 * creating the partitions and the partitioning hierarcy.
	 */
	partitionedTable = PartitionedTableNoLock(distributedTableId);
	includeData = !partitionedTable;

	/* we generate necessary commands to recreate the shard in target node */
	ddlCommandList =
		CopyShardCommandList(shardInterval, sourceNodeName, sourceNodePort, includeData);
	foreignConstraintCommandList = CopyShardForeignConstraintCommandList(shardInterval);
	ddlCommandList = list_concat(ddlCommandList, foreignConstraintCommandList);

	/*
	 * CopyShardCommandList() drops the table which cascades to partitions if the
	 * table is a partitioned table. This means that we need to create both parent
	 * table and its partitions.
	 *
	 * We also skipped copying the data, so include it here.
	 */
	if (partitionedTable)
	{
		List *partitionCommandList = NIL;

		char *shardName = ConstructQualifiedShardName(shardInterval);
		StringInfo copyShardDataCommand = makeStringInfo();

		partitionCommandList =
			CopyPartitionShardsCommandList(shardInterval, sourceNodeName, sourceNodePort);
		ddlCommandList = list_concat(ddlCommandList, partitionCommandList);

		/* finally copy the data as well */
		appendStringInfo(copyShardDataCommand, WORKER_APPEND_TABLE_TO_SHARD,
						 quote_literal_cstr(shardName), /* table to append */
						 quote_literal_cstr(shardName), /* remote table name */
						 quote_literal_cstr(sourceNodeName), /* remote host */
						 sourceNodePort); /* remote port */
		ddlCommandList = lappend(ddlCommandList, copyShardDataCommand->data);
	}

	EnsureNoModificationsHaveBeenDone();
	SendCommandListToWorkerInSingleTransaction(targetNodeName, targetNodePort, tableOwner,
											   ddlCommandList);

	/* after successful repair, we update shard state as healthy*/
	placementList = ShardPlacementList(shardId);
	placement = SearchShardPlacementInList(placementList, targetNodeName, targetNodePort,
										   missingOk);
	UpdateShardPlacementState(placement->placementId, FILE_FINALIZED);
}