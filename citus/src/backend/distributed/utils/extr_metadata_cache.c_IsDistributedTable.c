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
struct TYPE_3__ {int isDistributedTable; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ DistTableCacheEntry ;

/* Variables and functions */
 TYPE_1__* LookupDistTableCacheEntry (int /*<<< orphan*/ ) ; 

bool
IsDistributedTable(Oid relationId)
{
	DistTableCacheEntry *cacheEntry = NULL;

	cacheEntry = LookupDistTableCacheEntry(relationId);

	/*
	 * If extension hasn't been created, or has the wrong version and the
	 * table isn't a distributed one, LookupDistTableCacheEntry() will return NULL.
	 */
	if (!cacheEntry)
	{
		return false;
	}

	return cacheEntry->isDistributedTable;
}