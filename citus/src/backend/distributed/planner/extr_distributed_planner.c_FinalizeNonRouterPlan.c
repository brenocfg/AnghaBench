#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  rtable; int /*<<< orphan*/  utilityStmt; int /*<<< orphan*/  queryId; } ;
typedef  TYPE_1__ PlannedStmt ;
typedef  int /*<<< orphan*/  DistributedPlan ;
typedef  int /*<<< orphan*/  CustomScan ;

/* Variables and functions */
 TYPE_1__* MasterNodeSelectPlan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PlannedStmt *
FinalizeNonRouterPlan(PlannedStmt *localPlan, DistributedPlan *distributedPlan,
					  CustomScan *customScan)
{
	PlannedStmt *finalPlan = NULL;

	finalPlan = MasterNodeSelectPlan(distributedPlan, customScan);
	finalPlan->queryId = localPlan->queryId;
	finalPlan->utilityStmt = localPlan->utilityStmt;

	/* add original range table list for access permission checks */
	finalPlan->rtable = list_concat(finalPlan->rtable, localPlan->rtable);

	return finalPlan;
}