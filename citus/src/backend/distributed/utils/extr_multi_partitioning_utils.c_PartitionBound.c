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
struct TYPE_2__ {int /*<<< orphan*/  relispartition; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_1__* Form_pg_class ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_class_relpartbound ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_get_expr ; 

__attribute__((used)) static char *
PartitionBound(Oid partitionId)
{
	char *partitionBoundString = NULL;
	HeapTuple tuple = NULL;
	Datum datum = 0;
	bool isnull = false;
	Datum partitionBoundDatum = 0;

	tuple = SearchSysCache1(RELOID, partitionId);
	if (!HeapTupleIsValid(tuple))
	{
		elog(ERROR, "cache lookup failed for relation %u", partitionId);
	}

	/*
	 * It is possible that the pg_class tuple of a partition has not been
	 * updated yet to set its relpartbound field.  The only case where
	 * this happens is when we open the parent relation to check using its
	 * partition descriptor that a new partition's bound does not overlap
	 * some existing partition.
	 */
	if (!((Form_pg_class) GETSTRUCT(tuple))->relispartition)
	{
		ReleaseSysCache(tuple);
		return "";
	}

	datum = SysCacheGetAttr(RELOID, tuple,
							Anum_pg_class_relpartbound,
							&isnull);
	Assert(!isnull);

	partitionBoundDatum =
		DirectFunctionCall2(pg_get_expr, datum, ObjectIdGetDatum(partitionId));

	partitionBoundString = TextDatumGetCString(partitionBoundDatum);

	ReleaseSysCache(tuple);

	return partitionBoundString;
}