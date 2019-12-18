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
typedef  int int32 ;
struct TYPE_3__ {int /*<<< orphan*/  maxValue; int /*<<< orphan*/  minValue; } ;
typedef  TYPE_1__ ShardInterval ;

/* Variables and functions */
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int HASH_TOKEN_COUNT ; 
 int INT32_MAX ; 
 int INT32_MIN ; 

bool
HasUniformHashDistribution(ShardInterval **shardIntervalArray,
						   int shardIntervalArrayLength)
{
	uint64 hashTokenIncrement = 0;
	int shardIndex = 0;

	/* if there are no shards, there is no uniform distribution */
	if (shardIntervalArrayLength == 0)
	{
		return false;
	}

	/* calculate the hash token increment */
	hashTokenIncrement = HASH_TOKEN_COUNT / shardIntervalArrayLength;

	for (shardIndex = 0; shardIndex < shardIntervalArrayLength; shardIndex++)
	{
		ShardInterval *shardInterval = shardIntervalArray[shardIndex];
		int32 shardMinHashToken = INT32_MIN + (shardIndex * hashTokenIncrement);
		int32 shardMaxHashToken = shardMinHashToken + (hashTokenIncrement - 1);

		if (shardIndex == (shardIntervalArrayLength - 1))
		{
			shardMaxHashToken = INT32_MAX;
		}

		if (DatumGetInt32(shardInterval->minValue) != shardMinHashToken ||
			DatumGetInt32(shardInterval->maxValue) != shardMaxHashToken)
		{
			return false;
		}
	}

	return true;
}