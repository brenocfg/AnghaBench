#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ jointree; scalar_t__ groupingSets; scalar_t__ hasForUpdate; scalar_t__ cteList; scalar_t__ hasRecursive; scalar_t__ setOperations; scalar_t__ hasWindowFuncs; scalar_t__ hasSubLinks; } ;
typedef  int /*<<< orphan*/ * StringInfo ;
typedef  TYPE_1__ Query ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  DeferredErrorMessage ;

/* Variables and functions */
 int /*<<< orphan*/ * DeferredError (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int ErrorHintRequired (char const*,TYPE_1__*) ; 
 int HasComplexRangeTableType (TYPE_1__*) ; 
 int HasTablesample (TYPE_1__*) ; 
 int HasUnsupportedJoinWalker (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SafeToPushdownWindowFunction (TYPE_1__*,int /*<<< orphan*/ **) ; 
 scalar_t__ TargetListContainsSubquery (TYPE_1__*) ; 

DeferredErrorMessage *
DeferErrorIfQueryNotSupported(Query *queryTree)
{
	char *errorMessage = NULL;
	bool hasTablesample = false;
	bool hasUnsupportedJoin = false;
	bool hasComplexRangeTableType = false;
	bool preconditionsSatisfied = true;
	StringInfo errorInfo = NULL;
	const char *errorHint = NULL;
	const char *joinHint = "Consider joining tables on partition column and have "
						   "equal filter on joining columns.";
	const char *filterHint = "Consider using an equality filter on the distributed "
							 "table's partition column.";

	/*
	 * There could be Sublinks in the target list as well. To produce better
	 * error messages we're checking if that's the case.
	 */
	if (queryTree->hasSubLinks && TargetListContainsSubquery(queryTree))
	{
		preconditionsSatisfied = false;
		errorMessage = "could not run distributed query with subquery outside the "
					   "FROM, WHERE and HAVING clauses";
		errorHint = filterHint;
	}

	if (queryTree->hasWindowFuncs &&
		!SafeToPushdownWindowFunction(queryTree, &errorInfo))
	{
		preconditionsSatisfied = false;
		errorMessage = "could not run distributed query because the window "
					   "function that is used cannot be pushed down";
		errorHint = "Window functions are supported in two ways. Either add "
					"an equality filter on the distributed tables' partition "
					"column or use the window functions with a PARTITION BY "
					"clause containing the distribution column";
	}

	if (queryTree->setOperations)
	{
		preconditionsSatisfied = false;
		errorMessage = "could not run distributed query with UNION, INTERSECT, or "
					   "EXCEPT";
		errorHint = filterHint;
	}

	if (queryTree->hasRecursive)
	{
		preconditionsSatisfied = false;
		errorMessage = "could not run distributed query with RECURSIVE";
		errorHint = filterHint;
	}

	if (queryTree->cteList)
	{
		preconditionsSatisfied = false;
		errorMessage = "could not run distributed query with common table expressions";
		errorHint = filterHint;
	}

	if (queryTree->hasForUpdate)
	{
		preconditionsSatisfied = false;
		errorMessage = "could not run distributed query with FOR UPDATE/SHARE commands";
		errorHint = filterHint;
	}

	if (queryTree->groupingSets)
	{
		preconditionsSatisfied = false;
		errorMessage = "could not run distributed query with GROUPING SETS, CUBE, "
					   "or ROLLUP";
		errorHint = filterHint;
	}

	hasTablesample = HasTablesample(queryTree);
	if (hasTablesample)
	{
		preconditionsSatisfied = false;
		errorMessage = "could not run distributed query which use TABLESAMPLE";
		errorHint = filterHint;
	}

	hasUnsupportedJoin = HasUnsupportedJoinWalker((Node *) queryTree->jointree, NULL);
	if (hasUnsupportedJoin)
	{
		preconditionsSatisfied = false;
		errorMessage = "could not run distributed query with join types other than "
					   "INNER or OUTER JOINS";
		errorHint = joinHint;
	}

	hasComplexRangeTableType = HasComplexRangeTableType(queryTree);
	if (hasComplexRangeTableType)
	{
		preconditionsSatisfied = false;
		errorMessage = "could not run distributed query with complex table expressions";
		errorHint = filterHint;
	}


	/* finally check and error out if not satisfied */
	if (!preconditionsSatisfied)
	{
		bool showHint = ErrorHintRequired(errorHint, queryTree);
		return DeferredError(ERRCODE_FEATURE_NOT_SUPPORTED,
							 errorMessage, NULL,
							 showHint ? errorHint : NULL);
	}

	return NULL;
}