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
struct TYPE_4__ {scalar_t__ isDistributedTable; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ DistTableCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* LookupDistTableCacheEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 

DistTableCacheEntry *
DistributedTableCacheEntry(Oid distributedRelationId)
{
	DistTableCacheEntry *cacheEntry =
		LookupDistTableCacheEntry(distributedRelationId);

	if (cacheEntry && cacheEntry->isDistributedTable)
	{
		return cacheEntry;
	}
	else
	{
		char *relationName = get_rel_name(distributedRelationId);
		ereport(ERROR, (errmsg("relation %s is not distributed", relationName)));
	}
}