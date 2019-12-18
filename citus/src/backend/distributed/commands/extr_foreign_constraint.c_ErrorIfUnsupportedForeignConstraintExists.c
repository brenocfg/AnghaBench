#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  Var ;
struct TYPE_8__ {scalar_t__ contype; scalar_t__ confdeltype; scalar_t__ confupdtype; int /*<<< orphan*/  confrelid; } ;
struct TYPE_7__ {int /*<<< orphan*/  rd_id; } ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_constraint ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_constraint_conrelid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 scalar_t__ CONSTRAINT_FOREIGN ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  ConstraintRelidTypidNameIndexId ; 
 char DISTRIBUTE_BY_NONE ; 
 int /*<<< orphan*/ * DistPartitionKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TABLE_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FKCONSTR_ACTION_CASCADE ; 
 scalar_t__ FKCONSTR_ACTION_SETDEFAULT ; 
 scalar_t__ FKCONSTR_ACTION_SETNULL ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  ForeignConstraintFindDistKeys (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_COLOCATION_ID ; 
 int /*<<< orphan*/  InvalidOid ; 
 int IsDistributedTable (int /*<<< orphan*/ ) ; 
 char PartitionMethod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ShardReplicationFactor ; 
 int SingleReplicatedTable (int /*<<< orphan*/ ) ; 
 scalar_t__ TableColocationId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  heap_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_beginscan (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ *) ; 

void
ErrorIfUnsupportedForeignConstraintExists(Relation relation, char referencingDistMethod,
										  Var *referencingDistKey,
										  uint32 referencingColocationId)
{
	Relation pgConstraint = NULL;
	SysScanDesc scanDescriptor = NULL;
	ScanKeyData scanKey[1];
	int scanKeyCount = 1;
	HeapTuple heapTuple = NULL;

	Oid referencingTableId = relation->rd_id;
	Oid referencedTableId = InvalidOid;
	uint32 referencedColocationId = INVALID_COLOCATION_ID;
	bool selfReferencingTable = false;
	bool referencingNotReplicated = true;

	if (IsDistributedTable(referencingTableId))
	{
		/* ALTER TABLE command is applied over single replicated table */
		referencingNotReplicated = SingleReplicatedTable(referencingTableId);
	}
	else
	{
		/* Creating single replicated table with foreign constraint */
		referencingNotReplicated = (ShardReplicationFactor == 1);
	}

	pgConstraint = heap_open(ConstraintRelationId, AccessShareLock);
	ScanKeyInit(&scanKey[0], Anum_pg_constraint_conrelid, BTEqualStrategyNumber, F_OIDEQ,
				relation->rd_id);
	scanDescriptor = systable_beginscan(pgConstraint, ConstraintRelidTypidNameIndexId,
										true, NULL,
										scanKeyCount, scanKey);

	heapTuple = systable_getnext(scanDescriptor);
	while (HeapTupleIsValid(heapTuple))
	{
		Form_pg_constraint constraintForm = (Form_pg_constraint) GETSTRUCT(heapTuple);
		bool referencedIsDistributed = false;
		char referencedDistMethod = 0;
		Var *referencedDistKey = NULL;
		bool referencingIsReferenceTable = false;
		bool referencedIsReferenceTable = false;
		int referencingAttrIndex = -1;
		int referencedAttrIndex = -1;
		bool referencingColumnsIncludeDistKey = false;
		bool foreignConstraintOnDistKey = false;

		if (constraintForm->contype != CONSTRAINT_FOREIGN)
		{
			heapTuple = systable_getnext(scanDescriptor);
			continue;
		}

		referencedTableId = constraintForm->confrelid;
		selfReferencingTable = (referencingTableId == referencedTableId);

		referencedIsDistributed = IsDistributedTable(referencedTableId);
		if (!referencedIsDistributed && !selfReferencingTable)
		{
			ereport(ERROR, (errcode(ERRCODE_INVALID_TABLE_DEFINITION),
							errmsg("cannot create foreign key constraint"),
							errdetail("Referenced table must be a distributed table"
									  " or a reference table.")));
		}

		if (!selfReferencingTable)
		{
			referencedDistMethod = PartitionMethod(referencedTableId);
			referencedDistKey = (referencedDistMethod == DISTRIBUTE_BY_NONE) ?
								NULL :
								DistPartitionKey(referencedTableId);
			referencedColocationId = TableColocationId(referencedTableId);
		}
		else
		{
			referencedDistMethod = referencingDistMethod;
			referencedDistKey = referencingDistKey;
			referencedColocationId = referencingColocationId;
		}

		referencingIsReferenceTable = (referencingDistMethod == DISTRIBUTE_BY_NONE);
		referencedIsReferenceTable = (referencedDistMethod == DISTRIBUTE_BY_NONE);


		/*
		 * We support foreign keys between reference tables. No more checks
		 * are necessary.
		 */
		if (referencingIsReferenceTable && referencedIsReferenceTable)
		{
			heapTuple = systable_getnext(scanDescriptor);
			continue;
		}

		/*
		 * Foreign keys from reference tables to distributed tables are not
		 * supported.
		 */
		if (referencingIsReferenceTable && !referencedIsReferenceTable)
		{
			ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							errmsg("cannot create foreign key constraint "
								   "since foreign keys from reference tables "
								   "to distributed tables are not supported"),
							errdetail("A reference table can only have reference "
									  "keys to other reference tables")));
		}

		/*
		 * To enforce foreign constraints, tables must be co-located unless a
		 * reference table is referenced.
		 */
		if (referencingColocationId == INVALID_COLOCATION_ID ||
			(referencingColocationId != referencedColocationId &&
			 !referencedIsReferenceTable))
		{
			ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							errmsg("cannot create foreign key constraint since "
								   "relations are not colocated or not referencing "
								   "a reference table"),
							errdetail(
								"A distributed table can only have foreign keys "
								"if it is referencing another colocated hash "
								"distributed table or a reference table")));
		}

		ForeignConstraintFindDistKeys(heapTuple,
									  referencingDistKey,
									  referencedDistKey,
									  &referencingAttrIndex,
									  &referencedAttrIndex);
		referencingColumnsIncludeDistKey = (referencingAttrIndex != -1);
		foreignConstraintOnDistKey =
			(referencingColumnsIncludeDistKey && referencingAttrIndex ==
			 referencedAttrIndex);

		/*
		 * If columns in the foreign key includes the distribution key from the
		 * referencing side, we do not allow update/delete operations through
		 * foreign key constraints (e.g. ... ON UPDATE SET NULL)
		 */
		if (referencingColumnsIncludeDistKey)
		{
			/*
			 * ON DELETE SET NULL and ON DELETE SET DEFAULT is not supported. Because we do
			 * not want to set partition column to NULL or default value.
			 */
			if (constraintForm->confdeltype == FKCONSTR_ACTION_SETNULL ||
				constraintForm->confdeltype == FKCONSTR_ACTION_SETDEFAULT)
			{
				ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
								errmsg("cannot create foreign key constraint"),
								errdetail("SET NULL or SET DEFAULT is not supported"
										  " in ON DELETE operation when distribution "
										  "key is included in the foreign key constraint")));
			}

			/*
			 * ON UPDATE SET NULL, ON UPDATE SET DEFAULT and UPDATE CASCADE is not supported.
			 * Because we do not want to set partition column to NULL or default value. Also
			 * cascading update operation would require re-partitioning. Updating partition
			 * column value is not allowed anyway even outside of foreign key concept.
			 */
			if (constraintForm->confupdtype == FKCONSTR_ACTION_SETNULL ||
				constraintForm->confupdtype == FKCONSTR_ACTION_SETDEFAULT ||
				constraintForm->confupdtype == FKCONSTR_ACTION_CASCADE)
			{
				ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
								errmsg("cannot create foreign key constraint"),
								errdetail("SET NULL, SET DEFAULT or CASCADE is not "
										  "supported in ON UPDATE operation  when "
										  "distribution key included in the foreign "
										  "constraint.")));
			}
		}

		/*
		 * if tables are hash-distributed and colocated, we need to make sure that
		 * the distribution key is included in foreign constraint.
		 */
		if (!referencedIsReferenceTable && !foreignConstraintOnDistKey)
		{
			ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							errmsg("cannot create foreign key constraint"),
							errdetail("Foreign keys are supported in two cases, "
									  "either in between two colocated tables including "
									  "partition column in the same ordinal in the both "
									  "tables or from distributed to reference tables")));
		}

		/*
		 * We do not allow to create foreign constraints if shard replication factor is
		 * greater than 1. Because in our current design, multiple replicas may cause
		 * locking problems and inconsistent shard contents.
		 *
		 * Note that we allow referenced table to be a reference table (e.g., not a
		 * single replicated table). This is allowed since (a) we are sure that
		 * placements always be in the same state (b) executors are aware of reference
		 * tables and handle concurrency related issues accordingly.
		 */
		if (!referencingNotReplicated)
		{
			ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							errmsg("cannot create foreign key constraint"),
							errdetail("Citus Community Edition currently supports "
									  "foreign key constraints only for "
									  "\"citus.shard_replication_factor = 1\"."),
							errhint("Please change \"citus.shard_replication_factor to "
									"1\". To learn more about using foreign keys with "
									"other replication factors, please contact us at "
									"https://citusdata.com/about/contact_us.")));
		}

		heapTuple = systable_getnext(scanDescriptor);
	}

	/* clean up scan and close system catalog */
	systable_endscan(scanDescriptor);
	heap_close(pgConstraint, AccessShareLock);
}