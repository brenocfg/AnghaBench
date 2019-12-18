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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/ * Form_pg_sequence ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEQRELID ; 
 int /*<<< orphan*/ * SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

Form_pg_sequence
pg_get_sequencedef(Oid sequenceRelationId)
{
	Form_pg_sequence pgSequenceForm = NULL;
	HeapTuple heapTuple = NULL;

	heapTuple = SearchSysCache1(SEQRELID, sequenceRelationId);
	if (!HeapTupleIsValid(heapTuple))
	{
		elog(ERROR, "cache lookup failed for sequence %u", sequenceRelationId);
	}

	pgSequenceForm = (Form_pg_sequence) GETSTRUCT(heapTuple);

	ReleaseSysCache(heapTuple);

	return pgSequenceForm;
}