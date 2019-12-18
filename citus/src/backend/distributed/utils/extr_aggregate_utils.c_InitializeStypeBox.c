#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  aggcombinefn; int /*<<< orphan*/  aggserialfn; int /*<<< orphan*/  aggdeserialfn; int /*<<< orphan*/  aggtransfn; int /*<<< orphan*/  aggfinalfn; int /*<<< orphan*/  aggfnoid; } ;
struct TYPE_4__ {int valueInit; scalar_t__ value; scalar_t__ valueNull; int /*<<< orphan*/  transtype; } ;
typedef  TYPE_1__ StypeBox ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  TYPE_2__* Form_pg_aggregate ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AGGFNOID ; 
 int /*<<< orphan*/  AggCheckCallContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Anum_pg_aggregate_agginitval ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJECT_AGGREGATE ; 
 int /*<<< orphan*/  OBJECT_FUNCTION ; 
 scalar_t__ OidInputFunctionCall (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 char* TextDatumGetCString (scalar_t__) ; 
 int /*<<< orphan*/  aclcheckAggregate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getTypeInputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static void
InitializeStypeBox(FunctionCallInfo fcinfo, StypeBox *box, HeapTuple aggTuple, Oid
				   transtype)
{
	Datum textInitVal;
	Form_pg_aggregate aggform = (Form_pg_aggregate) GETSTRUCT(aggTuple);
	Oid userId = GetUserId();

	/* First we make ACL_EXECUTE checks as would be done in nodeAgg.c */
	aclcheckAggregate(OBJECT_AGGREGATE, userId, aggform->aggfnoid);
	aclcheckAggregate(OBJECT_FUNCTION, userId, aggform->aggfinalfn);
	aclcheckAggregate(OBJECT_FUNCTION, userId, aggform->aggtransfn);
	aclcheckAggregate(OBJECT_FUNCTION, userId, aggform->aggdeserialfn);
	aclcheckAggregate(OBJECT_FUNCTION, userId, aggform->aggserialfn);
	aclcheckAggregate(OBJECT_FUNCTION, userId, aggform->aggcombinefn);

	textInitVal = SysCacheGetAttr(AGGFNOID, aggTuple,
								  Anum_pg_aggregate_agginitval,
								  &box->valueNull);
	box->transtype = transtype;
	box->valueInit = !box->valueNull;
	if (box->valueNull)
	{
		box->value = (Datum) 0;
	}
	else
	{
		Oid typinput,
			typioparam;
		char *strInitVal;

		MemoryContext aggregateContext;
		MemoryContext oldContext;
		if (!AggCheckCallContext(fcinfo, &aggregateContext))
		{
			elog(ERROR, "InitializeStypeBox called from non aggregate context");
		}
		oldContext = MemoryContextSwitchTo(aggregateContext);

		getTypeInputInfo(transtype, &typinput, &typioparam);
		strInitVal = TextDatumGetCString(textInitVal);
		box->value = OidInputFunctionCall(typinput, strInitVal,
										  typioparam, -1);
		pfree(strInitVal);

		MemoryContextSwitchTo(oldContext);
	}
}