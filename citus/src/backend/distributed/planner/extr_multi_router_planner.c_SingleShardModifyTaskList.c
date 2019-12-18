#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64 ;
struct TYPE_11__ {int /*<<< orphan*/  replicationModel; int /*<<< orphan*/ * relationShardList; int /*<<< orphan*/ * taskPlacementList; void* jobId; void* anchorShardId; int /*<<< orphan*/  queryString; } ;
typedef  TYPE_1__ Task ;
struct TYPE_14__ {char partitionMethod; int /*<<< orphan*/  replicationModel; } ;
struct TYPE_13__ {int /*<<< orphan*/  relid; } ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* StringInfo ;
typedef  TYPE_3__ RangeTblEntry ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_4__ DistTableCacheEntry ;

/* Variables and functions */
 TYPE_1__* CreateTask (int /*<<< orphan*/ ) ; 
 char DISTRIBUTE_BY_NONE ; 
 TYPE_4__* DistributedTableCacheEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExtractRangeTableEntryWalker (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 TYPE_3__* GetUpdateOrDeleteRTE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MODIFY_TASK ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ SelectsFromDistributedTable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * list_make1 (TYPE_1__*) ; 
 TYPE_2__* makeStringInfo () ; 
 int /*<<< orphan*/  pg_get_query_def (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static List *
SingleShardModifyTaskList(Query *query, uint64 jobId, List *relationShardList,
						  List *placementList, uint64 shardId)
{
	Task *task = CreateTask(MODIFY_TASK);
	StringInfo queryString = makeStringInfo();
	DistTableCacheEntry *modificationTableCacheEntry = NULL;
	char modificationPartitionMethod = 0;
	List *rangeTableList = NIL;
	RangeTblEntry *updateOrDeleteRTE = NULL;

	ExtractRangeTableEntryWalker((Node *) query, &rangeTableList);
	updateOrDeleteRTE = GetUpdateOrDeleteRTE(query);

	modificationTableCacheEntry = DistributedTableCacheEntry(updateOrDeleteRTE->relid);
	modificationPartitionMethod = modificationTableCacheEntry->partitionMethod;

	if (modificationPartitionMethod == DISTRIBUTE_BY_NONE &&
		SelectsFromDistributedTable(rangeTableList, query))
	{
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("cannot perform select on a distributed table "
							   "and modify a reference table")));
	}

	pg_get_query_def(query, queryString);

	task->queryString = queryString->data;
	task->anchorShardId = shardId;
	task->jobId = jobId;
	task->taskPlacementList = placementList;
	task->relationShardList = relationShardList;
	task->replicationModel = modificationTableCacheEntry->replicationModel;

	return list_make1(task);
}