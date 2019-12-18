#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_21__ {int /*<<< orphan*/  tuplestorestate; } ;
struct TYPE_20__ {int /*<<< orphan*/  es_param_list_info; } ;
struct TYPE_19__ {scalar_t__ commandType; } ;
struct TYPE_18__ {TYPE_1__* estate; } ;
struct TYPE_17__ {int /*<<< orphan*/  es_processed; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  int /*<<< orphan*/  QueryEnvironment ;
typedef  TYPE_2__ QueryDesc ;
typedef  TYPE_3__ PlannedStmt ;
typedef  int /*<<< orphan*/  ParamListInfo ;
typedef  TYPE_4__ EState ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  TYPE_5__ CitusScanState ;

/* Variables and functions */
 scalar_t__ CMD_SELECT ; 
 int /*<<< orphan*/ * CreateDestReceiver (int /*<<< orphan*/ ) ; 
 TYPE_2__* CreateQueryDesc (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DestTuplestore ; 
 int /*<<< orphan*/  ExecutorEnd (TYPE_2__*) ; 
 int /*<<< orphan*/  ExecutorFinish (TYPE_2__*) ; 
 int /*<<< orphan*/  ExecutorRun (TYPE_2__*,int /*<<< orphan*/ ,long,int) ; 
 int /*<<< orphan*/  ExecutorStart (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  FreeQueryDesc (TYPE_2__*) ; 
 int /*<<< orphan*/  GetActiveSnapshot () ; 
 int /*<<< orphan*/  InvalidSnapshot ; 
 TYPE_4__* ScanStateGetExecutorState (TYPE_5__*) ; 
 int /*<<< orphan*/  SetTuplestoreDestReceiverParams (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * create_queryEnv () ; 

__attribute__((used)) static uint64
ExecuteLocalTaskPlan(CitusScanState *scanState, PlannedStmt *taskPlan, char *queryString)
{
	EState *executorState = ScanStateGetExecutorState(scanState);
	ParamListInfo paramListInfo = executorState->es_param_list_info;
	DestReceiver *tupleStoreDestReceiever = CreateDestReceiver(DestTuplestore);
	ScanDirection scanDirection = ForwardScanDirection;
	QueryEnvironment *queryEnv = create_queryEnv();
	QueryDesc *queryDesc = NULL;
	int eflags = 0;
	uint64 totalRowsProcessed = 0;

	/*
	 * Use the tupleStore provided by the scanState because it is shared accross
	 * the other task executions and the adaptive executor.
	 */
	SetTuplestoreDestReceiverParams(tupleStoreDestReceiever,
									scanState->tuplestorestate,
									CurrentMemoryContext, false);

	/* Create a QueryDesc for the query */
	queryDesc = CreateQueryDesc(taskPlan, queryString,
								GetActiveSnapshot(), InvalidSnapshot,
								tupleStoreDestReceiever, paramListInfo,
								queryEnv, 0);

	ExecutorStart(queryDesc, eflags);
	ExecutorRun(queryDesc, scanDirection, 0L, true);

	/*
	 * We'll set the executorState->es_processed later, for now only remember
	 * the count.
	 */
	if (taskPlan->commandType != CMD_SELECT)
	{
		totalRowsProcessed = queryDesc->estate->es_processed;
	}

	ExecutorFinish(queryDesc);
	ExecutorEnd(queryDesc);

	FreeQueryDesc(queryDesc);

	return totalRowsProcessed;
}