#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* jointree; scalar_t__ setOperations; } ;
struct TYPE_12__ {scalar_t__ quals; } ;
typedef  int /*<<< orphan*/  RecursivePlanningContext ;
typedef  TYPE_2__ Query ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  DeferredErrorMessage ;

/* Variables and functions */
 int /*<<< orphan*/  RecursivelyPlanAllSubqueries (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RecursivelyPlanCTEs (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RecursivelyPlanNonColocatedSubqueries (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RecursivelyPlanSetOperations (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RecursivelyPlanSubqueryWalker ; 
 scalar_t__ ShouldRecursivelyPlanAllSubqueriesInWhere (TYPE_2__*) ; 
 scalar_t__ ShouldRecursivelyPlanNonColocatedSubqueries (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ShouldRecursivelyPlanSetOperation (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ SubqueryPushdown ; 
 int /*<<< orphan*/  WrapFunctionsInSubqueries (TYPE_2__*) ; 
 int /*<<< orphan*/  query_tree_walker (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DeferredErrorMessage *
RecursivelyPlanSubqueriesAndCTEs(Query *query, RecursivePlanningContext *context)
{
	DeferredErrorMessage *error = NULL;

	error = RecursivelyPlanCTEs(query, context);
	if (error != NULL)
	{
		return error;
	}

	if (SubqueryPushdown)
	{
		/*
		 * When the subquery_pushdown flag is enabled we make some hacks
		 * to push down subqueries with LIMIT. Recursive planning would
		 * valiantly do the right thing and try to recursively plan the
		 * inner subqueries, but we don't really want it to because those
		 * subqueries might not be supported and would be much slower.
		 *
		 * Instead, we skip recursive planning altogether when
		 * subquery_pushdown is enabled.
		 */
		return NULL;
	}

	/* make sure function calls in joins are executed in the coordinator */
	WrapFunctionsInSubqueries(query);

	/* descend into subqueries */
	query_tree_walker(query, RecursivelyPlanSubqueryWalker, context, 0);

	/*
	 * At this point, all CTEs, leaf subqueries containing local tables and
	 * non-pushdownable subqueries have been replaced. We now check for
	 * combinations of subqueries that cannot be pushed down (e.g.
	 * <subquery on reference table> UNION <subquery on distributed table>).
	 *
	 * This code also runs for the top-level query, which allows us to support
	 * top-level set operations.
	 */

	if (ShouldRecursivelyPlanSetOperation(query, context))
	{
		RecursivelyPlanSetOperations(query, (Node *) query->setOperations, context);
	}

	/*
	 * If the FROM clause is recurring (does not contain a distributed table),
	 * then we cannot have any distributed tables appearing in subqueries in
	 * the WHERE clause.
	 */
	if (ShouldRecursivelyPlanAllSubqueriesInWhere(query))
	{
		/* replace all subqueries in the WHERE clause */
		RecursivelyPlanAllSubqueries((Node *) query->jointree->quals, context);
	}

	/*
	 * If the query doesn't have distribution key equality,
	 * recursively plan some of its subqueries.
	 */
	if (ShouldRecursivelyPlanNonColocatedSubqueries(query, context))
	{
		RecursivelyPlanNonColocatedSubqueries(query, context);
	}

	return NULL;
}