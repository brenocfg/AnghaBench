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
struct ExplainState {int indent; int /*<<< orphan*/  str; } ;
struct TYPE_5__ {TYPE_1__* distributedPlan; } ;
struct TYPE_4__ {scalar_t__ subPlanList; int /*<<< orphan*/  workerJob; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ DistributedPlan ;
typedef  int /*<<< orphan*/  CustomScanState ;
typedef  TYPE_2__ CitusScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExplainCloseGroup (char*,char*,int,struct ExplainState*) ; 
 int /*<<< orphan*/  ExplainDistributedQueries ; 
 int /*<<< orphan*/  ExplainJob (int /*<<< orphan*/ ,struct ExplainState*) ; 
 int /*<<< orphan*/  ExplainOpenGroup (char*,char*,int,struct ExplainState*) ; 
 int /*<<< orphan*/  ExplainSubPlans (TYPE_1__*,struct ExplainState*) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  appendStringInfoSpaces (int /*<<< orphan*/ ,int) ; 

void
CitusExplainScan(CustomScanState *node, List *ancestors, struct ExplainState *es)
{
	CitusScanState *scanState = (CitusScanState *) node;
	DistributedPlan *distributedPlan = scanState->distributedPlan;

	if (!ExplainDistributedQueries)
	{
		appendStringInfoSpaces(es->str, es->indent * 2);
		appendStringInfo(es->str, "explain statements for distributed queries ");
		appendStringInfo(es->str, "are not enabled\n");
		return;
	}

	ExplainOpenGroup("Distributed Query", "Distributed Query", true, es);

	if (distributedPlan->subPlanList != NIL)
	{
		ExplainSubPlans(distributedPlan, es);
	}

	ExplainJob(distributedPlan->workerJob, es);

	ExplainCloseGroup("Distributed Query", "Distributed Query", true, es);
}