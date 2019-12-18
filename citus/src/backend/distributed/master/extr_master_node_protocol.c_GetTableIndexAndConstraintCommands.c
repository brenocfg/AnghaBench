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
struct TYPE_6__ {scalar_t__ indexrelid; scalar_t__ indisclustered; scalar_t__ indisexclusion; scalar_t__ indisunique; scalar_t__ indisprimary; } ;
struct TYPE_5__ {int addCatalog; void* schemas; } ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  TYPE_1__ OverrideSearchPath ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_index ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_index_indrelid ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 TYPE_1__* GetOverrideSearchPath (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IndexIndrelidIndexId ; 
 int /*<<< orphan*/  IndexRelationId ; 
 scalar_t__ InvalidOid ; 
 void* NIL ; 
 int OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  PopOverrideSearchPath () ; 
 int /*<<< orphan*/  PushOverrideSearchPath (TYPE_1__*) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_index_constraint (scalar_t__) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,char*) ; 
 char* pg_get_constraintdef_command (scalar_t__) ; 
 char* pg_get_indexclusterdef_string (scalar_t__) ; 
 char* pg_get_indexdef_string (scalar_t__) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ *) ; 

List *
GetTableIndexAndConstraintCommands(Oid relationId)
{
	List *indexDDLEventList = NIL;
	Relation pgIndex = NULL;
	SysScanDesc scanDescriptor = NULL;
	ScanKeyData scanKey[1];
	int scanKeyCount = 1;
	HeapTuple heapTuple = NULL;

	/*
	 * Set search_path to NIL so that all objects outside of pg_catalog will be
	 * schema-prefixed. pg_catalog will be added automatically when we call
	 * PushOverrideSearchPath(), since we set addCatalog to true;
	 */
	OverrideSearchPath *overridePath = GetOverrideSearchPath(CurrentMemoryContext);
	overridePath->schemas = NIL;
	overridePath->addCatalog = true;
	PushOverrideSearchPath(overridePath);

	/* open system catalog and scan all indexes that belong to this table */
	pgIndex = heap_open(IndexRelationId, AccessShareLock);

	ScanKeyInit(&scanKey[0], Anum_pg_index_indrelid,
				BTEqualStrategyNumber, F_OIDEQ, relationId);

	scanDescriptor = systable_beginscan(pgIndex,
										IndexIndrelidIndexId, true, /* indexOK */
										NULL, scanKeyCount, scanKey);

	heapTuple = systable_getnext(scanDescriptor);
	while (HeapTupleIsValid(heapTuple))
	{
		Form_pg_index indexForm = (Form_pg_index) GETSTRUCT(heapTuple);
		Oid indexId = indexForm->indexrelid;
		bool isConstraint = false;
		char *statementDef = NULL;

		/*
		 * A primary key index is always created by a constraint statement.
		 * A unique key index or exclusion index is created by a constraint
		 * if and only if the index has a corresponding constraint entry in pg_depend.
		 * Any other index form is never associated with a constraint.
		 */
		if (indexForm->indisprimary)
		{
			isConstraint = true;
		}
		else if (indexForm->indisunique || indexForm->indisexclusion)
		{
			Oid constraintId = get_index_constraint(indexId);
			isConstraint = OidIsValid(constraintId);
		}
		else
		{
			isConstraint = false;
		}

		/* get the corresponding constraint or index statement */
		if (isConstraint)
		{
			Oid constraintId = get_index_constraint(indexId);
			Assert(constraintId != InvalidOid);

			statementDef = pg_get_constraintdef_command(constraintId);
		}
		else
		{
			statementDef = pg_get_indexdef_string(indexId);
		}

		/* append found constraint or index definition to the list */
		indexDDLEventList = lappend(indexDDLEventList, statementDef);

		/* if table is clustered on this index, append definition to the list */
		if (indexForm->indisclustered)
		{
			char *clusteredDef = pg_get_indexclusterdef_string(indexId);
			Assert(clusteredDef != NULL);

			indexDDLEventList = lappend(indexDDLEventList, clusteredDef);
		}

		heapTuple = systable_getnext(scanDescriptor);
	}

	/* clean up scan and close system catalog */
	systable_endscan(scanDescriptor);
	heap_close(pgIndex, AccessShareLock);

	/* revert back to original search_path */
	PopOverrideSearchPath();

	return indexDDLEventList;
}