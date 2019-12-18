#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char partitionMethod; } ;
struct TYPE_6__ {int /*<<< orphan*/  minValue; int /*<<< orphan*/  relationId; } ;
typedef  TYPE_1__ ShardInterval ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ DistTableCacheEntry ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 char DISTRIBUTE_BY_HASH ; 
 char DISTRIBUTE_BY_NONE ; 
 TYPE_2__* DistributedTableCacheEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int FindShardIntervalIndex (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int INVALID_SHARD_INDEX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

int
ShardIndex(ShardInterval *shardInterval)
{
	int shardIndex = INVALID_SHARD_INDEX;
	Oid distributedTableId = shardInterval->relationId;
	Datum shardMinValue = shardInterval->minValue;

	DistTableCacheEntry *cacheEntry = DistributedTableCacheEntry(distributedTableId);
	char partitionMethod = cacheEntry->partitionMethod;

	/*
	 * Note that, we can also support append and range distributed tables, but
	 * currently it is not required.
	 */
	if (partitionMethod != DISTRIBUTE_BY_HASH && partitionMethod != DISTRIBUTE_BY_NONE)
	{
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("finding index of a given shard is only supported for "
							   "hash distributed and reference tables")));
	}

	/* short-circuit for reference tables */
	if (partitionMethod == DISTRIBUTE_BY_NONE)
	{
		/* reference tables has only a single shard, so the index is fixed to 0 */
		shardIndex = 0;

		return shardIndex;
	}

	shardIndex = FindShardIntervalIndex(shardMinValue, cacheEntry);

	return shardIndex;
}