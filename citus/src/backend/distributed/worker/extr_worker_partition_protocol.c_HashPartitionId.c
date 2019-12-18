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
typedef  int uint64 ;
typedef  int uint32 ;
typedef  scalar_t__ int32 ;
struct TYPE_2__ {int partitionCount; scalar_t__ hasUniformHashDistribution; int /*<<< orphan*/  collation; int /*<<< orphan*/ * comparisonFunction; int /*<<< orphan*/ ** syntheticShardIntervalArray; int /*<<< orphan*/ * hashFunction; } ;
typedef  int /*<<< orphan*/  ShardInterval ;
typedef  TYPE_1__ HashPartitionContext ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 scalar_t__ DatumGetInt32 (scalar_t__) ; 
 scalar_t__ FunctionCall1Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int HASH_TOKEN_COUNT ; 
 scalar_t__ INT32_MIN ; 
 int SearchCachedShardInterval (scalar_t__,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32
HashPartitionId(Datum partitionValue, const void *context)
{
	HashPartitionContext *hashPartitionContext = (HashPartitionContext *) context;
	FmgrInfo *hashFunction = hashPartitionContext->hashFunction;
	uint32 partitionCount = hashPartitionContext->partitionCount;
	ShardInterval **syntheticShardIntervalArray =
		hashPartitionContext->syntheticShardIntervalArray;
	FmgrInfo *comparisonFunction = hashPartitionContext->comparisonFunction;
	Datum hashDatum = FunctionCall1Coll(hashFunction, hashPartitionContext->collation,
										partitionValue);
	int32 hashResult = 0;
	uint32 hashPartitionId = 0;

	if (hashDatum == 0)
	{
		return hashPartitionId;
	}

	if (hashPartitionContext->hasUniformHashDistribution)
	{
		uint64 hashTokenIncrement = HASH_TOKEN_COUNT / partitionCount;

		hashResult = DatumGetInt32(hashDatum);
		hashPartitionId = (uint32) (hashResult - INT32_MIN) / hashTokenIncrement;
	}
	else
	{
		hashPartitionId =
			SearchCachedShardInterval(hashDatum, syntheticShardIntervalArray,
									  partitionCount, comparisonFunction);
	}


	return hashPartitionId;
}