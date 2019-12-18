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
struct TYPE_6__ {scalar_t__ partitionMethod; int /*<<< orphan*/ ** sortedShardIntervalArray; TYPE_1__* partitionColumn; int /*<<< orphan*/  hashFunction; } ;
struct TYPE_5__ {int /*<<< orphan*/  varcollid; } ;
typedef  int /*<<< orphan*/  ShardInterval ;
typedef  TYPE_2__ DistTableCacheEntry ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DISTRIBUTE_BY_HASH ; 
 int FindShardIntervalIndex (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  FunctionCall1Coll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INVALID_SHARD_INDEX ; 

ShardInterval *
FindShardInterval(Datum partitionColumnValue, DistTableCacheEntry *cacheEntry)
{
	Datum searchedValue = partitionColumnValue;
	int shardIndex = INVALID_SHARD_INDEX;

	if (cacheEntry->partitionMethod == DISTRIBUTE_BY_HASH)
	{
		searchedValue = FunctionCall1Coll(cacheEntry->hashFunction,
										  cacheEntry->partitionColumn->varcollid,
										  partitionColumnValue);
	}

	shardIndex = FindShardIntervalIndex(searchedValue, cacheEntry);

	if (shardIndex == INVALID_SHARD_INDEX)
	{
		return NULL;
	}

	return cacheEntry->sortedShardIntervalArray[shardIndex];
}