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
typedef  scalar_t__ uint32 ;
struct TYPE_3__ {scalar_t__ shardIntervalArrayLength; scalar_t__ colocationId; scalar_t__ partitionMethod; int /*<<< orphan*/ * shardIntervalCompareFunction; int /*<<< orphan*/ ** sortedShardIntervalArray; } ;
typedef  int /*<<< orphan*/  ShardInterval ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  TYPE_1__ DistTableCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoPlacedShardIntervals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ DISTRIBUTE_BY_HASH ; 
 TYPE_1__* DistributedTableCacheEntry (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_COLOCATION_ID ; 
 int ShardIntervalsEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
CoPartitionedTables(Oid firstRelationId, Oid secondRelationId)
{
	bool coPartitionedTables = true;
	uint32 intervalIndex = 0;
	DistTableCacheEntry *firstTableCache = DistributedTableCacheEntry(firstRelationId);
	DistTableCacheEntry *secondTableCache = DistributedTableCacheEntry(secondRelationId);
	ShardInterval **sortedFirstIntervalArray = firstTableCache->sortedShardIntervalArray;
	ShardInterval **sortedSecondIntervalArray =
		secondTableCache->sortedShardIntervalArray;
	uint32 firstListShardCount = firstTableCache->shardIntervalArrayLength;
	uint32 secondListShardCount = secondTableCache->shardIntervalArrayLength;
	FmgrInfo *comparisonFunction = firstTableCache->shardIntervalCompareFunction;

	if (firstListShardCount != secondListShardCount)
	{
		return false;
	}

	/* if there are not any shards just return true */
	if (firstListShardCount == 0)
	{
		return true;
	}

	Assert(comparisonFunction != NULL);

	/*
	 * Check if the tables have the same colocation ID - if so, we know
	 * they're colocated.
	 */
	if (firstTableCache->colocationId != INVALID_COLOCATION_ID &&
		firstTableCache->colocationId == secondTableCache->colocationId)
	{
		return true;
	}

	/*
	 * For hash distributed tables two tables are accepted as colocated only if
	 * they have the same colocationId. Otherwise they may have same minimum and
	 * maximum values for each shard interval, yet hash function may result with
	 * different values for the same value. int vs bigint can be given as an
	 * example.
	 */
	if (firstTableCache->partitionMethod == DISTRIBUTE_BY_HASH ||
		secondTableCache->partitionMethod == DISTRIBUTE_BY_HASH)
	{
		return false;
	}


	/*
	 * If not known to be colocated check if the remaining shards are
	 * anyway. Do so by comparing the shard interval arrays that are sorted on
	 * interval minimum values. Then it compares every shard interval in order
	 * and if any pair of shard intervals are not equal or they are not located
	 * in the same node it returns false.
	 */
	for (intervalIndex = 0; intervalIndex < firstListShardCount; intervalIndex++)
	{
		ShardInterval *firstInterval = sortedFirstIntervalArray[intervalIndex];
		ShardInterval *secondInterval = sortedSecondIntervalArray[intervalIndex];

		bool shardIntervalsEqual = ShardIntervalsEqual(comparisonFunction,
													   firstInterval,
													   secondInterval);
		if (!shardIntervalsEqual || !CoPlacedShardIntervals(firstInterval,
															secondInterval))
		{
			coPartitionedTables = false;
			break;
		}
	}

	return coPartitionedTables;
}