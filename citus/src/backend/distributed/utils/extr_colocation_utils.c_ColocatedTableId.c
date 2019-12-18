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
typedef  int /*<<< orphan*/ * TupleDesc ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_dist_partition_colocationid ; 
 int /*<<< orphan*/  Anum_pg_dist_partition_logicalrelid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  DistPartitionColocationidIndexId () ; 
 int /*<<< orphan*/  DistPartitionRelationId () ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_COLOCATION_ID ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  LockRelationOid (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  RelationClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RelationGetDescr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RelationIdGetRelation (scalar_t__) ; 
 scalar_t__ RelationIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ heap_getattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ *) ; 

Oid
ColocatedTableId(Oid colocationId)
{
	Oid colocatedTableId = InvalidOid;
	Relation pgDistPartition = NULL;
	TupleDesc tupleDescriptor = NULL;
	SysScanDesc scanDescriptor = NULL;
	HeapTuple heapTuple = NULL;
	bool indexOK = true;
	bool isNull = false;
	ScanKeyData scanKey[1];
	int scanKeyCount = 1;

	/*
	 * We may have a distributed table whose colocation id is INVALID_COLOCATION_ID.
	 * In this case, we do not want to send that table's id as colocated table id.
	 */
	if (colocationId == INVALID_COLOCATION_ID)
	{
		return colocatedTableId;
	}

	ScanKeyInit(&scanKey[0], Anum_pg_dist_partition_colocationid,
				BTEqualStrategyNumber, F_INT4EQ, ObjectIdGetDatum(colocationId));

	pgDistPartition = heap_open(DistPartitionRelationId(), AccessShareLock);
	tupleDescriptor = RelationGetDescr(pgDistPartition);
	scanDescriptor = systable_beginscan(pgDistPartition,
										DistPartitionColocationidIndexId(),
										indexOK, NULL, scanKeyCount, scanKey);

	heapTuple = systable_getnext(scanDescriptor);
	while (HeapTupleIsValid(heapTuple))
	{
		Relation colocatedRelation = NULL;

		colocatedTableId = heap_getattr(heapTuple, Anum_pg_dist_partition_logicalrelid,
										tupleDescriptor, &isNull);

		/*
		 * Make sure the relation isn't dropped for the remainder of
		 * the transaction.
		 */
		LockRelationOid(colocatedTableId, AccessShareLock);

		/*
		 * The relation might have been dropped just before we locked it.
		 * Let's look it up.
		 */
		colocatedRelation = RelationIdGetRelation(colocatedTableId);
		if (RelationIsValid(colocatedRelation))
		{
			/* relation still exists, we can use it */
			RelationClose(colocatedRelation);
			break;
		}

		/* relation was dropped, try the next one */
		colocatedTableId = InvalidOid;

		heapTuple = systable_getnext(scanDescriptor);
	}

	systable_endscan(scanDescriptor);
	heap_close(pgDistPartition, AccessShareLock);

	return colocatedTableId;
}