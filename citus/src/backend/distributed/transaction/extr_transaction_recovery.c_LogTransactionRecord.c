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
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  isNulls ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/ * TupleDesc ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int Datum ;

/* Variables and functions */
 int Anum_pg_dist_transaction_gid ; 
 int Anum_pg_dist_transaction_groupid ; 
 int CStringGetTextDatum (char*) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DistTransactionRelationId () ; 
 int Int32GetDatum (int /*<<< orphan*/ ) ; 
 int Natts_pg_dist_transaction ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/ * RelationGetDescr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_form_tuple (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

void
LogTransactionRecord(int32 groupId, char *transactionName)
{
	Relation pgDistTransaction = NULL;
	TupleDesc tupleDescriptor = NULL;
	HeapTuple heapTuple = NULL;
	Datum values[Natts_pg_dist_transaction];
	bool isNulls[Natts_pg_dist_transaction];

	/* form new transaction tuple */
	memset(values, 0, sizeof(values));
	memset(isNulls, false, sizeof(isNulls));

	values[Anum_pg_dist_transaction_groupid - 1] = Int32GetDatum(groupId);
	values[Anum_pg_dist_transaction_gid - 1] = CStringGetTextDatum(transactionName);

	/* open transaction relation and insert new tuple */
	pgDistTransaction = heap_open(DistTransactionRelationId(), RowExclusiveLock);

	tupleDescriptor = RelationGetDescr(pgDistTransaction);
	heapTuple = heap_form_tuple(tupleDescriptor, values, isNulls);

	CatalogTupleInsert(pgDistTransaction, heapTuple);

	CommandCounterIncrement();

	/* close relation and invalidate previous cache entry */
	heap_close(pgDistTransaction, NoLock);
}