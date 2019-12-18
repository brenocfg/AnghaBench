#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_7__ {TYPE_1__ ps; } ;
struct TYPE_8__ {int /*<<< orphan*/ * methods; TYPE_2__ ss; } ;
struct TYPE_9__ {TYPE_3__ customScanState; int /*<<< orphan*/  distributedPlan; int /*<<< orphan*/  executorType; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  CustomScan ;
typedef  TYPE_4__ CitusScanState ;

/* Variables and functions */
 int /*<<< orphan*/  AdaptiveExecutorCustomExecMethods ; 
 int /*<<< orphan*/  GetDistributedPlan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MULTI_EXECUTOR_ADAPTIVE ; 
 int /*<<< orphan*/  T_CustomScanState ; 
 TYPE_4__* palloc0 (int) ; 

__attribute__((used)) static Node *
AdaptiveExecutorCreateScan(CustomScan *scan)
{
	CitusScanState *scanState = palloc0(sizeof(CitusScanState));

	scanState->executorType = MULTI_EXECUTOR_ADAPTIVE;
	scanState->customScanState.ss.ps.type = T_CustomScanState;
	scanState->distributedPlan = GetDistributedPlan(scan);

	scanState->customScanState.methods = &AdaptiveExecutorCustomExecMethods;

	return (Node *) scanState;
}