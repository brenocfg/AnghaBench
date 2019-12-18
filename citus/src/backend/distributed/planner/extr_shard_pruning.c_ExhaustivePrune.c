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
struct TYPE_3__ {int shardIntervalArrayLength; int /*<<< orphan*/ ** sortedShardIntervalArray; } ;
typedef  int /*<<< orphan*/  ShardInterval ;
typedef  int /*<<< orphan*/  PruningInstance ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ DistTableCacheEntry ;
typedef  int /*<<< orphan*/  ClauseWalkerContext ;

/* Variables and functions */
 int /*<<< orphan*/  ExhaustivePruneOne (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
ExhaustivePrune(DistTableCacheEntry *cacheEntry, ClauseWalkerContext *context,
				PruningInstance *prune)
{
	List *remainingShardList = NIL;
	int shardCount = cacheEntry->shardIntervalArrayLength;
	ShardInterval **sortedShardIntervalArray = cacheEntry->sortedShardIntervalArray;
	int curIdx = 0;

	for (curIdx = 0; curIdx < shardCount; curIdx++)
	{
		ShardInterval *curInterval = sortedShardIntervalArray[curIdx];

		if (!ExhaustivePruneOne(curInterval, context, prune))
		{
			remainingShardList = lappend(remainingShardList, curInterval);
		}
	}

	return remainingShardList;
}