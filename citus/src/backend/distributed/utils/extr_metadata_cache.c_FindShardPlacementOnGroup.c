#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  scalar_t__ int32 ;
struct TYPE_9__ {int* arrayOfPlacementArrayLengths; TYPE_2__** arrayOfPlacementArrays; } ;
struct TYPE_8__ {scalar_t__ groupId; } ;
struct TYPE_7__ {size_t shardIndex; TYPE_3__* tableEntry; } ;
typedef  int /*<<< orphan*/  ShardPlacement ;
typedef  TYPE_1__ ShardCacheEntry ;
typedef  TYPE_2__ GroupShardPlacement ;
typedef  TYPE_3__ DistTableCacheEntry ;

/* Variables and functions */
 TYPE_1__* LookupShardCacheEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ResolveGroupShardPlacement (TYPE_2__*,TYPE_1__*) ; 

ShardPlacement *
FindShardPlacementOnGroup(int32 groupId, uint64 shardId)
{
	ShardCacheEntry *shardEntry = NULL;
	DistTableCacheEntry *tableEntry = NULL;
	GroupShardPlacement *placementArray = NULL;
	int numberOfPlacements = 0;
	ShardPlacement *placementOnNode = NULL;
	int placementIndex = 0;

	shardEntry = LookupShardCacheEntry(shardId);
	tableEntry = shardEntry->tableEntry;
	placementArray = tableEntry->arrayOfPlacementArrays[shardEntry->shardIndex];
	numberOfPlacements = tableEntry->arrayOfPlacementArrayLengths[shardEntry->shardIndex];

	for (placementIndex = 0; placementIndex < numberOfPlacements; placementIndex++)
	{
		GroupShardPlacement *placement = &placementArray[placementIndex];

		if (placement->groupId == groupId)
		{
			placementOnNode = ResolveGroupShardPlacement(placement, shardEntry);
			break;
		}
	}

	return placementOnNode;
}