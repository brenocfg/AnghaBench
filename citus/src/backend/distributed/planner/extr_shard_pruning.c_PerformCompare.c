#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* flinfo; scalar_t__ isnull; } ;
struct TYPE_5__ {int /*<<< orphan*/  fn_oid; } ;
typedef  TYPE_2__* FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCallInvoke (TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
PerformCompare(FunctionCallInfo compareFunctionCall)
{
	Datum result = FunctionCallInvoke(compareFunctionCall);

	if (compareFunctionCall->isnull)
	{
		elog(ERROR, "function %u returned NULL", compareFunctionCall->flinfo->fn_oid);
	}

	return DatumGetInt32(result);
}