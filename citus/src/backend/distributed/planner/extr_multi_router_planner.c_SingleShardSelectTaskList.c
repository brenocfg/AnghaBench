#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64 ;
struct TYPE_7__ {int /*<<< orphan*/ * relationRowLockList; int /*<<< orphan*/ * relationShardList; int /*<<< orphan*/ * taskPlacementList; void* jobId; void* anchorShardId; int /*<<< orphan*/  queryString; } ;
typedef  TYPE_1__ Task ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* StringInfo ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 TYPE_1__* CreateTask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  ROUTER_TASK ; 
 int /*<<< orphan*/  RowLocksOnRelations (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * list_make1 (TYPE_1__*) ; 
 TYPE_2__* makeStringInfo () ; 
 int /*<<< orphan*/  pg_get_query_def (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static List *
SingleShardSelectTaskList(Query *query, uint64 jobId, List *relationShardList,
						  List *placementList,
						  uint64 shardId)
{
	Task *task = CreateTask(ROUTER_TASK);
	StringInfo queryString = makeStringInfo();
	List *relationRowLockList = NIL;

	RowLocksOnRelations((Node *) query, &relationRowLockList);
	pg_get_query_def(query, queryString);

	task->queryString = queryString->data;
	task->anchorShardId = shardId;
	task->jobId = jobId;
	task->taskPlacementList = placementList;
	task->relationShardList = relationShardList;
	task->relationRowLockList = relationRowLockList;

	return list_make1(task);
}