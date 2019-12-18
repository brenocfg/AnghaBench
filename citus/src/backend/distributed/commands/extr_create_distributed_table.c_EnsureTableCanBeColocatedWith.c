#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ vartype; } ;
typedef  TYPE_1__ Var ;
struct TYPE_6__ {char partitionMethod; char replicationModel; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_2__ DistTableCacheEntry ;

/* Variables and functions */
 char DISTRIBUTE_BY_HASH ; 
 TYPE_1__* DistPartitionKey (scalar_t__) ; 
 TYPE_2__* DistributedTableCacheEntry (scalar_t__) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 char* get_rel_name (scalar_t__) ; 

__attribute__((used)) static void
EnsureTableCanBeColocatedWith(Oid relationId, char replicationModel,
							  Oid distributionColumnType, Oid sourceRelationId)
{
	DistTableCacheEntry *sourceTableEntry = DistributedTableCacheEntry(sourceRelationId);
	char sourceDistributionMethod = sourceTableEntry->partitionMethod;
	char sourceReplicationModel = sourceTableEntry->replicationModel;
	Var *sourceDistributionColumn = DistPartitionKey(sourceRelationId);
	Oid sourceDistributionColumnType = InvalidOid;

	if (sourceDistributionMethod != DISTRIBUTE_BY_HASH)
	{
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("cannot distribute relation"),
						errdetail("Currently, colocate_with option is only supported "
								  "for hash distributed tables.")));
	}

	if (sourceReplicationModel != replicationModel)
	{
		char *relationName = get_rel_name(relationId);
		char *sourceRelationName = get_rel_name(sourceRelationId);

		ereport(ERROR, (errmsg("cannot colocate tables %s and %s",
							   sourceRelationName, relationName),
						errdetail("Replication models don't match for %s and %s.",
								  sourceRelationName, relationName)));
	}

	sourceDistributionColumnType = sourceDistributionColumn->vartype;
	if (sourceDistributionColumnType != distributionColumnType)
	{
		char *relationName = get_rel_name(relationId);
		char *sourceRelationName = get_rel_name(sourceRelationId);

		ereport(ERROR, (errmsg("cannot colocate tables %s and %s",
							   sourceRelationName, relationName),
						errdetail("Distribution column types don't match for "
								  "%s and %s.", sourceRelationName,
								  relationName)));
	}
}