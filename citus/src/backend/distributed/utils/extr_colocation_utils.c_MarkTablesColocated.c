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
typedef  scalar_t__ uint32 ;
struct TYPE_3__ {int /*<<< orphan*/  vartype; } ;
typedef  TYPE_1__ Var ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  CheckDistributionColumnType (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckReplicationModel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateColocationGroup (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteColocationGroupIfNoTablesBelong (scalar_t__) ; 
 int /*<<< orphan*/  DistColocationRelationId () ; 
 TYPE_1__* DistPartitionKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ErrorIfShardPlacementsNotColocated (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 scalar_t__ INVALID_COLOCATION_ID ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ ShardIntervalCount (int /*<<< orphan*/ ) ; 
 scalar_t__ TableColocationId (int /*<<< orphan*/ ) ; 
 scalar_t__ TableShardReplicationFactor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateRelationColocationGroup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
MarkTablesColocated(Oid sourceRelationId, Oid targetRelationId)
{
	uint32 sourceColocationId = INVALID_COLOCATION_ID;
	uint32 targetColocationId = INVALID_COLOCATION_ID;
	Relation pgDistColocation = NULL;

	CheckReplicationModel(sourceRelationId, targetRelationId);
	CheckDistributionColumnType(sourceRelationId, targetRelationId);

	/*
	 * Get an exclusive lock on the colocation system catalog. Therefore, we
	 * can be sure that there will no modifications on the colocation table
	 * until this transaction is committed.
	 */
	pgDistColocation = heap_open(DistColocationRelationId(), ExclusiveLock);

	/* check if shard placements are colocated */
	ErrorIfShardPlacementsNotColocated(sourceRelationId, targetRelationId);

	/*
	 * Get colocation group of the source table, if the source table does not
	 * have a colocation group, create a new one, and set it for the source table.
	 */
	sourceColocationId = TableColocationId(sourceRelationId);
	if (sourceColocationId == INVALID_COLOCATION_ID)
	{
		uint32 shardCount = ShardIntervalCount(sourceRelationId);
		uint32 shardReplicationFactor = TableShardReplicationFactor(sourceRelationId);

		Var *sourceDistributionColumn = DistPartitionKey(sourceRelationId);
		Oid sourceDistributionColumnType = InvalidOid;

		/* reference tables has NULL distribution column */
		if (sourceDistributionColumn != NULL)
		{
			sourceDistributionColumnType = sourceDistributionColumn->vartype;
		}

		sourceColocationId = CreateColocationGroup(shardCount, shardReplicationFactor,
												   sourceDistributionColumnType);
		UpdateRelationColocationGroup(sourceRelationId, sourceColocationId);
	}

	targetColocationId = TableColocationId(targetRelationId);

	/* finally set colocation group for the target relation */
	UpdateRelationColocationGroup(targetRelationId, sourceColocationId);

	/* if there is not any remaining table in the colocation group, delete it */
	DeleteColocationGroupIfNoTablesBelong(targetColocationId);

	heap_close(pgDistColocation, NoLock);
}