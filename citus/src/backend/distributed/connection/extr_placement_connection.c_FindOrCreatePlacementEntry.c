#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int hasSecondaryConnections; TYPE_2__* primaryConnection; } ;
struct TYPE_15__ {int failed; int hasSecondaryConnections; TYPE_2__* primaryConnection; TYPE_6__* colocatedEntry; } ;
struct TYPE_14__ {int /*<<< orphan*/  representativeValue; int /*<<< orphan*/  colocationGroupId; int /*<<< orphan*/  nodeId; int /*<<< orphan*/  placementId; } ;
struct TYPE_13__ {int /*<<< orphan*/  representativeValue; int /*<<< orphan*/  colocationGroupId; } ;
struct TYPE_12__ {scalar_t__ partitionMethod; int /*<<< orphan*/  representativeValue; int /*<<< orphan*/  colocationGroupId; int /*<<< orphan*/  nodeId; int /*<<< orphan*/  placementId; } ;
typedef  TYPE_1__ ShardPlacement ;
typedef  TYPE_2__ ConnectionReference ;
typedef  TYPE_3__ ConnectionPlacementHashKey ;
typedef  TYPE_4__ ConnectionPlacementHashEntry ;
typedef  TYPE_3__ ColocatedPlacementsHashKey ;
typedef  TYPE_6__ ColocatedPlacementsHashEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AssociatePlacementWithShard (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ColocatedPlacementsHash ; 
 int /*<<< orphan*/  ConnectionPlacementHash ; 
 scalar_t__ DISTRIBUTE_BY_HASH ; 
 scalar_t__ DISTRIBUTE_BY_NONE ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 void* MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TopTransactionContext ; 
 void* hash_search (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ConnectionPlacementHashEntry *
FindOrCreatePlacementEntry(ShardPlacement *placement)
{
	ConnectionPlacementHashKey connKey;
	ConnectionPlacementHashEntry *placementEntry = NULL;
	bool found = false;

	connKey.placementId = placement->placementId;

	placementEntry = hash_search(ConnectionPlacementHash, &connKey, HASH_ENTER, &found);
	if (!found)
	{
		/* no connection has been chosen for this placement */
		placementEntry->failed = false;
		placementEntry->primaryConnection = NULL;
		placementEntry->hasSecondaryConnections = false;
		placementEntry->colocatedEntry = NULL;

		if (placement->partitionMethod == DISTRIBUTE_BY_HASH ||
			placement->partitionMethod == DISTRIBUTE_BY_NONE)
		{
			ColocatedPlacementsHashKey coloKey;
			ColocatedPlacementsHashEntry *colocatedEntry = NULL;

			coloKey.nodeId = placement->nodeId;
			coloKey.colocationGroupId = placement->colocationGroupId;
			coloKey.representativeValue = placement->representativeValue;

			/* look for a connection assigned to co-located placements */
			colocatedEntry = hash_search(ColocatedPlacementsHash, &coloKey, HASH_ENTER,
										 &found);
			if (!found)
			{
				void *conRef = MemoryContextAllocZero(TopTransactionContext,
													  sizeof(ConnectionReference));

				ConnectionReference *connectionReference = (ConnectionReference *) conRef;

				/*
				 * Store the co-location group information such that we can later
				 * determine whether a connection accessed different placements
				 * of the same co-location group.
				 */
				connectionReference->colocationGroupId = placement->colocationGroupId;
				connectionReference->representativeValue = placement->representativeValue;

				/*
				 * Create a connection reference that can be used for the entire
				 * set of co-located placements.
				 */
				colocatedEntry->primaryConnection = connectionReference;

				colocatedEntry->hasSecondaryConnections = false;
			}

			/*
			 * Assign the connection reference for the set of co-located placements
			 * to the current placement.
			 */
			placementEntry->primaryConnection = colocatedEntry->primaryConnection;
			placementEntry->colocatedEntry = colocatedEntry;
		}
		else
		{
			void *conRef = MemoryContextAllocZero(TopTransactionContext,
												  sizeof(ConnectionReference));

			placementEntry->primaryConnection = (ConnectionReference *) conRef;
		}
	}

	/* record association with shard, for invalidation */
	AssociatePlacementWithShard(placementEntry, placement);

	return placementEntry;
}