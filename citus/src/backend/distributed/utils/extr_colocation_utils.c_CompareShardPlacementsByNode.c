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
struct TYPE_2__ {scalar_t__ nodeId; } ;
typedef  TYPE_1__ ShardPlacement ;

/* Variables and functions */

__attribute__((used)) static int
CompareShardPlacementsByNode(const void *leftElement, const void *rightElement)
{
	const ShardPlacement *leftPlacement = *((const ShardPlacement **) leftElement);
	const ShardPlacement *rightPlacement = *((const ShardPlacement **) rightElement);

	/* if node names are same, check node ports */
	if (leftPlacement->nodeId < rightPlacement->nodeId)
	{
		return -1;
	}
	else if (leftPlacement->nodeId > rightPlacement->nodeId)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}