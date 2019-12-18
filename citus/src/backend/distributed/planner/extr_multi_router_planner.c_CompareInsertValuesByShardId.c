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
typedef  scalar_t__ int64 ;
struct TYPE_2__ {scalar_t__ shardId; scalar_t__ listIndex; } ;
typedef  TYPE_1__ InsertValues ;
typedef  scalar_t__ Index ;

/* Variables and functions */

__attribute__((used)) static int
CompareInsertValuesByShardId(const void *leftElement, const void *rightElement)
{
	InsertValues *leftValue = *((InsertValues **) leftElement);
	InsertValues *rightValue = *((InsertValues **) rightElement);
	int64 leftShardId = leftValue->shardId;
	int64 rightShardId = rightValue->shardId;
	Index leftIndex = leftValue->listIndex;
	Index rightIndex = rightValue->listIndex;

	if (leftShardId > rightShardId)
	{
		return 1;
	}
	else if (leftShardId < rightShardId)
	{
		return -1;
	}
	else
	{
		/* shard identifiers are the same, list index is secondary sort key */
		if (leftIndex > rightIndex)
		{
			return 1;
		}
		else if (leftIndex < rightIndex)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
}