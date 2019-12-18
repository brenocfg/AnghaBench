#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  replace ;
typedef  int /*<<< orphan*/  isNull ;
typedef  int /*<<< orphan*/ * TupleDesc ;
struct TYPE_7__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  int Datum ;

/* Variables and functions */
 int Anum_pg_dist_partition_colocationid ; 
 int /*<<< orphan*/  Anum_pg_dist_partition_logicalrelid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CitusInvalidateRelcacheByRelid (int /*<<< orphan*/ ) ; 
 char* ColocationIdUpdateCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DistPartitionLogicalRelidIndexId () ; 
 int /*<<< orphan*/  DistPartitionRelationId () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int Natts_pg_dist_partition ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RelationGetDescr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendCommandToWorkers (int /*<<< orphan*/ ,char*) ; 
 int ShouldSyncTableMetadata (int /*<<< orphan*/ ) ; 
 int UInt32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WORKERS_WITH_METADATA ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ *,int*,int*,int*) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 TYPE_1__* systable_getnext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
UpdateRelationColocationGroup(Oid distributedRelationId, uint32 colocationId)
{
	Relation pgDistPartition = NULL;
	HeapTuple heapTuple = NULL;
	TupleDesc tupleDescriptor = NULL;
	SysScanDesc scanDescriptor = NULL;
	bool shouldSyncMetadata = false;
	bool indexOK = true;
	int scanKeyCount = 1;
	ScanKeyData scanKey[1];
	Datum values[Natts_pg_dist_partition];
	bool isNull[Natts_pg_dist_partition];
	bool replace[Natts_pg_dist_partition];

	pgDistPartition = heap_open(DistPartitionRelationId(), RowExclusiveLock);
	tupleDescriptor = RelationGetDescr(pgDistPartition);

	ScanKeyInit(&scanKey[0], Anum_pg_dist_partition_logicalrelid,
				BTEqualStrategyNumber, F_OIDEQ, ObjectIdGetDatum(distributedRelationId));

	scanDescriptor = systable_beginscan(pgDistPartition,
										DistPartitionLogicalRelidIndexId(), indexOK,
										NULL, scanKeyCount, scanKey);

	heapTuple = systable_getnext(scanDescriptor);
	if (!HeapTupleIsValid(heapTuple))
	{
		char *distributedRelationName = get_rel_name(distributedRelationId);
		ereport(ERROR, (errmsg("could not find valid entry for relation %s",
							   distributedRelationName)));
	}

	memset(values, 0, sizeof(values));
	memset(isNull, false, sizeof(isNull));
	memset(replace, false, sizeof(replace));

	values[Anum_pg_dist_partition_colocationid - 1] = UInt32GetDatum(colocationId);
	isNull[Anum_pg_dist_partition_colocationid - 1] = false;
	replace[Anum_pg_dist_partition_colocationid - 1] = true;

	heapTuple = heap_modify_tuple(heapTuple, tupleDescriptor, values, isNull, replace);


	CatalogTupleUpdate(pgDistPartition, &heapTuple->t_self, heapTuple);

	CitusInvalidateRelcacheByRelid(distributedRelationId);

	CommandCounterIncrement();

	systable_endscan(scanDescriptor);
	heap_close(pgDistPartition, NoLock);

	shouldSyncMetadata = ShouldSyncTableMetadata(distributedRelationId);
	if (shouldSyncMetadata)
	{
		char *updateColocationIdCommand = ColocationIdUpdateCommand(distributedRelationId,
																	colocationId);

		SendCommandToWorkers(WORKERS_WITH_METADATA, updateColocationIdCommand);
	}
}