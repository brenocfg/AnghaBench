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
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_11__ {scalar_t__ mydest; int /*<<< orphan*/  (* rShutdown ) (TYPE_3__*) ;int /*<<< orphan*/  (* rStartup ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  es_lastoid; scalar_t__ es_processed; } ;
struct TYPE_9__ {int /*<<< orphan*/  tupDesc; TYPE_3__* dest; TYPE_2__* estate; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  TYPE_1__ QueryDesc ;
typedef  TYPE_2__ EState ;
typedef  TYPE_3__ DestReceiver ;

/* Variables and functions */
 scalar_t__ AlterTableConstraintCheck (TYPE_1__*) ; 
 int /*<<< orphan*/  CMD_SELECT ; 
 scalar_t__ DestSPI ; 
 int FunctionCallLevel ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  standard_ExecutorRun (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

void
CitusExecutorRun(QueryDesc *queryDesc,
				 ScanDirection direction, uint64 count, bool execute_once)
{
	DestReceiver *dest = queryDesc->dest;
	int originalLevel = FunctionCallLevel;

	if (dest->mydest == DestSPI)
	{
		/*
		 * If the query runs via SPI, we assume we're in a function call
		 * and we should treat statements as part of a bigger transaction.
		 * We reset this counter to 0 in the abort handler.
		 */
		FunctionCallLevel++;
	}

	/*
	 * Disable execution of ALTER TABLE constraint validation queries. These
	 * constraints will be validated in worker nodes, so running these queries
	 * from the coordinator would be redundant.
	 *
	 * For example, ALTER TABLE ... ATTACH PARTITION checks that the new
	 * partition doesn't violate constraints of the parent table, which
	 * might involve running some SELECT queries.
	 *
	 * Ideally we'd completely skip these checks in the coordinator, but we don't
	 * have any means to tell postgres to skip the checks. So the best we can do is
	 * to not execute the queries and return an empty result set, as if this table has
	 * no rows, so no constraints will be violated.
	 */
	if (AlterTableConstraintCheck(queryDesc))
	{
		EState *estate = queryDesc->estate;

		estate->es_processed = 0;
#if PG_VERSION_NUM < 120000
		estate->es_lastoid = InvalidOid;
#endif

		/* start and shutdown tuple receiver to simulate empty result */
		dest->rStartup(queryDesc->dest, CMD_SELECT, queryDesc->tupDesc);
		dest->rShutdown(dest);
	}
	else
	{
		standard_ExecutorRun(queryDesc, direction, count, execute_once);
	}

	if (dest->mydest == DestSPI)
	{
		/*
		 * Restore the original value. It is not sufficient to decrease
		 * the value because exceptions might cause us to go back a few
		 * levels at once.
		 */
		FunctionCallLevel = originalLevel;
	}
}