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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  newValues ;
typedef  int /*<<< orphan*/  newNulls ;
typedef  int /*<<< orphan*/  Var ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int Datum ;

/* Variables and functions */
 int Anum_pg_dist_partition_colocationid ; 
 int Anum_pg_dist_partition_logicalrelid ; 
 int Anum_pg_dist_partition_partkey ; 
 int Anum_pg_dist_partition_partmethod ; 
 int Anum_pg_dist_partition_repmodel ; 
 int CStringGetTextDatum (char*) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int CharGetDatum (char) ; 
 int /*<<< orphan*/  CitusInvalidateRelcacheByRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 char DISTRIBUTE_BY_NONE ; 
 int /*<<< orphan*/  DistPartitionRelationId () ; 
 int Natts_pg_dist_partition ; 
 int /*<<< orphan*/  NoLock ; 
 int ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RecordDistributedRelationDependencies (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int UInt32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 char* nodeToString (int /*<<< orphan*/ *) ; 

void
InsertIntoPgDistPartition(Oid relationId, char distributionMethod,
						  Var *distributionColumn, uint32 colocationId,
						  char replicationModel)
{
	Relation pgDistPartition = NULL;
	char *distributionColumnString = NULL;

	HeapTuple newTuple = NULL;
	Datum newValues[Natts_pg_dist_partition];
	bool newNulls[Natts_pg_dist_partition];

	/* open system catalog and insert new tuple */
	pgDistPartition = heap_open(DistPartitionRelationId(), RowExclusiveLock);

	/* form new tuple for pg_dist_partition */
	memset(newValues, 0, sizeof(newValues));
	memset(newNulls, false, sizeof(newNulls));

	newValues[Anum_pg_dist_partition_logicalrelid - 1] =
		ObjectIdGetDatum(relationId);
	newValues[Anum_pg_dist_partition_partmethod - 1] =
		CharGetDatum(distributionMethod);
	newValues[Anum_pg_dist_partition_colocationid - 1] = UInt32GetDatum(colocationId);
	newValues[Anum_pg_dist_partition_repmodel - 1] = CharGetDatum(replicationModel);

	/* set partkey column to NULL for reference tables */
	if (distributionMethod != DISTRIBUTE_BY_NONE)
	{
		distributionColumnString = nodeToString((Node *) distributionColumn);

		newValues[Anum_pg_dist_partition_partkey - 1] =
			CStringGetTextDatum(distributionColumnString);
	}
	else
	{
		newValues[Anum_pg_dist_partition_partkey - 1] = PointerGetDatum(NULL);
		newNulls[Anum_pg_dist_partition_partkey - 1] = true;
	}

	newTuple = heap_form_tuple(RelationGetDescr(pgDistPartition), newValues, newNulls);

	/* finally insert tuple, build index entries & register cache invalidation */
	CatalogTupleInsert(pgDistPartition, newTuple);

	CitusInvalidateRelcacheByRelid(relationId);

	RecordDistributedRelationDependencies(relationId, (Node *) distributionColumn);

	CommandCounterIncrement();
	heap_close(pgDistPartition, NoLock);
}