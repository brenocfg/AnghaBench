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
typedef  int uint64 ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  text ;
typedef  int int64 ;
typedef  int int32 ;
struct TYPE_3__ {scalar_t__ replicationModel; int /*<<< orphan*/  relationId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ DistTableCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  CheckHashPartitionedTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CompareWorkerNodes ; 
 int /*<<< orphan*/  CreateShardsOnWorkers (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  DistNodeRelationId () ; 
 TYPE_1__* DistributedTableCacheEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DistributedTablePlacementNodeList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnsureTableOwner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int GetNextShardId () ; 
 int HASH_TOKEN_COUNT ; 
 int INT32_MAX ; 
 int INT32_MIN ; 
 int /*<<< orphan*/ * InsertShardPlacementRows (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  InsertShardRow (int /*<<< orphan*/ ,int,char,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IntegerToText (int) ; 
 int /*<<< orphan*/ * LoadShardList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockShardDistributionMetadata (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ REPLICATION_MODEL_STREAMING ; 
 int /*<<< orphan*/  RowShareLock ; 
 char ShardStorageType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SortList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 

void
CreateShardsWithRoundRobinPolicy(Oid distributedTableId, int32 shardCount,
								 int32 replicationFactor, bool useExclusiveConnections)
{
	char shardStorageType = 0;
	List *workerNodeList = NIL;
	int32 workerNodeCount = 0;
	uint32 placementAttemptCount = 0;
	uint64 hashTokenIncrement = 0;
	List *existingShardList = NIL;
	int64 shardIndex = 0;
	DistTableCacheEntry *cacheEntry = DistributedTableCacheEntry(distributedTableId);
	bool colocatedShard = false;
	List *insertedShardPlacements = NIL;

	/* make sure table is hash partitioned */
	CheckHashPartitionedTable(distributedTableId);

	/*
	 * In contrast to append/range partitioned tables it makes more sense to
	 * require ownership privileges - shards for hash-partitioned tables are
	 * only created once, not continually during ingest as for the other
	 * partitioning types.
	 */
	EnsureTableOwner(distributedTableId);

	/* we plan to add shards: get an exclusive lock on relation oid */
	LockRelationOid(distributedTableId, ExclusiveLock);

	/* validate that shards haven't already been created for this table */
	existingShardList = LoadShardList(distributedTableId);
	if (existingShardList != NIL)
	{
		char *tableName = get_rel_name(distributedTableId);
		ereport(ERROR, (errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
						errmsg("table \"%s\" has already had shards created for it",
							   tableName)));
	}

	/* make sure that at least one shard is specified */
	if (shardCount <= 0)
	{
		ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						errmsg("shard_count must be positive")));
	}

	/* make sure that at least one replica is specified */
	if (replicationFactor <= 0)
	{
		ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						errmsg("replication_factor must be positive")));
	}

	/* make sure that RF=1 if the table is streaming replicated */
	if (cacheEntry->replicationModel == REPLICATION_MODEL_STREAMING &&
		replicationFactor > 1)
	{
		char *relationName = get_rel_name(cacheEntry->relationId);
		ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						errmsg("using replication factor %d with the streaming "
							   "replication model is not supported",
							   replicationFactor),
						errdetail("The table %s is marked as streaming replicated and "
								  "the shard replication factor of streaming replicated "
								  "tables must be 1.", relationName),
						errhint("Use replication factor 1.")));
	}

	/* calculate the split of the hash space */
	hashTokenIncrement = HASH_TOKEN_COUNT / shardCount;

	/* don't allow concurrent node list changes that require an exclusive lock */
	LockRelationOid(DistNodeRelationId(), RowShareLock);

	/* load and sort the worker node list for deterministic placement */
	workerNodeList = DistributedTablePlacementNodeList(NoLock);
	workerNodeList = SortList(workerNodeList, CompareWorkerNodes);

	workerNodeCount = list_length(workerNodeList);
	if (replicationFactor > workerNodeCount)
	{
		ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						errmsg("replication_factor (%d) exceeds number of worker nodes "
							   "(%d)", replicationFactor, workerNodeCount),
						errhint("Add more worker nodes or try again with a lower "
								"replication factor.")));
	}

	/* if we have enough nodes, add an extra placement attempt for backup */
	placementAttemptCount = (uint32) replicationFactor;
	if (workerNodeCount > replicationFactor)
	{
		placementAttemptCount++;
	}

	/* set shard storage type according to relation type */
	shardStorageType = ShardStorageType(distributedTableId);

	for (shardIndex = 0; shardIndex < shardCount; shardIndex++)
	{
		uint32 roundRobinNodeIndex = shardIndex % workerNodeCount;

		/* initialize the hash token space for this shard */
		text *minHashTokenText = NULL;
		text *maxHashTokenText = NULL;
		int32 shardMinHashToken = INT32_MIN + (shardIndex * hashTokenIncrement);
		int32 shardMaxHashToken = shardMinHashToken + (hashTokenIncrement - 1);
		uint64 shardId = GetNextShardId();
		List *currentInsertedShardPlacements = NIL;

		/* if we are at the last shard, make sure the max token value is INT_MAX */
		if (shardIndex == (shardCount - 1))
		{
			shardMaxHashToken = INT32_MAX;
		}

		/* insert the shard metadata row along with its min/max values */
		minHashTokenText = IntegerToText(shardMinHashToken);
		maxHashTokenText = IntegerToText(shardMaxHashToken);

		/*
		 * Grabbing the shard metadata lock isn't technically necessary since
		 * we already hold an exclusive lock on the partition table, but we'll
		 * acquire it for the sake of completeness. As we're adding new active
		 * placements, the mode must be exclusive.
		 */
		LockShardDistributionMetadata(shardId, ExclusiveLock);

		InsertShardRow(distributedTableId, shardId, shardStorageType,
					   minHashTokenText, maxHashTokenText);

		currentInsertedShardPlacements = InsertShardPlacementRows(distributedTableId,
																  shardId,
																  workerNodeList,
																  roundRobinNodeIndex,
																  replicationFactor);
		insertedShardPlacements = list_concat(insertedShardPlacements,
											  currentInsertedShardPlacements);
	}

	CreateShardsOnWorkers(distributedTableId, insertedShardPlacements,
						  useExclusiveConnections, colocatedShard);
}