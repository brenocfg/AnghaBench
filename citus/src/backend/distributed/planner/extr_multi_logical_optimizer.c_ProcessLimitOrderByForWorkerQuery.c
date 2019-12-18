#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  nextSortGroupRefIndex; int /*<<< orphan*/  workerSortClauseList; int /*<<< orphan*/  workerLimitCount; } ;
struct TYPE_5__ {int /*<<< orphan*/  targetEntryList; int /*<<< orphan*/  targetProjectionNumber; } ;
typedef  TYPE_1__ QueryTargetList ;
typedef  TYPE_2__ QueryOrderByLimit ;
typedef  int /*<<< orphan*/  OrderByLimitReference ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * GenerateNewTargetEntriesForSortClauses (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  WorkerLimitCount (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WorkerSortClauseList (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ProcessLimitOrderByForWorkerQuery(OrderByLimitReference orderByLimitReference,
								  Node *originalLimitCount, Node *limitOffset,
								  List *sortClauseList, List *groupClauseList,
								  List *originalTargetList,
								  QueryOrderByLimit *queryOrderByLimit,
								  QueryTargetList *queryTargetList)
{
	List *newTargetEntryListForSortClauses = NIL;

	queryOrderByLimit->workerLimitCount =
		WorkerLimitCount(originalLimitCount, limitOffset, orderByLimitReference);

	queryOrderByLimit->workerSortClauseList =
		WorkerSortClauseList(originalLimitCount,
							 groupClauseList,
							 sortClauseList,
							 orderByLimitReference);

	/*
	 * TODO: Do we really need to add the target entries if we're not pushing
	 * down ORDER BY?
	 */
	newTargetEntryListForSortClauses =
		GenerateNewTargetEntriesForSortClauses(originalTargetList,
											   queryOrderByLimit->workerSortClauseList,
											   &(queryTargetList->targetProjectionNumber),
											   queryOrderByLimit->nextSortGroupRefIndex);

	queryTargetList->targetEntryList =
		list_concat(queryTargetList->targetEntryList, newTargetEntryListForSortClauses);
}