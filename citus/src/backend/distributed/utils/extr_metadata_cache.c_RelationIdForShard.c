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
struct TYPE_5__ {int /*<<< orphan*/  relationId; int /*<<< orphan*/  isDistributedTable; } ;
struct TYPE_4__ {TYPE_2__* tableEntry; } ;
typedef  TYPE_1__ ShardCacheEntry ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ DistTableCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* LookupShardCacheEntry (int /*<<< orphan*/ ) ; 

Oid
RelationIdForShard(uint64 shardId)
{
	ShardCacheEntry *shardEntry = NULL;
	DistTableCacheEntry *tableEntry = NULL;

	shardEntry = LookupShardCacheEntry(shardId);

	tableEntry = shardEntry->tableEntry;

	Assert(tableEntry->isDistributedTable);

	return tableEntry->relationId;
}