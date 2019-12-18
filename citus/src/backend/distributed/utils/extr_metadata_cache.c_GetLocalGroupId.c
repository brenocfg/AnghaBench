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
typedef  int int32 ;
typedef  int /*<<< orphan*/ * TupleDesc ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_dist_local_groupid ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int GROUP_ID_UPGRADING ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitializeCaches () ; 
 scalar_t__ InvalidOid ; 
 int LocalGroupId ; 
 int /*<<< orphan*/  PG_CATALOG_NAMESPACE ; 
 int /*<<< orphan*/ * RelationGetDescr (int /*<<< orphan*/ *) ; 
 scalar_t__ get_relname_relid (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * heap_open (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ *) ; 

int32
GetLocalGroupId(void)
{
	SysScanDesc scanDescriptor = NULL;
	ScanKeyData scanKey[1];
	int scanKeyCount = 0;
	HeapTuple heapTuple = NULL;
	TupleDesc tupleDescriptor = NULL;
	int32 groupId = 0;
	Relation pgDistLocalGroupId = NULL;
	Oid localGroupTableOid = InvalidOid;

	InitializeCaches();

	/*
	 * Already set the group id, no need to read the heap again.
	 */
	if (LocalGroupId != -1)
	{
		return LocalGroupId;
	}

	localGroupTableOid = get_relname_relid("pg_dist_local_group", PG_CATALOG_NAMESPACE);
	if (localGroupTableOid == InvalidOid)
	{
		return 0;
	}

	pgDistLocalGroupId = heap_open(localGroupTableOid, AccessShareLock);

	scanDescriptor = systable_beginscan(pgDistLocalGroupId,
										InvalidOid, false,
										NULL, scanKeyCount, scanKey);

	tupleDescriptor = RelationGetDescr(pgDistLocalGroupId);

	heapTuple = systable_getnext(scanDescriptor);

	if (HeapTupleIsValid(heapTuple))
	{
		bool isNull = false;
		Datum groupIdDatum = heap_getattr(heapTuple,
										  Anum_pg_dist_local_groupid,
										  tupleDescriptor, &isNull);

		groupId = DatumGetInt32(groupIdDatum);

		/* set the local cache variable */
		LocalGroupId = groupId;
	}
	else
	{
		/*
		 * Upgrade is happening. When upgrading postgres, pg_dist_local_group is
		 * temporarily empty before citus_finish_pg_upgrade() finishes execution.
		 */
		groupId = GROUP_ID_UPGRADING;
	}

	systable_endscan(scanDescriptor);
	heap_close(pgDistLocalGroupId, AccessShareLock);

	return groupId;
}