#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_11__ {TYPE_1__* planTree; } ;
struct TYPE_10__ {int total_cost; } ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  PlannerRestrictionContext ;
typedef  TYPE_2__ PlannedStmt ;
typedef  int /*<<< orphan*/  ParamListInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  DistributedPlan ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustPartitioningForDistributedPlanning (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Assert (scalar_t__) ; 
 int /*<<< orphan*/  AssignRTEIdentities (int /*<<< orphan*/ *) ; 
 int CURSOR_OPT_FORCE_DISTRIBUTED ; 
 scalar_t__ CitusHasBeenLoaded () ; 
 int /*<<< orphan*/ * CreateAndPushPlannerRestrictionContext () ; 
 TYPE_2__* CreateDistributedPlannedStmt (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * ExtractRangeTableEntryList (int /*<<< orphan*/ *) ; 
 int FLT_MAX ; 
 TYPE_2__* FastPathPlanner (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FastPathRouterQuery (int /*<<< orphan*/ *) ; 
 TYPE_2__* FinalizePlan (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ InsertSelectIntoLocalTable (int /*<<< orphan*/ *) ; 
 scalar_t__ IsLocalReferenceTableJoin (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ListContainsDistributedTableRTE (int /*<<< orphan*/ *) ; 
 scalar_t__ NeedsDistributedPlanning (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NextPlanId ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  PopPlannerRestrictionContext () ; 
 int /*<<< orphan*/  ReplaceTableVisibleFunction (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TryToDelegateFunctionCall (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  UpdateReferenceTablesWithShard (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_2__* standard_planner (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

PlannedStmt *
distributed_planner(Query *parse, int cursorOptions, ParamListInfo boundParams)
{
	PlannedStmt *result = NULL;
	bool needsDistributedPlanning = false;
	Query *originalQuery = NULL;
	PlannerRestrictionContext *plannerRestrictionContext = NULL;
	bool setPartitionedTablesInherited = false;
	List *rangeTableList = ExtractRangeTableEntryList(parse);

	if (cursorOptions & CURSOR_OPT_FORCE_DISTRIBUTED)
	{
		/* this cursor flag could only be set when Citus has been loaded */
		Assert(CitusHasBeenLoaded());

		needsDistributedPlanning = true;
	}
	else if (CitusHasBeenLoaded())
	{
		if (IsLocalReferenceTableJoin(parse, rangeTableList))
		{
			/*
			 * For joins between reference tables and local tables, we replace
			 * reference table names with shard tables names in the query, so
			 * we can use the standard_planner for planning it locally.
			 */
			needsDistributedPlanning = false;
			UpdateReferenceTablesWithShard((Node *) parse, NULL);
		}
		else
		{
			needsDistributedPlanning = ListContainsDistributedTableRTE(rangeTableList);
		}
	}

	if (needsDistributedPlanning)
	{
		/*
		 * Inserting into a local table needs to go through the regular postgres
		 * planner/executor, but the SELECT needs to go through Citus. We currently
		 * don't have a way of doing both things and therefore error out, but do
		 * have a handy tip for users.
		 */
		if (InsertSelectIntoLocalTable(parse))
		{
			ereport(ERROR, (errmsg("cannot INSERT rows from a distributed query into a "
								   "local table"),
							errhint("Consider using CREATE TEMPORARY TABLE tmp AS "
									"SELECT ... and inserting from the temporary "
									"table.")));
		}

		/*
		 * standard_planner scribbles on it's input, but for deparsing we need the
		 * unmodified form. Note that we keep RTE_RELATIONs with their identities
		 * set, which doesn't break our goals, but, prevents us keeping an extra copy
		 * of the query tree. Note that we copy the query tree once we're sure it's a
		 * distributed query.
		 */
		AssignRTEIdentities(rangeTableList);
		originalQuery = copyObject(parse);

		setPartitionedTablesInherited = false;
		AdjustPartitioningForDistributedPlanning(rangeTableList,
												 setPartitionedTablesInherited);
	}

	/*
	 * Make sure that we hide shard names on the Citus MX worker nodes. See comments in
	 * ReplaceTableVisibleFunction() for the details.
	 */
	ReplaceTableVisibleFunction((Node *) parse);

	/* create a restriction context and put it at the end if context list */
	plannerRestrictionContext = CreateAndPushPlannerRestrictionContext();

	PG_TRY();
	{
		/*
		 * For trivial queries, we're skipping the standard_planner() in
		 * order to eliminate its overhead.
		 *
		 * Otherwise, call into standard planner. This is required because the Citus
		 * planner relies on both the restriction information per table and parse tree
		 * transformations made by postgres' planner.
		 */

		if (needsDistributedPlanning && FastPathRouterQuery(originalQuery))
		{
			result = FastPathPlanner(originalQuery, parse, boundParams);
		}
		else
		{
			result = standard_planner(parse, cursorOptions, boundParams);
		}

		if (needsDistributedPlanning)
		{
			uint64 planId = NextPlanId++;

			result = CreateDistributedPlannedStmt(planId, result, originalQuery, parse,
												  boundParams, plannerRestrictionContext);

			setPartitionedTablesInherited = true;
			AdjustPartitioningForDistributedPlanning(rangeTableList,
													 setPartitionedTablesInherited);
		}
		else
		{
			bool hasExternParam = false;
			DistributedPlan *delegatePlan = TryToDelegateFunctionCall(parse,
																	  &hasExternParam);
			if (delegatePlan != NULL)
			{
				result = FinalizePlan(result, delegatePlan);
			}
			else if (hasExternParam)
			{
				/*
				 * As in CreateDistributedPlannedStmt, try dissuade planner when planning
				 * potentially failed due to unresolved prepared statement parameters.
				 */
				result->planTree->total_cost = FLT_MAX / 100000000;
			}
		}
	}
	PG_CATCH();
	{
		PopPlannerRestrictionContext();
		PG_RE_THROW();
	}
	PG_END_TRY();

	/* remove the context from the context list */
	PopPlannerRestrictionContext();

	/*
	 * In some cases, for example; parameterized SQL functions, we may miss that
	 * there is a need for distributed planning. Such cases only become clear after
	 * standart_planner performs some modifications on parse tree. In such cases
	 * we will simply error out.
	 */
	if (!needsDistributedPlanning && NeedsDistributedPlanning(parse))
	{
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("cannot perform distributed planning on this "
							   "query because parameterized queries for SQL "
							   "functions referencing distributed tables are "
							   "not supported"),
						errhint("Consider using PL/pgSQL functions instead.")));
	}

	return result;
}