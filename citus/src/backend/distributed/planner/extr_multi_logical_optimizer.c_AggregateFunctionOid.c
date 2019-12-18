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
struct TYPE_3__ {scalar_t__* values; } ;
struct TYPE_4__ {int pronargs; scalar_t__ oid; TYPE_1__ proargtypes; } ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_proc ;

/* Variables and functions */
 scalar_t__ ANYELEMENTOID ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_proc_proname ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ HeapTupleGetOid (int /*<<< orphan*/ *) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  ProcedureNameArgsNspIndexId ; 
 int /*<<< orphan*/  ProcedureRelationId ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Oid
AggregateFunctionOid(const char *functionName, Oid inputType)
{
	Oid functionOid = InvalidOid;
	Relation procRelation = NULL;
	SysScanDesc scanDescriptor = NULL;
	ScanKeyData scanKey[1];
	int scanKeyCount = 1;
	HeapTuple heapTuple = NULL;

	procRelation = heap_open(ProcedureRelationId, AccessShareLock);

	ScanKeyInit(&scanKey[0], Anum_pg_proc_proname,
				BTEqualStrategyNumber, F_NAMEEQ, CStringGetDatum(functionName));

	scanDescriptor = systable_beginscan(procRelation,
										ProcedureNameArgsNspIndexId, true,
										NULL, scanKeyCount, scanKey);

	/* loop until we find the right function */
	heapTuple = systable_getnext(scanDescriptor);
	while (HeapTupleIsValid(heapTuple))
	{
		Form_pg_proc procForm = (Form_pg_proc) GETSTRUCT(heapTuple);
		int argumentCount = procForm->pronargs;

		if (argumentCount == 1)
		{
			/* check if input type and found value type match */
			if (procForm->proargtypes.values[0] == inputType ||
				procForm->proargtypes.values[0] == ANYELEMENTOID)
			{
#if PG_VERSION_NUM < 120000
				functionOid = HeapTupleGetOid(heapTuple);
#else
				functionOid = procForm->oid;
#endif
				break;
			}
		}
		Assert(argumentCount <= 1);

		heapTuple = systable_getnext(scanDescriptor);
	}

	if (functionOid == InvalidOid)
	{
		ereport(ERROR, (errmsg("no matching oid for function: %s", functionName)));
	}

	systable_endscan(scanDescriptor);
	heap_close(procRelation, AccessShareLock);

	return functionOid;
}