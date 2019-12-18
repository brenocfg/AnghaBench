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
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  AggCheckCallContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 void* MemoryContextAlloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void *
pallocInAggContext(FunctionCallInfo fcinfo, size_t size)
{
	MemoryContext aggregateContext;
	if (!AggCheckCallContext(fcinfo, &aggregateContext))
	{
		elog(ERROR, "Aggregate function called without an aggregate context");
	}
	return MemoryContextAlloc(aggregateContext, size);
}