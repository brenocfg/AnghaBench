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
typedef  int /*<<< orphan*/  values ;
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  isNulls ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/ * TupleDesc ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int Datum ;

/* Variables and functions */
 int Anum_pg_dist_placement_groupid ; 
 int Anum_pg_dist_placement_placementid ; 
 int Anum_pg_dist_placement_shardid ; 
 int Anum_pg_dist_placement_shardlength ; 
 int Anum_pg_dist_placement_shardstate ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int CharGetDatum (char) ; 
 int /*<<< orphan*/  CitusInvalidateRelcacheByShardId (scalar_t__) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DistPlacementRelationId () ; 
 scalar_t__ INVALID_PLACEMENT_ID ; 
 int Int32GetDatum (int /*<<< orphan*/ ) ; 
 int Int64GetDatum (scalar_t__) ; 
 int Natts_pg_dist_placement ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/ * RelationGetDescr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_form_tuple (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ master_get_new_placementid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

uint64
InsertShardPlacementRow(uint64 shardId, uint64 placementId,
						char shardState, uint64 shardLength,
						int32 groupId)
{
	Relation pgDistPlacement = NULL;
	TupleDesc tupleDescriptor = NULL;
	HeapTuple heapTuple = NULL;
	Datum values[Natts_pg_dist_placement];
	bool isNulls[Natts_pg_dist_placement];

	/* form new shard placement tuple */
	memset(values, 0, sizeof(values));
	memset(isNulls, false, sizeof(isNulls));

	if (placementId == INVALID_PLACEMENT_ID)
	{
		placementId = master_get_new_placementid(NULL);
	}
	values[Anum_pg_dist_placement_placementid - 1] = Int64GetDatum(placementId);
	values[Anum_pg_dist_placement_shardid - 1] = Int64GetDatum(shardId);
	values[Anum_pg_dist_placement_shardstate - 1] = CharGetDatum(shardState);
	values[Anum_pg_dist_placement_shardlength - 1] = Int64GetDatum(shardLength);
	values[Anum_pg_dist_placement_groupid - 1] = Int32GetDatum(groupId);

	/* open shard placement relation and insert new tuple */
	pgDistPlacement = heap_open(DistPlacementRelationId(), RowExclusiveLock);

	tupleDescriptor = RelationGetDescr(pgDistPlacement);
	heapTuple = heap_form_tuple(tupleDescriptor, values, isNulls);

	CatalogTupleInsert(pgDistPlacement, heapTuple);

	CitusInvalidateRelcacheByShardId(shardId);

	CommandCounterIncrement();
	heap_close(pgDistPlacement, NoLock);

	return placementId;
}