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
struct TYPE_3__ {int /*<<< orphan*/  objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/ * HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_dist_object_classid ; 
 int /*<<< orphan*/  Anum_pg_dist_object_objid ; 
 int /*<<< orphan*/  Anum_pg_dist_object_objsubid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  DistObjectPrimaryKeyIndexId () ; 
 int /*<<< orphan*/  DistObjectRelationId () ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ *) ; 

bool
IsObjectDistributed(const ObjectAddress *address)
{
	Relation pgDistObjectRel = NULL;
	ScanKeyData key[3];
	SysScanDesc pgDistObjectScan = NULL;
	HeapTuple pgDistObjectTup = NULL;
	bool result = false;

	pgDistObjectRel = heap_open(DistObjectRelationId(), AccessShareLock);

	/* scan pg_dist_object for classid = $1 AND objid = $2 AND objsubid = $3 via index */
	ScanKeyInit(&key[0], Anum_pg_dist_object_classid, BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(address->classId));
	ScanKeyInit(&key[1], Anum_pg_dist_object_objid, BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(address->objectId));
	ScanKeyInit(&key[2], Anum_pg_dist_object_objsubid, BTEqualStrategyNumber, F_INT4EQ,
				Int32GetDatum(address->objectSubId));
	pgDistObjectScan = systable_beginscan(pgDistObjectRel, DistObjectPrimaryKeyIndexId(),
										  true, NULL, 3, key);

	pgDistObjectTup = systable_getnext(pgDistObjectScan);
	if (HeapTupleIsValid(pgDistObjectTup))
	{
		result = true;
	}

	systable_endscan(pgDistObjectScan);
	relation_close(pgDistObjectRel, AccessShareLock);

	return result;
}