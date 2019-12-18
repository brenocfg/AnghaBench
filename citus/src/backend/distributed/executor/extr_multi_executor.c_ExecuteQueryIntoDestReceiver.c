#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  PlannedStmt ;
typedef  int /*<<< orphan*/  ParamListInfo ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int CURSOR_OPT_PARALLEL_OK ; 
 int /*<<< orphan*/  ExecutePlanIntoDestReceiver (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pg_plan_query (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void
ExecuteQueryIntoDestReceiver(Query *query, ParamListInfo params, DestReceiver *dest)
{
	PlannedStmt *queryPlan = NULL;
	int cursorOptions = 0;

	cursorOptions = CURSOR_OPT_PARALLEL_OK;

	/* plan the subquery, this may be another distributed query */
	queryPlan = pg_plan_query(query, cursorOptions, params);

	ExecutePlanIntoDestReceiver(queryPlan, params, dest);
}