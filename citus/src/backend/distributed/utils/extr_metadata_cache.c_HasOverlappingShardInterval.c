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
struct TYPE_3__ {int /*<<< orphan*/  minValue; int /*<<< orphan*/  maxValue; scalar_t__ maxValueExists; scalar_t__ minValueExists; } ;
typedef  TYPE_1__ ShardInterval ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CompareCall2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
HasOverlappingShardInterval(ShardInterval **shardIntervalArray,
							int shardIntervalArrayLength,
							FmgrInfo *shardIntervalSortCompareFunction)
{
	int shardIndex = 0;
	ShardInterval *lastShardInterval = NULL;
	Datum comparisonDatum = 0;
	int comparisonResult = 0;

	/* zero/a single shard can't overlap */
	if (shardIntervalArrayLength < 2)
	{
		return false;
	}

	lastShardInterval = shardIntervalArray[0];
	for (shardIndex = 1; shardIndex < shardIntervalArrayLength; shardIndex++)
	{
		ShardInterval *curShardInterval = shardIntervalArray[shardIndex];

		/* only called if !hasUninitializedShardInterval */
		Assert(lastShardInterval->minValueExists && lastShardInterval->maxValueExists);
		Assert(curShardInterval->minValueExists && curShardInterval->maxValueExists);

		comparisonDatum = CompareCall2(shardIntervalSortCompareFunction,
									   lastShardInterval->maxValue,
									   curShardInterval->minValue);
		comparisonResult = DatumGetInt32(comparisonDatum);

		if (comparisonResult >= 0)
		{
			return true;
		}

		lastShardInterval = curShardInterval;
	}

	return false;
}