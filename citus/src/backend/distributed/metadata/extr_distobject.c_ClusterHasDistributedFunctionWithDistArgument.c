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
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_2__ {scalar_t__ classid; } ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_1__* Form_pg_dist_object ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_dist_object_distribution_argument_index ; 
 int /*<<< orphan*/  DistObjectRelationId () ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ ProcedureRelationId ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int heap_attisnull (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ *) ; 

bool
ClusterHasDistributedFunctionWithDistArgument(void)
{
	bool foundDistributedFunction = false;

	SysScanDesc pgDistObjectScan = NULL;
	HeapTuple pgDistObjectTup = NULL;

	Relation pgDistObjectRel = heap_open(DistObjectRelationId(), AccessShareLock);

	TupleDesc tupleDescriptor = RelationGetDescr(pgDistObjectRel);

	pgDistObjectScan =
		systable_beginscan(pgDistObjectRel, InvalidOid, false, NULL, 0, NULL);
	while (HeapTupleIsValid(pgDistObjectTup = systable_getnext(pgDistObjectScan)))
	{
		Form_pg_dist_object pg_dist_object =
			(Form_pg_dist_object) GETSTRUCT(pgDistObjectTup);

		if (pg_dist_object->classid == ProcedureRelationId)
		{
			bool distArgumentIsNull = false;
			distArgumentIsNull =
				heap_attisnull(pgDistObjectTup,
							   Anum_pg_dist_object_distribution_argument_index,
							   tupleDescriptor);

			/* we found one distributed function that has an distribution argument */
			if (!distArgumentIsNull)
			{
				foundDistributedFunction = true;

				break;
			}
		}
	}

	systable_endscan(pgDistObjectScan);
	relation_close(pgDistObjectRel, AccessShareLock);

	return foundDistributedFunction;
}