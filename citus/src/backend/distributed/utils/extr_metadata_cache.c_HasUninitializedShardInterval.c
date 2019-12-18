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
struct TYPE_3__ {int /*<<< orphan*/  maxValueExists; int /*<<< orphan*/  minValueExists; } ;
typedef  TYPE_1__ ShardInterval ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
HasUninitializedShardInterval(ShardInterval **sortedShardIntervalArray, int shardCount)
{
	bool hasUninitializedShardInterval = false;
	ShardInterval *lastShardInterval = NULL;

	if (shardCount == 0)
	{
		return hasUninitializedShardInterval;
	}

	Assert(sortedShardIntervalArray != NULL);

	/*
	 * Since the shard interval array is sorted, and uninitialized ones stored
	 * in the end of the array, checking the last element is enough.
	 */
	lastShardInterval = sortedShardIntervalArray[shardCount - 1];
	if (!lastShardInterval->minValueExists || !lastShardInterval->maxValueExists)
	{
		hasUninitializedShardInterval = true;
	}

	return hasUninitializedShardInterval;
}