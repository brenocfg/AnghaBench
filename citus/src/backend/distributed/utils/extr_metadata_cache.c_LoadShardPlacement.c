#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  ShardPlacement ;
typedef  int /*<<< orphan*/  ShardCacheEntry ;
typedef  int /*<<< orphan*/  GroupShardPlacement ;

/* Variables and functions */
 int /*<<< orphan*/ * LoadGroupShardPlacement (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LookupShardCacheEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ResolveGroupShardPlacement (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ShardPlacement *
LoadShardPlacement(uint64 shardId, uint64 placementId)
{
	ShardCacheEntry *shardEntry = NULL;
	GroupShardPlacement *groupPlacement = NULL;
	ShardPlacement *nodePlacement = NULL;

	shardEntry = LookupShardCacheEntry(shardId);
	groupPlacement = LoadGroupShardPlacement(shardId, placementId);
	nodePlacement = ResolveGroupShardPlacement(groupPlacement, shardEntry);

	return nodePlacement;
}