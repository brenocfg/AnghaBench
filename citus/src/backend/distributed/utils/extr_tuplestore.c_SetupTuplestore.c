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
typedef  int /*<<< orphan*/  Tuplestorestate ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_5__ {int /*<<< orphan*/  setDesc; int /*<<< orphan*/ * setResult; int /*<<< orphan*/  returnMode; TYPE_1__* econtext; } ;
struct TYPE_4__ {int /*<<< orphan*/  ecxt_per_query_memory; } ;
typedef  TYPE_2__ ReturnSetInfo ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;

/* Variables and functions */
 TYPE_2__* CheckTuplestoreReturn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SFRM_Materialize ; 
 int /*<<< orphan*/ * tuplestore_begin_heap (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_mem ; 

Tuplestorestate *
SetupTuplestore(FunctionCallInfo fcinfo, TupleDesc *tupleDescriptor)
{
	ReturnSetInfo *resultSet = CheckTuplestoreReturn(fcinfo, tupleDescriptor);
	MemoryContext perQueryContext = resultSet->econtext->ecxt_per_query_memory;

	MemoryContext oldContext = MemoryContextSwitchTo(perQueryContext);
	Tuplestorestate *tupstore = tuplestore_begin_heap(true, false, work_mem);
	resultSet->returnMode = SFRM_Materialize;
	resultSet->setResult = tupstore;
	resultSet->setDesc = *tupleDescriptor;
	MemoryContextSwitchTo(oldContext);

	return tupstore;
}