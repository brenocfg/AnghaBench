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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  isNulls ;
typedef  int /*<<< orphan*/ * TupleDesc ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int Datum ;

/* Variables and functions */
 int Anum_pg_dist_shard_logicalrelid ; 
 int Anum_pg_dist_shard_shardalias_DROPPED ; 
 int Anum_pg_dist_shard_shardid ; 
 int Anum_pg_dist_shard_shardmaxvalue ; 
 int Anum_pg_dist_shard_shardminvalue ; 
 int Anum_pg_dist_shard_shardstorage ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int CharGetDatum (char) ; 
 int /*<<< orphan*/  CitusInvalidateRelcacheByRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DistShardRelationId () ; 
 int Int64GetDatum (int /*<<< orphan*/ ) ; 
 int Natts_pg_dist_shard ; 
 int /*<<< orphan*/  NoLock ; 
 int ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RelationGetDescr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_form_tuple (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

void
InsertShardRow(Oid relationId, uint64 shardId, char storageType,
			   text *shardMinValue, text *shardMaxValue)
{
	Relation pgDistShard = NULL;
	TupleDesc tupleDescriptor = NULL;
	HeapTuple heapTuple = NULL;
	Datum values[Natts_pg_dist_shard];
	bool isNulls[Natts_pg_dist_shard];

	/* form new shard tuple */
	memset(values, 0, sizeof(values));
	memset(isNulls, false, sizeof(isNulls));

	values[Anum_pg_dist_shard_logicalrelid - 1] = ObjectIdGetDatum(relationId);
	values[Anum_pg_dist_shard_shardid - 1] = Int64GetDatum(shardId);
	values[Anum_pg_dist_shard_shardstorage - 1] = CharGetDatum(storageType);

	/* dropped shardalias column must also be set; it is still part of the tuple */
	isNulls[Anum_pg_dist_shard_shardalias_DROPPED - 1] = true;

	/* check if shard min/max values are null */
	if (shardMinValue != NULL && shardMaxValue != NULL)
	{
		values[Anum_pg_dist_shard_shardminvalue - 1] = PointerGetDatum(shardMinValue);
		values[Anum_pg_dist_shard_shardmaxvalue - 1] = PointerGetDatum(shardMaxValue);
	}
	else
	{
		isNulls[Anum_pg_dist_shard_shardminvalue - 1] = true;
		isNulls[Anum_pg_dist_shard_shardmaxvalue - 1] = true;
	}

	/* open shard relation and insert new tuple */
	pgDistShard = heap_open(DistShardRelationId(), RowExclusiveLock);

	tupleDescriptor = RelationGetDescr(pgDistShard);
	heapTuple = heap_form_tuple(tupleDescriptor, values, isNulls);

	CatalogTupleInsert(pgDistShard, heapTuple);

	/* invalidate previous cache entry and close relation */
	CitusInvalidateRelcacheByRelid(relationId);

	CommandCounterIncrement();
	heap_close(pgDistShard, NoLock);
}