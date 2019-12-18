#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* data; } ;
struct TYPE_4__ {scalar_t__ conrelid; scalar_t__ confrelid; TYPE_1__ conname; } ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_constraint ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
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
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  IsDistributedTable (scalar_t__) ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 scalar_t__ PartitionMethod (scalar_t__) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ *) ; 

bool
ConstraintIsAForeignKeyToReferenceTable(char *constraintName, Oid relationId)
{
	Relation pgConstraint = NULL;
	SysScanDesc scanDescriptor = NULL;
	ScanKeyData scanKey[1];
	int scanKeyCount = 1;
	HeapTuple heapTuple = NULL;
	bool foreignKeyToReferenceTable = false;


	pgConstraint = heap_open(ConstraintRelationId, AccessShareLock);

	ScanKeyInit(&scanKey[0], Anum_pg_constraint_contype, BTEqualStrategyNumber, F_CHAREQ,
				CharGetDatum(CONSTRAINT_FOREIGN));
	scanDescriptor = systable_beginscan(pgConstraint, InvalidOid, false,
										NULL, scanKeyCount, scanKey);

	heapTuple = systable_getnext(scanDescriptor);
	while (HeapTupleIsValid(heapTuple))
	{
		Oid referencedTableId = InvalidOid;
		Form_pg_constraint constraintForm = (Form_pg_constraint) GETSTRUCT(heapTuple);
		char *tupleConstraintName = (constraintForm->conname).data;

		if (strncmp(constraintName, tupleConstraintName, NAMEDATALEN) != 0 ||
			constraintForm->conrelid != relationId)
		{
			heapTuple = systable_getnext(scanDescriptor);
			continue;
		}

		referencedTableId = constraintForm->confrelid;

		Assert(IsDistributedTable(referencedTableId));

		if (PartitionMethod(referencedTableId) == DISTRIBUTE_BY_NONE)
		{
			foreignKeyToReferenceTable = true;
			break;
		}

		heapTuple = systable_getnext(scanDescriptor);
	}

	/* clean up scan and close system catalog */
	systable_endscan(scanDescriptor);
	heap_close(pgConstraint, AccessShareLock);

	return foreignKeyToReferenceTable;
}