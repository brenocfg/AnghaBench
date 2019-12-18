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
struct TYPE_3__ {scalar_t__ partitionMethod; scalar_t__ referencedRelationsViaForeignKey; } ;
typedef  int /*<<< orphan*/  ShardPlacementAccessType ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ DistTableCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 ; 
 scalar_t__ DISTRIBUTE_BY_HASH ; 
 TYPE_1__* DistributedTableCacheEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnforceForeignKeyRestrictions ; 
 scalar_t__ HoldsConflictingLockWithReferencedRelations (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  IsDistributedTable (int /*<<< orphan*/ ) ; 
 scalar_t__ MultiShardConnectionType ; 
 scalar_t__ NIL ; 
 scalar_t__ PARALLEL_CONNECTION ; 
 int /*<<< orphan*/  PLACEMENT_ACCESS_SELECT ; 
 scalar_t__ ParallelQueryExecutedInTransaction () ; 
 char* PlacementAccessTypeToText (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLocalMultiShardModifyModeToSequential () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CheckConflictingParallelRelationAccesses(Oid relationId, ShardPlacementAccessType
										 accessType)
{
	DistTableCacheEntry *cacheEntry = NULL;
	Oid conflictingReferencingRelationId = InvalidOid;
	ShardPlacementAccessType conflictingAccessType = PLACEMENT_ACCESS_SELECT;

	if (!EnforceForeignKeyRestrictions || !IsDistributedTable(relationId))
	{
		return;
	}

	cacheEntry = DistributedTableCacheEntry(relationId);
	if (!(cacheEntry->partitionMethod == DISTRIBUTE_BY_HASH &&
		  cacheEntry->referencedRelationsViaForeignKey != NIL))
	{
		return;
	}

	if (MultiShardConnectionType == PARALLEL_CONNECTION &&
		HoldsConflictingLockWithReferencedRelations(relationId, accessType,
													&conflictingReferencingRelationId,
													&conflictingAccessType))
	{
		char *relationName = get_rel_name(relationId);
		char *conflictingRelationName = get_rel_name(conflictingReferencingRelationId);

		char *accessTypeText = PlacementAccessTypeToText(accessType);
		char *conflictingAccessTypeText =
			PlacementAccessTypeToText(conflictingAccessType);

		if (ParallelQueryExecutedInTransaction())
		{
			/*
			 * If there has already been a parallel query executed, the sequential mode
			 * would still use the already opened parallel connections to the workers,
			 * thus contradicting our purpose of using sequential mode.
			 */
			ereport(ERROR, (errmsg("cannot execute parallel %s on relation \"%s\" "
								   "after %s command on reference relation "
								   "\"%s\" because there is a foreign key between "
								   "them and \"%s\" has been accessed in this transaction",
								   accessTypeText, relationName,
								   conflictingAccessTypeText, conflictingRelationName,
								   conflictingRelationName),
							errdetail("When there is a foreign key to a reference "
									  "table, Citus needs to perform all operations "
									  "over a single connection per node to ensure "
									  "consistency."),
							errhint("Try re-running the transaction with "
									"\"SET LOCAL citus.multi_shard_modify_mode TO "
									"\'sequential\';\"")));
		}
		else
		{
			ereport(DEBUG1, (errmsg("switching to sequential query execution mode"),
							 errdetail("cannot execute parallel %s on relation \"%s\" "
									   "after %s command on reference relation "
									   "\"%s\" because there is a foreign key between "
									   "them and \"%s\" has been accessed in this transaction",
									   accessTypeText, relationName,
									   conflictingAccessTypeText, conflictingRelationName,
									   conflictingRelationName)));

			SetLocalMultiShardModifyModeToSequential();
		}
	}
}