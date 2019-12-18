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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/ * HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_dist_placement_groupid ; 
 int /*<<< orphan*/  Anum_pg_dist_placement_shardstate ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  DistPlacementGroupidIndexId () ; 
 int /*<<< orphan*/  DistPlacementRelationId () ; 
 int /*<<< orphan*/  FILE_FINALIZED ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ *) ; 

bool
NodeGroupHasShardPlacements(int32 groupId, bool onlyConsiderActivePlacements)
{
	const int scanKeyCount = (onlyConsiderActivePlacements ? 2 : 1);
	const bool indexOK = false;

	bool hasFinalizedPlacements = false;

	HeapTuple heapTuple = NULL;
	SysScanDesc scanDescriptor = NULL;
	ScanKeyData scanKey[2];

	Relation pgPlacement = heap_open(DistPlacementRelationId(),
									 AccessShareLock);

	ScanKeyInit(&scanKey[0], Anum_pg_dist_placement_groupid,
				BTEqualStrategyNumber, F_INT4EQ, Int32GetDatum(groupId));
	if (onlyConsiderActivePlacements)
	{
		ScanKeyInit(&scanKey[1], Anum_pg_dist_placement_shardstate,
					BTEqualStrategyNumber, F_INT4EQ, Int32GetDatum(FILE_FINALIZED));
	}

	scanDescriptor = systable_beginscan(pgPlacement,
										DistPlacementGroupidIndexId(), indexOK,
										NULL, scanKeyCount, scanKey);

	heapTuple = systable_getnext(scanDescriptor);
	hasFinalizedPlacements = HeapTupleIsValid(heapTuple);

	systable_endscan(scanDescriptor);
	heap_close(pgPlacement, NoLock);

	return hasFinalizedPlacements;
}