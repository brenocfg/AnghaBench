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
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ DISABLE_LIMIT_APPROXIMATION ; 
 int HasOrderByAverage (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int HasOrderByComplexExpression (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ LimitClauseRowFetchCount ; 
 int /*<<< orphan*/ * NIL ; 

__attribute__((used)) static bool
CanPushDownLimitApproximate(List *sortClauseList, List *targetList)
{
	bool canApproximate = false;

	/* user hasn't enabled the limit approximation */
	if (LimitClauseRowFetchCount == DISABLE_LIMIT_APPROXIMATION)
	{
		return false;
	}

	if (sortClauseList != NIL)
	{
		bool orderByAverage = HasOrderByAverage(sortClauseList, targetList);
		bool orderByComplex = HasOrderByComplexExpression(sortClauseList, targetList);

		/*
		 * If we don't have any order by average or any complex expressions with
		 * aggregates in them, we can meaningfully approximate.
		 */
		if (!orderByAverage && !orderByComplex)
		{
			canApproximate = true;
		}
	}

	return canApproximate;
}