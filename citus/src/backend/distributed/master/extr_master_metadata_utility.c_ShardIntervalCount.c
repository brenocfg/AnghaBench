#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int shardIntervalArrayLength; scalar_t__ isDistributedTable; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ DistTableCacheEntry ;

/* Variables and functions */
 TYPE_1__* DistributedTableCacheEntry (int /*<<< orphan*/ ) ; 

int
ShardIntervalCount(Oid relationId)
{
	DistTableCacheEntry *cacheEntry = DistributedTableCacheEntry(relationId);
	int shardIntervalCount = 0;

	if (cacheEntry->isDistributedTable)
	{
		shardIntervalCount = cacheEntry->shardIntervalArrayLength;
	}

	return shardIntervalCount;
}