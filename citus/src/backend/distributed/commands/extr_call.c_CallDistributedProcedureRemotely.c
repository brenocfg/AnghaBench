#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* funcexpr; } ;
struct TYPE_10__ {int /*<<< orphan*/  isDistributed; } ;
struct TYPE_9__ {int /*<<< orphan*/  funcid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ FuncExpr ;
typedef  TYPE_2__ DistObjectCacheEntry ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  TYPE_3__ CallStmt ;

/* Variables and functions */
 int CallFuncExprRemotely (TYPE_3__*,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* LookupDistObjectCacheEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcedureRelationId ; 

bool
CallDistributedProcedureRemotely(CallStmt *callStmt, DestReceiver *dest)
{
	DistObjectCacheEntry *procedure = NULL;
	FuncExpr *funcExpr = callStmt->funcexpr;
	Oid functionId = funcExpr->funcid;

	procedure = LookupDistObjectCacheEntry(ProcedureRelationId, functionId, 0);
	if (procedure == NULL || !procedure->isDistributed)
	{
		return false;
	}

	return CallFuncExprRemotely(callStmt, procedure, funcExpr, dest);
}