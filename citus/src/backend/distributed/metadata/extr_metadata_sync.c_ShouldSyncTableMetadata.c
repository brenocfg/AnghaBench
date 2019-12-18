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
struct TYPE_3__ {scalar_t__ partitionMethod; scalar_t__ replicationModel; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ DistTableCacheEntry ;

/* Variables and functions */
 scalar_t__ DISTRIBUTE_BY_HASH ; 
 scalar_t__ DISTRIBUTE_BY_NONE ; 
 TYPE_1__* DistributedTableCacheEntry (int /*<<< orphan*/ ) ; 
 scalar_t__ REPLICATION_MODEL_STREAMING ; 

bool
ShouldSyncTableMetadata(Oid relationId)
{
	DistTableCacheEntry *tableEntry = DistributedTableCacheEntry(relationId);

	bool hashDistributed = (tableEntry->partitionMethod == DISTRIBUTE_BY_HASH);
	bool streamingReplicated =
		(tableEntry->replicationModel == REPLICATION_MODEL_STREAMING);

	bool mxTable = (streamingReplicated && hashDistributed);
	bool referenceTable = (tableEntry->partitionMethod == DISTRIBUTE_BY_NONE);

	if (mxTable || referenceTable)
	{
		return true;
	}
	else
	{
		return false;
	}
}