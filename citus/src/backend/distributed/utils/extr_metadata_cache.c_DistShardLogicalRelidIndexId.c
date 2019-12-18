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
struct TYPE_2__ {int /*<<< orphan*/  distShardLogicalRelidIndexId; } ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  CachedRelationLookup (char*,int /*<<< orphan*/ *) ; 
 TYPE_1__ MetadataCache ; 

Oid
DistShardLogicalRelidIndexId(void)
{
	CachedRelationLookup("pg_dist_shard_logical_relid_index",
						 &MetadataCache.distShardLogicalRelidIndexId);

	return MetadataCache.distShardLogicalRelidIndexId;
}