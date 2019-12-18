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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  CompareWorkerNodes ; 
 int /*<<< orphan*/  CreateShardsOnWorkers (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnsureTableOwner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  GetNextShardId () ; 
 int /*<<< orphan*/  INVALID_SHARD_ID ; 
 int /*<<< orphan*/ * InsertShardPlacementRows (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  InsertShardRow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LoadShardList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockShardDistributionMetadata (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * ReferenceTablePlacementNodeList (int /*<<< orphan*/ ) ; 
 int ReferenceTableReplicationFactor () ; 
 char ShardStorageType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareLock ; 
 int /*<<< orphan*/ * SortList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 

void
CreateReferenceTableShard(Oid distributedTableId)
{
	char shardStorageType = 0;
	List *nodeList = NIL;
	List *existingShardList = NIL;
	uint64 shardId = INVALID_SHARD_ID;
	int workerStartIndex = 0;
	int replicationFactor = 0;
	text *shardMinValue = NULL;
	text *shardMaxValue = NULL;
	bool useExclusiveConnection = false;
	bool colocatedShard = false;
	List *insertedShardPlacements = NIL;

	/*
	 * In contrast to append/range partitioned tables it makes more sense to
	 * require ownership privileges - shards for reference tables are
	 * only created once, not continually during ingest as for the other
	 * partitioning types such as append and range.
	 */
	EnsureTableOwner(distributedTableId);

	/* we plan to add shards: get an exclusive lock on relation oid */
	LockRelationOid(distributedTableId, ExclusiveLock);

	/* set shard storage type according to relation type */
	shardStorageType = ShardStorageType(distributedTableId);

	/* validate that shards haven't already been created for this table */
	existingShardList = LoadShardList(distributedTableId);
	if (existingShardList != NIL)
	{
		char *tableName = get_rel_name(distributedTableId);
		ereport(ERROR, (errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
						errmsg("table \"%s\" has already had shards created for it",
							   tableName)));
	}

	/*
	 * load and sort the worker node list for deterministic placements
	 * create_reference_table has already acquired pg_dist_node lock
	 */
	nodeList = ReferenceTablePlacementNodeList(ShareLock);
	nodeList = SortList(nodeList, CompareWorkerNodes);

	replicationFactor = ReferenceTableReplicationFactor();

	/* get the next shard id */
	shardId = GetNextShardId();

	/*
	 * Grabbing the shard metadata lock isn't technically necessary since
	 * we already hold an exclusive lock on the partition table, but we'll
	 * acquire it for the sake of completeness. As we're adding new active
	 * placements, the mode must be exclusive.
	 */
	LockShardDistributionMetadata(shardId, ExclusiveLock);

	InsertShardRow(distributedTableId, shardId, shardStorageType, shardMinValue,
				   shardMaxValue);

	insertedShardPlacements = InsertShardPlacementRows(distributedTableId, shardId,
													   nodeList, workerStartIndex,
													   replicationFactor);

	CreateShardsOnWorkers(distributedTableId, insertedShardPlacements,
						  useExclusiveConnection, colocatedShard);
}