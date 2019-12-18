#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_2__ {scalar_t__ placementId; } ;
typedef  TYPE_1__ ShardPlacement ;

/* Variables and functions */

int
CompareShardPlacements(const void *leftElement, const void *rightElement)
{
	const ShardPlacement *leftPlacement = *((const ShardPlacement **) leftElement);
	const ShardPlacement *rightPlacement = *((const ShardPlacement **) rightElement);

	uint64 leftPlacementId = leftPlacement->placementId;
	uint64 rightPlacementId = rightPlacement->placementId;

	if (leftPlacementId < rightPlacementId)
	{
		return -1;
	}
	else if (leftPlacementId > rightPlacementId)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}