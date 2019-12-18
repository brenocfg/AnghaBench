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
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int INVALID_SHARD_INDEX ; 
 int PerformCompare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcSetArg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
UpperShardBoundary(Datum partitionColumnValue, ShardInterval **shardIntervalCache,
				   int shardCount, FunctionCallInfo compareFunction, bool includeMin)
{
	int lowerBoundIndex = 0;
	int upperBoundIndex = shardCount;

	Assert(shardCount != 0);

	/* setup partitionColumnValue argument once */
	fcSetArg(compareFunction, 0, partitionColumnValue);

	while (lowerBoundIndex < upperBoundIndex)
	{
		int middleIndex = lowerBoundIndex + ((upperBoundIndex - lowerBoundIndex) / 2);
		int maxValueComparison = 0;
		int minValueComparison = 0;

		/* setup minValue as argument */
		fcSetArg(compareFunction, 1, shardIntervalCache[middleIndex]->minValue);

		/* execute cmp(partitionValue, lowerBound) */
		minValueComparison = PerformCompare(compareFunction);

		/* and evaluate results */
		if ((minValueComparison == 0 && !includeMin) ||
			minValueComparison < 0)
		{
			/* value smaller than entire range */
			upperBoundIndex = middleIndex;
			continue;
		}

		/* setup maxValue as argument */
		fcSetArg(compareFunction, 1, shardIntervalCache[middleIndex]->maxValue);

		/* execute cmp(partitionValue, upperBound) */
		maxValueComparison = PerformCompare(compareFunction);

		if (maxValueComparison > 0)
		{
			/* value bigger than entire range */
			lowerBoundIndex = middleIndex + 1;
			continue;
		}

		/* found interval containing partitionValue */
		return middleIndex;
	}

	Assert(lowerBoundIndex == upperBoundIndex);

	/*
	 * If we get here, none of the ShardIntervals exactly contain the value
	 * (we'd have hit the return middleIndex; case otherwise). Figure out
	 * whether there's possibly any interval containing a value that's smaller
	 * than the partition key one.
	 */
	if (upperBoundIndex == shardCount)
	{
		/* all intervals are smaller, thus return 0 */
		return shardCount - 1;
	}
	else if (upperBoundIndex == 0)
	{
		/* partition value is smaller than all partition values */
		return INVALID_SHARD_INDEX;
	}

	/* value falls inbetween intervals, return the inverval one smaller as bound */
	return upperBoundIndex - 1;
}