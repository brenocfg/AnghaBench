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
typedef  int /*<<< orphan*/  List ;
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
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/ * RelationGetDescr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ heap_getattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend_oid (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
ColocationGroupTableList(Oid colocationId)
{
	List *colocatedTableList = NIL;
	Relation pgDistPartition = NULL;
	TupleDesc tupleDescriptor = NULL;
	SysScanDesc scanDescriptor = NULL;
	HeapTuple heapTuple = NULL;
	bool indexOK = true;
	int scanKeyCount = 1;
	ScanKeyData scanKey[1];

	/*
	 * If distribution type of the table is not hash, the table is only co-located
	 * with itself.
	 */
	if (colocationId == INVALID_COLOCATION_ID)
	{
		return NIL;
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
		bool isNull = false;
		Oid colocatedTableId = heap_getattr(heapTuple,
											Anum_pg_dist_partition_logicalrelid,
											tupleDescriptor, &isNull);

		colocatedTableList = lappend_oid(colocatedTableList, colocatedTableId);
		heapTuple = systable_getnext(scanDescriptor);
	}

	systable_endscan(scanDescriptor);
	heap_close(pgDistPartition, AccessShareLock);

	return colocatedTableList;
}