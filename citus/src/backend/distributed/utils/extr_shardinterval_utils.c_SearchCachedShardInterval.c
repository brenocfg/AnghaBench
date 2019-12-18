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
struct TYPE_3__ {int /*<<< orphan*/  maxValue; int /*<<< orphan*/  minValue; } ;
typedef  TYPE_1__ ShardInterval ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_COLLATION_OID ; 
 scalar_t__ DatumGetInt32 (int) ; 
 int FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INVALID_SHARD_INDEX ; 

int
SearchCachedShardInterval(Datum partitionColumnValue, ShardInterval **shardIntervalCache,
						  int shardCount, FmgrInfo *compareFunction)
{
	int lowerBoundIndex = 0;
	int upperBoundIndex = shardCount;

	while (lowerBoundIndex < upperBoundIndex)
	{
		int middleIndex = (lowerBoundIndex + upperBoundIndex) / 2;
		int maxValueComparison = 0;
		int minValueComparison = 0;

		minValueComparison = FunctionCall2Coll(compareFunction,
											   DEFAULT_COLLATION_OID,
											   partitionColumnValue,
											   shardIntervalCache[middleIndex]->minValue);

		if (DatumGetInt32(minValueComparison) < 0)
		{
			upperBoundIndex = middleIndex;
			continue;
		}

		maxValueComparison = FunctionCall2Coll(compareFunction,
											   DEFAULT_COLLATION_OID,
											   partitionColumnValue,
											   shardIntervalCache[middleIndex]->maxValue);

		if (DatumGetInt32(maxValueComparison) <= 0)
		{
			return middleIndex;
		}

		lowerBoundIndex = middleIndex + 1;
	}

	return INVALID_SHARD_INDEX;
}