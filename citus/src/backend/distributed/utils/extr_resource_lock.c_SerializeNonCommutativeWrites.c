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
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_2__ {int /*<<< orphan*/  shardId; } ;
typedef  TYPE_1__ ShardInterval ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 scalar_t__ ClusterHasKnownMetadataWorkers () ; 
 int /*<<< orphan*/  IsFirstWorkerNode () ; 
 int /*<<< orphan*/  LockReferencedReferenceShardResources (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockShardListResources (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockShardListResourcesOnFirstWorker (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ReferenceTableShardId (int /*<<< orphan*/ ) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 

void
SerializeNonCommutativeWrites(List *shardIntervalList, LOCKMODE lockMode)
{
	ShardInterval *firstShardInterval = (ShardInterval *) linitial(shardIntervalList);
	int64 firstShardId = firstShardInterval->shardId;

	if (ReferenceTableShardId(firstShardId))
	{
		if (ClusterHasKnownMetadataWorkers() && !IsFirstWorkerNode())
		{
			LockShardListResourcesOnFirstWorker(lockMode, shardIntervalList);
		}

		/*
		 * Referenced tables can cascade their changes to this table, and we
		 * want to serialize changes to keep different replicas consistent.
		 */
		LockReferencedReferenceShardResources(firstShardId, lockMode);
	}


	LockShardListResources(shardIntervalList, lockMode);
}