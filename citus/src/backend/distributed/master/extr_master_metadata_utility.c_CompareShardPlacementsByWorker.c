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
struct TYPE_2__ {scalar_t__ nodePort; int /*<<< orphan*/  nodeName; } ;
typedef  TYPE_1__ ShardPlacement ;

/* Variables and functions */
 int /*<<< orphan*/  WORKER_LENGTH ; 
 int strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
CompareShardPlacementsByWorker(const void *leftElement, const void *rightElement)
{
	const ShardPlacement *leftPlacement = *((const ShardPlacement **) leftElement);
	const ShardPlacement *rightPlacement = *((const ShardPlacement **) rightElement);

	int nodeNameCmp = strncmp(leftPlacement->nodeName, rightPlacement->nodeName,
							  WORKER_LENGTH);
	if (nodeNameCmp != 0)
	{
		return nodeNameCmp;
	}
	else if (leftPlacement->nodePort > rightPlacement->nodePort)
	{
		return 1;
	}
	else if (leftPlacement->nodePort < rightPlacement->nodePort)
	{
		return -1;
	}

	return 0;
}