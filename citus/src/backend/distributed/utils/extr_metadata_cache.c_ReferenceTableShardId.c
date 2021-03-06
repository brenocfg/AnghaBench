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
struct TYPE_5__ {scalar_t__ partitionMethod; } ;
struct TYPE_4__ {TYPE_2__* tableEntry; } ;
typedef  TYPE_1__ ShardCacheEntry ;
typedef  TYPE_2__ DistTableCacheEntry ;

/* Variables and functions */
 scalar_t__ DISTRIBUTE_BY_NONE ; 
 TYPE_1__* LookupShardCacheEntry (int /*<<< orphan*/ ) ; 

bool
ReferenceTableShardId(uint64 shardId)
{
	ShardCacheEntry *shardEntry = LookupShardCacheEntry(shardId);
	DistTableCacheEntry *tableEntry = shardEntry->tableEntry;

	return (tableEntry->partitionMethod == DISTRIBUTE_BY_NONE);
}