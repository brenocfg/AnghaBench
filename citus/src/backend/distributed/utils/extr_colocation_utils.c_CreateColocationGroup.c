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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  isNulls ;
typedef  int /*<<< orphan*/ * TupleDesc ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int Datum ;

/* Variables and functions */
 int Anum_pg_dist_colocation_colocationid ; 
 int Anum_pg_dist_colocation_distributioncolumntype ; 
 int Anum_pg_dist_colocation_replicationfactor ; 
 int Anum_pg_dist_colocation_shardcount ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DistColocationRelationId () ; 
 int GetNextColocationId () ; 
 int Natts_pg_dist_colocation ; 
 int ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RelationGetDescr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int UInt32GetDatum (int) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_form_tuple (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

uint32
CreateColocationGroup(int shardCount, int replicationFactor, Oid distributionColumnType)
{
	uint32 colocationId = GetNextColocationId();
	Relation pgDistColocation = NULL;
	TupleDesc tupleDescriptor = NULL;
	HeapTuple heapTuple = NULL;
	Datum values[Natts_pg_dist_colocation];
	bool isNulls[Natts_pg_dist_colocation];

	/* form new colocation tuple */
	memset(values, 0, sizeof(values));
	memset(isNulls, false, sizeof(isNulls));

	values[Anum_pg_dist_colocation_colocationid - 1] = UInt32GetDatum(colocationId);
	values[Anum_pg_dist_colocation_shardcount - 1] = UInt32GetDatum(shardCount);
	values[Anum_pg_dist_colocation_replicationfactor - 1] =
		UInt32GetDatum(replicationFactor);
	values[Anum_pg_dist_colocation_distributioncolumntype - 1] =
		ObjectIdGetDatum(distributionColumnType);

	/* open colocation relation and insert the new tuple */
	pgDistColocation = heap_open(DistColocationRelationId(), RowExclusiveLock);

	tupleDescriptor = RelationGetDescr(pgDistColocation);
	heapTuple = heap_form_tuple(tupleDescriptor, values, isNulls);

	CatalogTupleInsert(pgDistColocation, heapTuple);

	/* increment the counter so that next command can see the row */
	CommandCounterIncrement();
	heap_close(pgDistColocation, RowExclusiveLock);

	return colocationId;
}