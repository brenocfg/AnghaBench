#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int groupedByDisjointPartitionColumn; int hasDistinctOn; int groupClauseIsEmpty; int sortClauseIsEmpty; int /*<<< orphan*/  hasOrderByAggregate; int /*<<< orphan*/  canApproximate; } ;
typedef  TYPE_1__ OrderByLimitReference ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  CanPushDownLimitApproximate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HasOrderByAggregate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 

__attribute__((used)) static OrderByLimitReference
BuildOrderByLimitReference(bool hasDistinctOn, bool groupedByDisjointPartitionColumn,
						   List *groupClause, List *sortClauseList, List *targetList)
{
	OrderByLimitReference limitOrderByReference;

	limitOrderByReference.groupedByDisjointPartitionColumn =
		groupedByDisjointPartitionColumn;
	limitOrderByReference.hasDistinctOn = hasDistinctOn;
	limitOrderByReference.groupClauseIsEmpty = (groupClause == NIL);
	limitOrderByReference.sortClauseIsEmpty = (sortClauseList == NIL);
	limitOrderByReference.canApproximate =
		CanPushDownLimitApproximate(sortClauseList, targetList);
	limitOrderByReference.hasOrderByAggregate =
		HasOrderByAggregate(sortClauseList, targetList);

	return limitOrderByReference;
}