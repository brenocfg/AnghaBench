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
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  text ;
struct TYPE_3__ {int /*<<< orphan*/  vartype; } ;
typedef  TYPE_1__ Var ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 scalar_t__ ColocationId (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateColocationGroup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateReferenceTableColocationId () ; 
 char DISTRIBUTE_BY_APPEND ; 
 char DISTRIBUTE_BY_NONE ; 
 char DISTRIBUTE_BY_RANGE ; 
 int /*<<< orphan*/  DistColocationRelationId () ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnsureTableCanBeColocatedWith (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 scalar_t__ GetNextColocationId () ; 
 scalar_t__ INVALID_COLOCATION_ID ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ResolveRelationId (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ShardCount ; 
 int /*<<< orphan*/  ShardReplicationFactor ; 
 scalar_t__ TableColocationId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cstring_to_text (char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_strncasecmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32
ColocationIdForNewTable(Oid relationId, Var *distributionColumn,
						char distributionMethod, char replicationModel,
						char *colocateWithTableName, bool viaDeprecatedAPI)
{
	uint32 colocationId = INVALID_COLOCATION_ID;

	if (viaDeprecatedAPI)
	{
		return colocationId;
	}
	else if (distributionMethod == DISTRIBUTE_BY_APPEND ||
			 distributionMethod == DISTRIBUTE_BY_RANGE)
	{
		if (pg_strncasecmp(colocateWithTableName, "default", NAMEDATALEN) != 0)
		{
			ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							errmsg("cannot distribute relation"),
							errdetail("Currently, colocate_with option is only supported "
									  "for hash distributed tables.")));
		}

		return colocationId;
	}
	else if (distributionMethod == DISTRIBUTE_BY_NONE)
	{
		return CreateReferenceTableColocationId();
	}
	else
	{
		/*
		 * Get an exclusive lock on the colocation system catalog. Therefore, we
		 * can be sure that there will no modifications on the colocation table
		 * until this transaction is committed.
		 */
		Relation pgDistColocation = heap_open(DistColocationRelationId(), ExclusiveLock);

		Oid distributionColumnType = distributionColumn->vartype;
		bool createdColocationGroup = false;

		if (pg_strncasecmp(colocateWithTableName, "default", NAMEDATALEN) == 0)
		{
			/* check for default colocation group */
			colocationId = ColocationId(ShardCount, ShardReplicationFactor,
										distributionColumnType);

			if (colocationId == INVALID_COLOCATION_ID)
			{
				colocationId = CreateColocationGroup(ShardCount, ShardReplicationFactor,
													 distributionColumnType);
				createdColocationGroup = true;
			}
		}
		else if (pg_strncasecmp(colocateWithTableName, "none", NAMEDATALEN) == 0)
		{
			colocationId = GetNextColocationId();

			createdColocationGroup = true;
		}
		else
		{
			text *colocateWithTableNameText = cstring_to_text(colocateWithTableName);
			Oid sourceRelationId = ResolveRelationId(colocateWithTableNameText, false);

			EnsureTableCanBeColocatedWith(relationId, replicationModel,
										  distributionColumnType, sourceRelationId);

			colocationId = TableColocationId(sourceRelationId);
		}

		/*
		 * If we created a new colocation group then we need to keep the lock to
		 * prevent a concurrent create_distributed_table call from creating another
		 * colocation group with the same parameters. If we're using an existing
		 * colocation group then other transactions will use the same one.
		 */
		if (createdColocationGroup)
		{
			/* keep the exclusive lock */
			heap_close(pgDistColocation, NoLock);
		}
		else
		{
			/* release the exclusive lock */
			heap_close(pgDistColocation, ExclusiveLock);
		}
	}

	return colocationId;
}