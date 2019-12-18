#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_6__ {int shardIntervalArrayLength; int* arrayOfPlacementArrayLengths; TYPE_1__** arrayOfPlacementArrays; } ;
struct TYPE_5__ {scalar_t__ groupId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ GroupShardPlacement ;
typedef  TYPE_2__ DistTableCacheEntry ;

/* Variables and functions */
 TYPE_2__* DistributedTableCacheEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_1__*) ; 

List *
GroupShardPlacementsForTableOnGroup(Oid relationId, int32 groupId)
{
	DistTableCacheEntry *distTableCacheEntry = DistributedTableCacheEntry(relationId);
	List *resultList = NIL;

	int shardIndex = 0;
	int shardIntervalArrayLength = distTableCacheEntry->shardIntervalArrayLength;

	for (shardIndex = 0; shardIndex < shardIntervalArrayLength; shardIndex++)
	{
		GroupShardPlacement *placementArray =
			distTableCacheEntry->arrayOfPlacementArrays[shardIndex];
		int numberOfPlacements =
			distTableCacheEntry->arrayOfPlacementArrayLengths[shardIndex];
		int placementIndex = 0;

		for (placementIndex = 0; placementIndex < numberOfPlacements; placementIndex++)
		{
			GroupShardPlacement *placement = &placementArray[placementIndex];

			if (placement->groupId == groupId)
			{
				resultList = lappend(resultList, placement);
			}
		}
	}

	return resultList;
}