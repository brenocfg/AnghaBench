#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  replace ;
typedef  int /*<<< orphan*/  isnull ;
typedef  int /*<<< orphan*/ * TupleDesc ;
struct TYPE_8__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  TYPE_1__* HeapTuple ;
typedef  int Datum ;
typedef  int /*<<< orphan*/  CatalogIndexState ;

/* Variables and functions */
 int Anum_pg_dist_node_hasmetadata ; 
 int Anum_pg_dist_node_metadatasynced ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int BoolGetDatum (int) ; 
 int /*<<< orphan*/  CatalogCloseIndexes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogOpenIndexes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CatalogTupleUpdateWithInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DistNodeRelationId () ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  F_BOOLEQ ; 
 scalar_t__ HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int Natts_pg_dist_node ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/ * RelationGetDescr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_1__*) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ *,int*,int*,int*) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 TYPE_1__* systable_getnext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
UnsetMetadataSyncedForAll(void)
{
	bool updatedAtLeastOne = false;
	Relation relation = NULL;
	SysScanDesc scanDescriptor = NULL;
	ScanKeyData scanKey[2];
	int scanKeyCount = 2;
	bool indexOK = false;
	HeapTuple heapTuple = NULL;
	TupleDesc tupleDescriptor = NULL;
	CatalogIndexState indstate;

	/*
	 * Concurrent master_update_node() calls might iterate and try to update
	 * pg_dist_node in different orders. To protect against deadlock, we
	 * get an exclusive lock here.
	 */
	relation = heap_open(DistNodeRelationId(), ExclusiveLock);
	tupleDescriptor = RelationGetDescr(relation);
	ScanKeyInit(&scanKey[0], Anum_pg_dist_node_hasmetadata,
				BTEqualStrategyNumber, F_BOOLEQ, BoolGetDatum(true));
	ScanKeyInit(&scanKey[1], Anum_pg_dist_node_metadatasynced,
				BTEqualStrategyNumber, F_BOOLEQ, BoolGetDatum(true));

	indstate = CatalogOpenIndexes(relation);

	scanDescriptor = systable_beginscan(relation,
										InvalidOid, indexOK,
										NULL, scanKeyCount, scanKey);

	heapTuple = systable_getnext(scanDescriptor);
	if (HeapTupleIsValid(heapTuple))
	{
		updatedAtLeastOne = true;
	}

	while (HeapTupleIsValid(heapTuple))
	{
		HeapTuple newHeapTuple = NULL;
		Datum values[Natts_pg_dist_node];
		bool isnull[Natts_pg_dist_node];
		bool replace[Natts_pg_dist_node];

		memset(replace, false, sizeof(replace));
		memset(isnull, false, sizeof(isnull));
		memset(values, 0, sizeof(values));

		values[Anum_pg_dist_node_metadatasynced - 1] = BoolGetDatum(false);
		replace[Anum_pg_dist_node_metadatasynced - 1] = true;

		newHeapTuple = heap_modify_tuple(heapTuple, tupleDescriptor, values, isnull,
										 replace);

		CatalogTupleUpdateWithInfo(relation, &newHeapTuple->t_self, newHeapTuple,
								   indstate);

		CommandCounterIncrement();

		heap_freetuple(newHeapTuple);

		heapTuple = systable_getnext(scanDescriptor);
	}

	systable_endscan(scanDescriptor);
	CatalogCloseIndexes(indstate);
	heap_close(relation, NoLock);

	return updatedAtLeastOne;
}