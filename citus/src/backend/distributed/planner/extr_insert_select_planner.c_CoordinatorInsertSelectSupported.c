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
struct TYPE_11__ {scalar_t__ targetList; } ;
struct TYPE_10__ {scalar_t__ subquery; int /*<<< orphan*/  relid; } ;
typedef  TYPE_1__ RangeTblEntry ;
typedef  TYPE_2__ Query ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  DeferredErrorMessage ;

/* Variables and functions */
 scalar_t__ DISTRIBUTE_BY_APPEND ; 
 int /*<<< orphan*/ * DeferredError (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/ * ErrorIfOnConflictNotSupported (TYPE_2__*) ; 
 TYPE_1__* ExtractResultRelationRTE (TYPE_2__*) ; 
 TYPE_1__* ExtractSelectRangeTableEntry (TYPE_2__*) ; 
 scalar_t__ NeedsDistributedPlanning (TYPE_2__*) ; 
 scalar_t__ PartitionMethod (int /*<<< orphan*/ ) ; 
 scalar_t__ contain_nextval_expression_walker (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static DeferredErrorMessage *
CoordinatorInsertSelectSupported(Query *insertSelectQuery)
{
	RangeTblEntry *insertRte = NULL;
	RangeTblEntry *subqueryRte = NULL;
	Query *subquery = NULL;
	DeferredErrorMessage *deferredError = NULL;

	deferredError = ErrorIfOnConflictNotSupported(insertSelectQuery);
	if (deferredError)
	{
		return deferredError;
	}

	insertRte = ExtractResultRelationRTE(insertSelectQuery);
	if (PartitionMethod(insertRte->relid) == DISTRIBUTE_BY_APPEND)
	{
		return DeferredError(ERRCODE_FEATURE_NOT_SUPPORTED,
							 "INSERT ... SELECT into an append-distributed table is "
							 "not supported", NULL, NULL);
	}

	subqueryRte = ExtractSelectRangeTableEntry(insertSelectQuery);
	subquery = (Query *) subqueryRte->subquery;

	if (NeedsDistributedPlanning(subquery) &&
		contain_nextval_expression_walker((Node *) insertSelectQuery->targetList, NULL))
	{
		return DeferredError(ERRCODE_FEATURE_NOT_SUPPORTED,
							 "INSERT ... SELECT cannot generate sequence values when "
							 "selecting from a distributed table",
							 NULL, NULL);
	}

	return NULL;
}