#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  planningError; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ DistributedPlan ;
typedef  int /*<<< orphan*/  CustomScan ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* GetDistributedPlan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RaiseDeferredError (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *
DelayedErrorCreateScan(CustomScan *scan)
{
	DistributedPlan *distributedPlan = GetDistributedPlan(scan);

	/* raise the deferred error */
	RaiseDeferredError(distributedPlan->planningError, ERROR);

	return NULL;
}