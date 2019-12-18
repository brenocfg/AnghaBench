#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_4__ {int /*<<< orphan*/  relationId; } ;
typedef  TYPE_1__ ShardInterval ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  ColocatedShardIdInRelation (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* LoadShardInterval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockShardResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PartitionParentOid (int /*<<< orphan*/ ) ; 
 scalar_t__ PartitionTable (int /*<<< orphan*/ ) ; 
 int ShardIndex (TYPE_1__*) ; 

void
LockParentShardResourceIfPartition(uint64 shardId, LOCKMODE lockMode)
{
	ShardInterval *shardInterval = LoadShardInterval(shardId);
	Oid relationId = shardInterval->relationId;

	if (PartitionTable(relationId))
	{
		int shardIndex = ShardIndex(shardInterval);
		Oid parentRelationId = PartitionParentOid(relationId);
		uint64 parentShardId = ColocatedShardIdInRelation(parentRelationId, shardIndex);

		LockShardResource(parentShardId, lockMode);
	}
}