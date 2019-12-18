#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  eoh_context; } ;
struct TYPE_10__ {int isnull; } ;
struct TYPE_9__ {int valueNull; int /*<<< orphan*/  value; int /*<<< orphan*/  transtypeLen; int /*<<< orphan*/  transtypeByVal; } ;
typedef  TYPE_1__ StypeBox ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__* FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AggCheckCallContext (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ CurrentMemoryContext ; 
 TYPE_7__* DatumGetEOHP (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumIsReadWriteExpandedObject (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteExpandedObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCallInvoke (TYPE_2__*) ; 
 scalar_t__ MemoryContextGetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 

__attribute__((used)) static void
HandleTransition(StypeBox *box, FunctionCallInfo fcinfo, FunctionCallInfo innerFcinfo)
{
	Datum newVal = FunctionCallInvoke(innerFcinfo);
	bool newValIsNull = innerFcinfo->isnull;

	if (!box->transtypeByVal &&
		DatumGetPointer(newVal) != DatumGetPointer(box->value))
	{
		if (!newValIsNull)
		{
			MemoryContext aggregateContext;
			MemoryContext oldContext;

			if (!AggCheckCallContext(fcinfo, &aggregateContext))
			{
				elog(ERROR,
					 "HandleTransition called from non aggregate context");
			}

			oldContext = MemoryContextSwitchTo(aggregateContext);
			if (!(DatumIsReadWriteExpandedObject(newVal,
												 false, box->transtypeLen) &&
				  MemoryContextGetParent(DatumGetEOHP(newVal)->eoh_context) ==
				  CurrentMemoryContext))
			{
				newVal = datumCopy(newVal, box->transtypeByVal, box->transtypeLen);
			}
			MemoryContextSwitchTo(oldContext);
		}

		if (!box->valueNull)
		{
			if (DatumIsReadWriteExpandedObject(box->value,
											   false, box->transtypeLen))
			{
				DeleteExpandedObject(box->value);
			}
			else
			{
				pfree(DatumGetPointer(box->value));
			}
		}
	}

	box->value = newVal;
	box->valueNull = newValIsNull;
}