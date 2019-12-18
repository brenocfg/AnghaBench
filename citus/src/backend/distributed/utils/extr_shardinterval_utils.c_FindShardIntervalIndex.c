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
typedef  int uint64 ;
typedef  int uint32 ;
struct TYPE_3__ {int shardIntervalArrayLength; char partitionMethod; int /*<<< orphan*/  hasUniformHashDistribution; int /*<<< orphan*/ * shardIntervalCompareFunction; int /*<<< orphan*/ ** sortedShardIntervalArray; } ;
typedef  int /*<<< orphan*/  ShardInterval ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  TYPE_1__ DistTableCacheEntry ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char DISTRIBUTE_BY_HASH ; 
 char DISTRIBUTE_BY_NONE ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DATA_EXCEPTION ; 
 int /*<<< orphan*/  ERROR ; 
 int HASH_TOKEN_COUNT ; 
 int INT32_MIN ; 
 int INVALID_SHARD_INDEX ; 
 int SearchCachedShardInterval (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

int
FindShardIntervalIndex(Datum searchedValue, DistTableCacheEntry *cacheEntry)
{
	ShardInterval **shardIntervalCache = cacheEntry->sortedShardIntervalArray;
	int shardCount = cacheEntry->shardIntervalArrayLength;
	char partitionMethod = cacheEntry->partitionMethod;
	FmgrInfo *compareFunction = cacheEntry->shardIntervalCompareFunction;
	bool useBinarySearch = (partitionMethod != DISTRIBUTE_BY_HASH ||
							!cacheEntry->hasUniformHashDistribution);
	int shardIndex = INVALID_SHARD_INDEX;

	if (shardCount == 0)
	{
		return INVALID_SHARD_INDEX;
	}

	if (partitionMethod == DISTRIBUTE_BY_HASH)
	{
		if (useBinarySearch)
		{
			Assert(compareFunction != NULL);

			shardIndex = SearchCachedShardInterval(searchedValue, shardIntervalCache,
												   shardCount, compareFunction);

			/* we should always return a valid shard index for hash partitioned tables */
			if (shardIndex == INVALID_SHARD_INDEX)
			{
				ereport(ERROR, (errcode(ERRCODE_DATA_EXCEPTION),
								errmsg("cannot find shard interval"),
								errdetail("Hash of the partition column value "
										  "does not fall into any shards.")));
			}
		}
		else
		{
			int hashedValue = DatumGetInt32(searchedValue);
			uint64 hashTokenIncrement = HASH_TOKEN_COUNT / shardCount;

			shardIndex = (uint32) (hashedValue - INT32_MIN) / hashTokenIncrement;
			Assert(shardIndex <= shardCount);

			/*
			 * If the shard count is not power of 2, the range of the last
			 * shard becomes larger than others. For that extra piece of range,
			 * we still need to use the last shard.
			 */
			if (shardIndex == shardCount)
			{
				shardIndex = shardCount - 1;
			}
		}
	}
	else if (partitionMethod == DISTRIBUTE_BY_NONE)
	{
		/* reference tables has a single shard, all values mapped to that shard */
		Assert(shardCount == 1);

		shardIndex = 0;
	}
	else
	{
		Assert(compareFunction != NULL);

		shardIndex = SearchCachedShardInterval(searchedValue, shardIntervalCache,
											   shardCount, compareFunction);
	}

	return shardIndex;
}