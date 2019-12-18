#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  replace ;
typedef  int /*<<< orphan*/ * TupleDesc ;
struct TYPE_10__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_9__ {int /*<<< orphan*/  objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__* HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_dist_object_classid ; 
 int Anum_pg_dist_object_colocationid ; 
 int Anum_pg_dist_object_distribution_argument_index ; 
 int /*<<< orphan*/  Anum_pg_dist_object_objid ; 
 int /*<<< orphan*/  Anum_pg_dist_object_objsubid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  CitusInvalidateRelcacheByRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DistObjectPrimaryKeyIndexId () ; 
 int /*<<< orphan*/  DistObjectRelationId () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int Natts_pg_dist_object ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RelationGetDescr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* heap_modify_tuple (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 TYPE_2__* systable_getnext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
UpdateFunctionDistributionInfo(const ObjectAddress *distAddress,
							   int *distribution_argument_index,
							   int *colocationId)
{
	const bool indexOK = true;

	Relation pgDistObjectRel = NULL;
	TupleDesc tupleDescriptor = NULL;
	ScanKeyData scanKey[3];
	SysScanDesc scanDescriptor = NULL;
	HeapTuple heapTuple = NULL;
	Datum values[Natts_pg_dist_object];
	bool isnull[Natts_pg_dist_object];
	bool replace[Natts_pg_dist_object];

	pgDistObjectRel = heap_open(DistObjectRelationId(), RowExclusiveLock);
	tupleDescriptor = RelationGetDescr(pgDistObjectRel);

	/* scan pg_dist_object for classid = $1 AND objid = $2 AND objsubid = $3 via index */
	ScanKeyInit(&scanKey[0], Anum_pg_dist_object_classid, BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(distAddress->classId));
	ScanKeyInit(&scanKey[1], Anum_pg_dist_object_objid, BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(distAddress->objectId));
	ScanKeyInit(&scanKey[2], Anum_pg_dist_object_objsubid, BTEqualStrategyNumber,
				F_INT4EQ, ObjectIdGetDatum(distAddress->objectSubId));

	scanDescriptor = systable_beginscan(pgDistObjectRel, DistObjectPrimaryKeyIndexId(),
										indexOK,
										NULL, 3, scanKey);

	heapTuple = systable_getnext(scanDescriptor);
	if (!HeapTupleIsValid(heapTuple))
	{
		ereport(ERROR, (errmsg("could not find valid entry for node \"%d,%d,%d\" "
							   "in pg_dist_object", distAddress->classId,
							   distAddress->objectId, distAddress->objectSubId)));
	}

	memset(replace, 0, sizeof(replace));

	replace[Anum_pg_dist_object_distribution_argument_index - 1] = true;

	if (distribution_argument_index != NULL)
	{
		values[Anum_pg_dist_object_distribution_argument_index - 1] = Int32GetDatum(
			*distribution_argument_index);
		isnull[Anum_pg_dist_object_distribution_argument_index - 1] = false;
	}
	else
	{
		isnull[Anum_pg_dist_object_distribution_argument_index - 1] = true;
	}

	replace[Anum_pg_dist_object_colocationid - 1] = true;
	if (colocationId != NULL)
	{
		values[Anum_pg_dist_object_colocationid - 1] = Int32GetDatum(*colocationId);
		isnull[Anum_pg_dist_object_colocationid - 1] = false;
	}
	else
	{
		isnull[Anum_pg_dist_object_colocationid - 1] = true;
	}

	heapTuple = heap_modify_tuple(heapTuple, tupleDescriptor, values, isnull, replace);

	CatalogTupleUpdate(pgDistObjectRel, &heapTuple->t_self, heapTuple);

	CitusInvalidateRelcacheByRelid(DistObjectRelationId());

	CommandCounterIncrement();

	systable_endscan(scanDescriptor);

	heap_close(pgDistObjectRel, NoLock);
}