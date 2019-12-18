#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_4__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  TYPE_1__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_dist_colocation_colocationid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CitusInvalidateRelcacheByRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DistColocationRelationId () ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 scalar_t__ HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  RelationGetReplicaIndex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UInt32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_heap_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 TYPE_1__* systable_getnext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
DeleteColocationGroup(uint32 colocationId)
{
	Relation pgDistColocation = NULL;
	SysScanDesc scanDescriptor = NULL;
	int scanKeyCount = 1;
	ScanKeyData scanKey[1];
	bool indexOK = false;
	HeapTuple heapTuple = NULL;

	pgDistColocation = heap_open(DistColocationRelationId(), RowExclusiveLock);

	ScanKeyInit(&scanKey[0], Anum_pg_dist_colocation_colocationid,
				BTEqualStrategyNumber, F_INT4EQ, UInt32GetDatum(colocationId));

	scanDescriptor = systable_beginscan(pgDistColocation, InvalidOid, indexOK,
										NULL, scanKeyCount, scanKey);

	/* if a record is found, delete it */
	heapTuple = systable_getnext(scanDescriptor);
	if (HeapTupleIsValid(heapTuple))
	{
		/*
		 * simple_heap_delete() expects that the caller has at least an
		 * AccessShareLock on replica identity index.
		 */
		Relation replicaIndex =
			index_open(RelationGetReplicaIndex(pgDistColocation),
					   AccessShareLock);
		simple_heap_delete(pgDistColocation, &(heapTuple->t_self));

		CitusInvalidateRelcacheByRelid(DistColocationRelationId());
		CommandCounterIncrement();
		heap_close(replicaIndex, AccessShareLock);
	}

	systable_endscan(scanDescriptor);
	heap_close(pgDistColocation, RowExclusiveLock);
}