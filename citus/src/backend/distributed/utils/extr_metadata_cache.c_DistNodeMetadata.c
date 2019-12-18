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
typedef  int /*<<< orphan*/ * TupleDesc ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_dist_node_metadata_metadata ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  PG_CATALOG_NAMESPACE ; 
 int /*<<< orphan*/ * RelationGetDescr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ get_relname_relid (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * heap_open (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ *) ; 

Datum
DistNodeMetadata(void)
{
	Datum metadata = 0;
	SysScanDesc scanDescriptor = NULL;
	ScanKeyData scanKey[1];
	const int scanKeyCount = 0;
	HeapTuple heapTuple = NULL;
	Oid metadataTableOid = InvalidOid;
	Relation pgDistNodeMetadata = NULL;
	TupleDesc tupleDescriptor = NULL;

	metadataTableOid = get_relname_relid("pg_dist_node_metadata",
										 PG_CATALOG_NAMESPACE);
	if (metadataTableOid == InvalidOid)
	{
		ereport(ERROR, (errmsg("pg_dist_node_metadata was not found")));
	}

	pgDistNodeMetadata = heap_open(metadataTableOid, AccessShareLock);
	scanDescriptor = systable_beginscan(pgDistNodeMetadata,
										InvalidOid, false,
										NULL, scanKeyCount, scanKey);
	tupleDescriptor = RelationGetDescr(pgDistNodeMetadata);

	heapTuple = systable_getnext(scanDescriptor);
	if (HeapTupleIsValid(heapTuple))
	{
		bool isNull = false;
		metadata = heap_getattr(heapTuple, Anum_pg_dist_node_metadata_metadata,
								tupleDescriptor, &isNull);
		Assert(!isNull);
	}
	else
	{
		ereport(ERROR, (errmsg(
							"could not find any entries in pg_dist_metadata")));
	}

	systable_endscan(scanDescriptor);
	heap_close(pgDistNodeMetadata, AccessShareLock);

	return metadata;
}