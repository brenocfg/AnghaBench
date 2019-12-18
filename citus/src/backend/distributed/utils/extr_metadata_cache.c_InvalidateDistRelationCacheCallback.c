#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ distPartitionRelationId; scalar_t__ distObjectRelationId; } ;
struct TYPE_4__ {int isValid; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ DistTableCacheEntry ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DistTableCacheHash ; 
 int /*<<< orphan*/  HASH_FIND ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  InvalidateDistObjectCache () ; 
 int /*<<< orphan*/  InvalidateDistTableCache () ; 
 int /*<<< orphan*/  InvalidateMetadataSystemCache () ; 
 TYPE_3__ MetadataCache ; 
 TYPE_1__* hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
InvalidateDistRelationCacheCallback(Datum argument, Oid relationId)
{
	/* invalidate either entire cache or a specific entry */
	if (relationId == InvalidOid)
	{
		InvalidateDistTableCache();
		InvalidateDistObjectCache();
	}
	else
	{
		void *hashKey = (void *) &relationId;
		bool foundInCache = false;


		DistTableCacheEntry *cacheEntry = hash_search(DistTableCacheHash, hashKey,
													  HASH_FIND, &foundInCache);
		if (foundInCache)
		{
			cacheEntry->isValid = false;
		}

		/*
		 * If pg_dist_partition is being invalidated drop all state
		 * This happens pretty rarely, but most importantly happens during
		 * DROP EXTENSION citus;
		 */
		if (relationId == MetadataCache.distPartitionRelationId)
		{
			InvalidateMetadataSystemCache();
		}

		if (relationId == MetadataCache.distObjectRelationId)
		{
			InvalidateDistObjectCache();
		}
	}
}