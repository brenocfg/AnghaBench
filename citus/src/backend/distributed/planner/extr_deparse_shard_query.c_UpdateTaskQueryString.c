#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  queryString; int /*<<< orphan*/ * relationShardList; int /*<<< orphan*/  anchorShardId; int /*<<< orphan*/ * rowValuesLists; } ;
typedef  TYPE_1__ Task ;
struct TYPE_16__ {scalar_t__ commandType; } ;
struct TYPE_15__ {scalar_t__ rtekind; int /*<<< orphan*/ * values_lists; } ;
struct TYPE_14__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* StringInfo ;
typedef  TYPE_3__ RangeTblEntry ;
typedef  TYPE_4__ Query ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CMD_INSERT ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ RTE_VALUES ; 
 int /*<<< orphan*/  UpdateRelationToShardNames (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deparse_shard_query (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* makeStringInfo () ; 
 int /*<<< orphan*/  pg_get_query_def (TYPE_4__*,TYPE_2__*) ; 

__attribute__((used)) static void
UpdateTaskQueryString(Query *query, Oid distributedTableId, RangeTblEntry *valuesRTE,
					  Task *task)
{
	StringInfo queryString = makeStringInfo();
	List *oldValuesLists = NIL;

	if (valuesRTE != NULL)
	{
		Assert(valuesRTE->rtekind == RTE_VALUES);
		Assert(task->rowValuesLists != NULL);

		oldValuesLists = valuesRTE->values_lists;
		valuesRTE->values_lists = task->rowValuesLists;
	}

	/*
	 * For INSERT queries, we only have one relation to update, so we can
	 * use deparse_shard_query(). For UPDATE and DELETE queries, we may have
	 * subqueries and joins, so we use relation shard list to update shard
	 * names and call pg_get_query_def() directly.
	 */
	if (query->commandType == CMD_INSERT)
	{
		deparse_shard_query(query, distributedTableId, task->anchorShardId, queryString);
	}
	else
	{
		List *relationShardList = task->relationShardList;
		UpdateRelationToShardNames((Node *) query, relationShardList);

		pg_get_query_def(query, queryString);
	}

	if (valuesRTE != NULL)
	{
		valuesRTE->values_lists = oldValuesLists;
	}

	task->queryString = queryString->data;
}