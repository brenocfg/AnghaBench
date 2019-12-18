#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_5__ {int shardIntervalArrayLength; TYPE_1__** sortedShardIntervalArray; } ;
struct TYPE_4__ {int /*<<< orphan*/  shardId; } ;
typedef  TYPE_1__ ShardInterval ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ DistTableCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateUint64 (int /*<<< orphan*/ ) ; 
 TYPE_2__* DistributedTableCacheEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

List *
LoadShardList(Oid relationId)
{
	DistTableCacheEntry *cacheEntry = DistributedTableCacheEntry(relationId);
	List *shardList = NIL;
	int i = 0;

	for (i = 0; i < cacheEntry->shardIntervalArrayLength; i++)
	{
		ShardInterval *currentShardInterval = cacheEntry->sortedShardIntervalArray[i];
		uint64 *shardIdPointer = AllocateUint64(currentShardInterval->shardId);

		shardList = lappend(shardList, shardIdPointer);
	}

	return shardList;
}