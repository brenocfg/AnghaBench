#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ aggcombinefn; int /*<<< orphan*/  aggtranstype; } ;
struct TYPE_3__ {scalar_t__ typtype; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_type ;
typedef  TYPE_2__* Form_pg_aggregate ;

/* Variables and functions */
 int /*<<< orphan*/  AGGFNOID ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEOID ; 
 scalar_t__ TYPTYPE_PSEUDO ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
AggregateEnabledCustom(Oid aggregateOid)
{
	HeapTuple aggTuple;
	Form_pg_aggregate aggform;
	HeapTuple typeTuple;
	Form_pg_type typeform;
	bool supportsSafeCombine;

	aggTuple = SearchSysCache1(AGGFNOID, aggregateOid);
	if (!HeapTupleIsValid(aggTuple))
	{
		elog(ERROR, "citus cache lookup failed.");
	}
	aggform = (Form_pg_aggregate) GETSTRUCT(aggTuple);

	if (aggform->aggcombinefn == InvalidOid)
	{
		ReleaseSysCache(aggTuple);
		return false;
	}

	typeTuple = SearchSysCache1(TYPEOID, aggform->aggtranstype);
	if (!HeapTupleIsValid(typeTuple))
	{
		elog(ERROR, "citus cache lookup failed.");
	}
	typeform = (Form_pg_type) GETSTRUCT(typeTuple);

	supportsSafeCombine = typeform->typtype != TYPTYPE_PSEUDO;

	ReleaseSysCache(aggTuple);
	ReleaseSysCache(typeTuple);

	return supportsSafeCombine;
}