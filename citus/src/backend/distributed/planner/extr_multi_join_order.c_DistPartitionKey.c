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
typedef  int /*<<< orphan*/  Var ;
struct TYPE_3__ {scalar_t__ partitionMethod; int /*<<< orphan*/  partitionColumn; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ DistTableCacheEntry ;

/* Variables and functions */
 scalar_t__ DISTRIBUTE_BY_NONE ; 
 TYPE_1__* DistributedTableCacheEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ ) ; 

Var *
DistPartitionKey(Oid relationId)
{
	DistTableCacheEntry *partitionEntry = DistributedTableCacheEntry(relationId);

	/* reference tables do not have partition column */
	if (partitionEntry->partitionMethod == DISTRIBUTE_BY_NONE)
	{
		return NULL;
	}

	return copyObject(partitionEntry->partitionColumn);
}