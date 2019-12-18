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
struct TYPE_3__ {char replicationModel; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ DistTableCacheEntry ;

/* Variables and functions */
 TYPE_1__* DistributedTableCacheEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char*,char*) ; 
 int /*<<< orphan*/  errmsg (char*,char*,char*) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 

void
CheckReplicationModel(Oid sourceRelationId, Oid targetRelationId)
{
	DistTableCacheEntry *sourceTableEntry = NULL;
	DistTableCacheEntry *targetTableEntry = NULL;
	char sourceReplicationModel = 0;
	char targetReplicationModel = 0;

	sourceTableEntry = DistributedTableCacheEntry(sourceRelationId);
	sourceReplicationModel = sourceTableEntry->replicationModel;

	targetTableEntry = DistributedTableCacheEntry(targetRelationId);
	targetReplicationModel = targetTableEntry->replicationModel;

	if (sourceReplicationModel != targetReplicationModel)
	{
		char *sourceRelationName = get_rel_name(sourceRelationId);
		char *targetRelationName = get_rel_name(targetRelationId);

		ereport(ERROR, (errmsg("cannot colocate tables %s and %s",
							   sourceRelationName, targetRelationName),
						errdetail("Replication models don't match for %s and %s.",
								  sourceRelationName, targetRelationName)));
	}
}