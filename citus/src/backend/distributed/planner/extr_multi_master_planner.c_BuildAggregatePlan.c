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
struct TYPE_9__ {scalar_t__ plan_rows; scalar_t__ total_cost; scalar_t__ startup_cost; } ;
struct TYPE_11__ {TYPE_1__ plan; } ;
struct TYPE_10__ {int /*<<< orphan*/  havingQual; int /*<<< orphan*/ * targetList; int /*<<< orphan*/ * groupClause; scalar_t__ hasAggs; } ;
typedef  TYPE_2__ Query ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  AggStrategy ;
typedef  int /*<<< orphan*/  AggClauseCosts ;
typedef  TYPE_3__ Agg ;

/* Variables and functions */
 int /*<<< orphan*/  AGGSPLIT_SIMPLE ; 
 int /*<<< orphan*/  AGG_HASHED ; 
 int /*<<< orphan*/  AGG_PLAIN ; 
 int /*<<< orphan*/  AGG_SORTED ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int HasDistinctAggregate (TYPE_2__*) ; 
 int /*<<< orphan*/ * SS_process_sublinks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * SS_replace_correlation_vars (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ UseGroupAggregateWithHLL (TYPE_2__*) ; 
 int /*<<< orphan*/  enable_hashagg ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errhint (char*,char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  get_agg_clause_costs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int grouping_is_hashable (int /*<<< orphan*/ *) ; 
 int grouping_is_sortable (int /*<<< orphan*/ *) ; 
 scalar_t__ list_length (int /*<<< orphan*/ *) ; 
 TYPE_3__* makeAggNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ make_sort_from_sortclauses (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Agg *
BuildAggregatePlan(PlannerInfo *root, Query *masterQuery, Plan *subPlan)
{
	/* assert that we need to build an aggregate plan */
	Assert(masterQuery->hasAggs || masterQuery->groupClause);
	AggClauseCosts aggregateCosts;
	AggStrategy aggregateStrategy = AGG_PLAIN;
	List *groupColumnList = masterQuery->groupClause;
	List *aggregateTargetList = masterQuery->targetList;

	/*
	 * Replaces SubLink nodes with SubPlan nodes in the having section of the
	 * query. (and creates the subplans in root->subplans)
	 *
	 * Would be nice if we could use masterQuery->hasSubLinks to only call
	 * these when that is true. However, for some reason hasSubLinks is false
	 * even when there are SubLinks.
	 */
	Node *havingQual = SS_process_sublinks(root, masterQuery->havingQual, true);

	/*
	 * Right now this is not really needed, since we don't support correlated
	 * subqueries anyway. Once we do calling this is critical to do right after
	 * calling SS_process_sublinks, according to the postgres function comment.
	 */
	havingQual = SS_replace_correlation_vars(root, havingQual);


	/* estimate aggregate execution costs */
	memset(&aggregateCosts, 0, sizeof(AggClauseCosts));
	get_agg_clause_costs(root, (Node *) aggregateTargetList, AGGSPLIT_SIMPLE,
						 &aggregateCosts);

	get_agg_clause_costs(root, (Node *) havingQual, AGGSPLIT_SIMPLE, &aggregateCosts);


	/* if we have grouping, then initialize appropriate information */
	if (list_length(groupColumnList) > 0)
	{
		bool groupingIsHashable = grouping_is_hashable(groupColumnList);
		bool groupingIsSortable = grouping_is_sortable(groupColumnList);
		bool hasDistinctAggregate = HasDistinctAggregate(masterQuery);

		if (!groupingIsHashable && !groupingIsSortable)
		{
			ereport(ERROR, (errmsg("grouped column list cannot be hashed or sorted")));
		}

		/*
		 * Postgres hash aggregate strategy does not support distinct aggregates
		 * in group and order by with aggregate operations.
		 * see nodeAgg.c:build_pertrans_for_aggref(). In that case we use
		 * sorted agg strategy, otherwise we use hash strategy.
		 *
		 * If the master query contains hll aggregate functions and the client set
		 * hll.force_groupagg to on, then we choose to use group aggregation.
		 */
		if (!enable_hashagg || !groupingIsHashable || hasDistinctAggregate ||
			UseGroupAggregateWithHLL(masterQuery))
		{
			char *messageHint = NULL;
			if (!enable_hashagg && groupingIsHashable)
			{
				messageHint = "Consider setting enable_hashagg to on.";
			}

			if (!groupingIsSortable)
			{
				ereport(ERROR, (errmsg("grouped column list must cannot be sorted"),
								errdetail("Having a distinct aggregate requires "
										  "grouped column list to be sortable."),
								messageHint ? errhint("%s", messageHint) : 0));
			}

			aggregateStrategy = AGG_SORTED;
			subPlan = (Plan *) make_sort_from_sortclauses(groupColumnList, subPlan);
		}
		else
		{
			aggregateStrategy = AGG_HASHED;
		}
	}

	/* finally create the plan */
	Agg *aggregatePlan = makeAggNode(groupColumnList, (List *) havingQual,
									 aggregateStrategy, aggregateTargetList, subPlan);

	/* just for reproducible costs between different PostgreSQL versions */
	aggregatePlan->plan.startup_cost = 0;
	aggregatePlan->plan.total_cost = 0;
	aggregatePlan->plan.plan_rows = 0;

	return aggregatePlan;
}