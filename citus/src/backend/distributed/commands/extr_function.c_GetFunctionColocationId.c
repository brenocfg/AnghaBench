#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ ColocatedTableId (int) ; 
 int ColocationId (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DistColocationRelationId () ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnsureFunctionCanBeColocatedWithTable (scalar_t__,scalar_t__,scalar_t__) ; 
 int INVALID_COLOCATION_ID ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ REPLICATION_MODEL_COORDINATOR ; 
 scalar_t__ ReplicationModel ; 
 scalar_t__ ResolveRelationId (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ShardCount ; 
 int /*<<< orphan*/  ShardReplicationFactor ; 
 int /*<<< orphan*/  ShareLock ; 
 int TableColocationId (scalar_t__) ; 
 int /*<<< orphan*/  cstring_to_text (char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 char* get_func_name (scalar_t__) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_strncasecmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
GetFunctionColocationId(Oid functionOid, char *colocateWithTableName,
						Oid distributionArgumentOid)
{
	int colocationId = INVALID_COLOCATION_ID;
	Relation pgDistColocation = heap_open(DistColocationRelationId(), ShareLock);

	if (pg_strncasecmp(colocateWithTableName, "default", NAMEDATALEN) == 0)
	{
		Oid colocatedTableId = InvalidOid;

		/* check for default colocation group */
		colocationId = ColocationId(ShardCount, ShardReplicationFactor,
									distributionArgumentOid);

		if (colocationId == INVALID_COLOCATION_ID)
		{
			char *functionName = get_func_name(functionOid);

			ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							errmsg("cannot distribute the function \"%s\" since there "
								   "is no table to colocate with", functionName),
							errhint("Provide a distributed table via \"colocate_with\" "
									"option to create_distributed_function()")));
		}

		colocatedTableId = ColocatedTableId(colocationId);
		if (colocatedTableId != InvalidOid)
		{
			EnsureFunctionCanBeColocatedWithTable(functionOid, distributionArgumentOid,
												  colocatedTableId);
		}
		else if (ReplicationModel == REPLICATION_MODEL_COORDINATOR)
		{
			/* streaming replication model is required for metadata syncing */
			ereport(ERROR, (errmsg("cannot create a function with a distribution "
								   "argument when citus.replication_model is "
								   "'statement'"),
							errhint("Set citus.replication_model to 'streaming' "
									"before creating distributed tables")));
		}
	}
	else
	{
		Oid sourceRelationId =
			ResolveRelationId(cstring_to_text(colocateWithTableName), false);

		EnsureFunctionCanBeColocatedWithTable(functionOid, distributionArgumentOid,
											  sourceRelationId);

		colocationId = TableColocationId(sourceRelationId);
	}

	/* keep the lock */
	heap_close(pgDistColocation, NoLock);

	return colocationId;
}