#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_5__ {TYPE_1__** sortedShardIntervalArray; } ;
struct TYPE_4__ {int /*<<< orphan*/  shardId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ DistTableCacheEntry ;

/* Variables and functions */
 TYPE_2__* DistributedTableCacheEntry (int /*<<< orphan*/ ) ; 

uint64
ColocatedShardIdInRelation(Oid relationId, int shardIndex)
{
	DistTableCacheEntry *tableCacheEntry = DistributedTableCacheEntry(relationId);

	return tableCacheEntry->sortedShardIntervalArray[shardIndex]->shardId;
}