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
typedef  scalar_t__ uint64 ;
struct TYPE_8__ {scalar_t__ executorType; int /*<<< orphan*/ * tuplestorestate; TYPE_1__* distributedPlan; } ;
struct TYPE_7__ {int /*<<< orphan*/  consttype; int /*<<< orphan*/  constvalue; } ;
struct TYPE_6__ {TYPE_3__* partitionKeyValue; } ;
struct TYPE_5__ {scalar_t__ queryId; TYPE_2__* workerJob; } ;
typedef  scalar_t__ MultiExecutorType ;
typedef  TYPE_2__ Job ;
typedef  int /*<<< orphan*/  CustomScanState ;
typedef  TYPE_3__ Const ;
typedef  TYPE_4__ CitusScanState ;

/* Variables and functions */
 int /*<<< orphan*/  CitusQueryStatsExecutorsEntry (scalar_t__,scalar_t__,char*) ; 
 char* DatumToString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MULTI_EXECUTOR_ADAPTIVE ; 
 int /*<<< orphan*/  tuplestore_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
CitusEndScan(CustomScanState *node)
{
	CitusScanState *scanState = (CitusScanState *) node;
	Job *workerJob = scanState->distributedPlan->workerJob;
	uint64 queryId = scanState->distributedPlan->queryId;
	MultiExecutorType executorType = scanState->executorType;
	Const *partitionKeyConst = NULL;
	char *partitionKeyString = NULL;

	if (workerJob != NULL)
	{
		partitionKeyConst = workerJob->partitionKeyValue;
	}

	/* queryId is not set if pg_stat_statements is not installed */
	if (queryId != 0)
	{
		if (partitionKeyConst != NULL && executorType == MULTI_EXECUTOR_ADAPTIVE)
		{
			partitionKeyString = DatumToString(partitionKeyConst->constvalue,
											   partitionKeyConst->consttype);
		}

		/* queries without partition key are also recorded */
		CitusQueryStatsExecutorsEntry(queryId, executorType, partitionKeyString);
	}

	if (scanState->tuplestorestate)
	{
		tuplestore_end(scanState->tuplestorestate);
		scanState->tuplestorestate = NULL;
	}
}