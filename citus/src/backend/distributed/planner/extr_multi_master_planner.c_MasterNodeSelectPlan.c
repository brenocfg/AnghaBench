#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* workerJob; int /*<<< orphan*/ * masterQuery; } ;
struct TYPE_6__ {TYPE_1__* jobQuery; } ;
struct TYPE_5__ {int /*<<< orphan*/ * targetList; } ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  PlannedStmt ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ Job ;
typedef  TYPE_3__ DistributedPlan ;
typedef  int /*<<< orphan*/  CustomScan ;

/* Variables and functions */
 int /*<<< orphan*/ * BuildSelectStatement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MasterTargetList (int /*<<< orphan*/ *) ; 

PlannedStmt *
MasterNodeSelectPlan(DistributedPlan *distributedPlan, CustomScan *remoteScan)
{
	Query *masterQuery = distributedPlan->masterQuery;
	PlannedStmt *masterSelectPlan = NULL;

	Job *workerJob = distributedPlan->workerJob;
	List *workerTargetList = workerJob->jobQuery->targetList;
	List *masterTargetList = MasterTargetList(workerTargetList);

	masterSelectPlan = BuildSelectStatement(masterQuery, masterTargetList, remoteScan);

	return masterSelectPlan;
}