#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  conrelid; int /*<<< orphan*/  confrelid; } ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_1__* Form_pg_constraint ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int Anum_pg_constraint_confkey ; 
 int Anum_pg_constraint_conkey ; 
 int /*<<< orphan*/  Anum_pg_constraint_contype ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CONSTRAINT_FOREIGN ; 
 int /*<<< orphan*/  CharGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 scalar_t__ DISTRIBUTE_BY_NONE ; 
 int /*<<< orphan*/  F_CHAREQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 scalar_t__ HeapTupleOfForeignConstraintIncludesColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  IsDistributedTable (int /*<<< orphan*/ ) ; 
 scalar_t__ PartitionMethod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ *) ; 

bool
ColumnAppearsInForeignKeyToReferenceTable(char *columnName, Oid relationId)
{
	Relation pgConstraint = NULL;
	SysScanDesc scanDescriptor = NULL;
	ScanKeyData scanKey[1];
	int scanKeyCount = 1;
	HeapTuple heapTuple = NULL;
	bool foreignKeyToReferenceTableIncludesGivenColumn = false;

	pgConstraint = heap_open(ConstraintRelationId, AccessShareLock);

	ScanKeyInit(&scanKey[0], Anum_pg_constraint_contype, BTEqualStrategyNumber, F_CHAREQ,
				CharGetDatum(CONSTRAINT_FOREIGN));

	scanDescriptor = systable_beginscan(pgConstraint, InvalidOid, false,
										NULL, scanKeyCount, scanKey);

	heapTuple = systable_getnext(scanDescriptor);
	while (HeapTupleIsValid(heapTuple))
	{
		Oid referencedTableId = InvalidOid;
		Oid referencingTableId = InvalidOid;
		int pgConstraintKey = 0;
		Form_pg_constraint constraintForm = (Form_pg_constraint) GETSTRUCT(heapTuple);

		referencedTableId = constraintForm->confrelid;
		referencingTableId = constraintForm->conrelid;

		if (referencedTableId == relationId)
		{
			pgConstraintKey = Anum_pg_constraint_confkey;
		}
		else if (referencingTableId == relationId)
		{
			pgConstraintKey = Anum_pg_constraint_conkey;
		}
		else
		{
			/*
			 * If the constraint is not from/to the given relation, we should simply
			 * skip.
			 */
			heapTuple = systable_getnext(scanDescriptor);
			continue;
		}

		/*
		 * We check if the referenced table is a reference table. There cannot be
		 * any foreign constraint from a distributed table to a local table.
		 */
		Assert(IsDistributedTable(referencedTableId));
		if (PartitionMethod(referencedTableId) != DISTRIBUTE_BY_NONE)
		{
			heapTuple = systable_getnext(scanDescriptor);
			continue;
		}

		if (HeapTupleOfForeignConstraintIncludesColumn(heapTuple, relationId,
													   pgConstraintKey, columnName))
		{
			foreignKeyToReferenceTableIncludesGivenColumn = true;
			break;
		}

		heapTuple = systable_getnext(scanDescriptor);
	}

	/* clean up scan and close system catalog */
	systable_endscan(scanDescriptor);
	heap_close(pgConstraint, AccessShareLock);
	return foreignKeyToReferenceTableIncludesGivenColumn;
}