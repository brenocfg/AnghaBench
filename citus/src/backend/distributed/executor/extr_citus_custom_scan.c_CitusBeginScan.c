#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ps; } ;
struct TYPE_6__ {TYPE_1__ ss; } ;
struct TYPE_8__ {TYPE_3__* distributedPlan; TYPE_2__ customScanState; } ;
struct TYPE_7__ {scalar_t__ modLevel; int /*<<< orphan*/ * insertSelectSubquery; } ;
typedef  int /*<<< orphan*/  EState ;
typedef  TYPE_3__ DistributedPlan ;
typedef  int /*<<< orphan*/  CustomScanState ;
typedef  TYPE_4__ CitusScanState ;

/* Variables and functions */
 int /*<<< orphan*/  CitusModifyBeginScan (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ExecInitResultSlot (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MarkCitusInitiatedCoordinatorBackend () ; 
 scalar_t__ ROW_MODIFY_READONLY ; 
 int /*<<< orphan*/  TTSOpsMinimalTuple ; 

__attribute__((used)) static void
CitusBeginScan(CustomScanState *node, EState *estate, int eflags)
{
	CitusScanState *scanState = NULL;
	DistributedPlan *distributedPlan = NULL;

	MarkCitusInitiatedCoordinatorBackend();

	scanState = (CitusScanState *) node;

#if PG_VERSION_NUM >= 120000
	ExecInitResultSlot(&scanState->customScanState.ss.ps, &TTSOpsMinimalTuple);
#endif

	distributedPlan = scanState->distributedPlan;
	if (distributedPlan->modLevel == ROW_MODIFY_READONLY ||
		distributedPlan->insertSelectSubquery != NULL)
	{
		/* no more action required */
		return;
	}

	CitusModifyBeginScan(node, estate, eflags);
}