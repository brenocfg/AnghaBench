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
typedef  int /*<<< orphan*/  instr_time ;
typedef  int /*<<< orphan*/  QueryEnvironment ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  PlannedStmt ;
typedef  int /*<<< orphan*/  ParamListInfo ;
typedef  int /*<<< orphan*/  IntoClause ;
typedef  int /*<<< orphan*/  ExplainState ;

/* Variables and functions */
 int /*<<< orphan*/  ExplainOnePlan (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExplainOneQuery_hook (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INSTR_TIME_SET_CURRENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SUBTRACT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pg_plan_query (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ExplainOneQuery(Query *query, int cursorOptions,
				IntoClause *into, ExplainState *es,
				const char *queryString, ParamListInfo params,
				QueryEnvironment *queryEnv)
{
	/* if an advisor plugin is present, let it manage things */
	if (ExplainOneQuery_hook)
	{
		(*ExplainOneQuery_hook) (query, cursorOptions, into, es,
								 queryString, params, queryEnv);
	}
	else
	{
		PlannedStmt *plan;
		instr_time	planstart,
					planduration;

		INSTR_TIME_SET_CURRENT(planstart);

		/* plan the query */
		plan = pg_plan_query(query, cursorOptions, params);

		INSTR_TIME_SET_CURRENT(planduration);
		INSTR_TIME_SUBTRACT(planduration, planstart);

		/* run it (if needed) and produce output */
		ExplainOnePlan(plan, into, es, queryString, params, queryEnv,
					   &planduration);
	}
}