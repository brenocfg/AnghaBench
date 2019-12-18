#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ReindexIndexCallbackState {int concurrent; void* locked_table_oid; } ;
struct TYPE_12__ {int /*<<< orphan*/ * schemaname; } ;
struct TYPE_11__ {int concurrentIndexCmd; char const* commandString; int /*<<< orphan*/  taskList; void* targetRelationId; } ;
struct TYPE_10__ {int concurrent; scalar_t__ kind; TYPE_5__* relation; } ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  TYPE_1__ ReindexStmt ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_2__ DDLJob ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CreateReindexTaskList (void*,TYPE_1__*) ; 
 int /*<<< orphan*/ * GetMemoryChunkContext (TYPE_5__*) ; 
 void* IndexGetRelation (void*,int) ; 
 void* InvalidOid ; 
 int IsDistributedTable (void*) ; 
 int /*<<< orphan*/ * MemoryContextStrdup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ REINDEX_OBJECT_INDEX ; 
 scalar_t__ REINDEX_OBJECT_TABLE ; 
 int /*<<< orphan*/  RangeVarCallbackForReindexIndex ; 
 int /*<<< orphan*/  RangeVarCallbackOwnsTable ; 
 void* RangeVarGetRelidExtended (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ReindexIndexCallbackState*) ; 
 int /*<<< orphan*/  RelationGetNamespace (int /*<<< orphan*/ *) ; 
 void* RelationGetRelid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_openrv (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * index_open (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make1 (TYPE_2__*) ; 
 TYPE_2__* palloc0 (int) ; 

List *
PlanReindexStmt(ReindexStmt *reindexStatement, const char *reindexCommand)
{
	List *ddlJobs = NIL;

	/*
	 * We first check whether a distributed relation is affected. For that, we need to
	 * open the relation. To prevent race conditions with later lookups, lock the table,
	 * and modify the rangevar to include the schema.
	 */
	if (reindexStatement->relation != NULL)
	{
		Relation relation = NULL;
		Oid relationId = InvalidOid;
		bool isDistributedRelation = false;
#if PG_VERSION_NUM >= 120000
		LOCKMODE lockmode = reindexStatement->concurrent ? ShareUpdateExclusiveLock :
							AccessExclusiveLock;
#else
		LOCKMODE lockmode = AccessExclusiveLock;
#endif
		MemoryContext relationContext = NULL;

		Assert(reindexStatement->kind == REINDEX_OBJECT_INDEX ||
			   reindexStatement->kind == REINDEX_OBJECT_TABLE);

		if (reindexStatement->kind == REINDEX_OBJECT_INDEX)
		{
			Oid indOid;
			struct ReindexIndexCallbackState state;
#if PG_VERSION_NUM >= 120000
			state.concurrent = reindexStatement->concurrent;
#endif
			state.locked_table_oid = InvalidOid;

			indOid = RangeVarGetRelidExtended(reindexStatement->relation,
											  lockmode, 0,
											  RangeVarCallbackForReindexIndex,
											  &state);
			relation = index_open(indOid, NoLock);
			relationId = IndexGetRelation(indOid, false);
		}
		else
		{
			RangeVarGetRelidExtended(reindexStatement->relation, lockmode, 0,
									 RangeVarCallbackOwnsTable, NULL);

			relation = heap_openrv(reindexStatement->relation, NoLock);
			relationId = RelationGetRelid(relation);
		}

		isDistributedRelation = IsDistributedTable(relationId);

		if (reindexStatement->relation->schemaname == NULL)
		{
			/*
			 * Before we do any further processing, fix the schema name to make sure
			 * that a (distributed) table with the same name does not appear on the
			 * search path in front of the current schema. We do this even if the
			 * table is not distributed, since a distributed table may appear on the
			 * search path by the time postgres starts processing this statement.
			 */
			char *namespaceName = get_namespace_name(RelationGetNamespace(relation));

			/* ensure we copy string into proper context */
			relationContext = GetMemoryChunkContext(reindexStatement->relation);
			reindexStatement->relation->schemaname = MemoryContextStrdup(relationContext,
																		 namespaceName);
		}

		if (reindexStatement->kind == REINDEX_OBJECT_INDEX)
		{
			index_close(relation, NoLock);
		}
		else
		{
			heap_close(relation, NoLock);
		}

		if (isDistributedRelation)
		{
			DDLJob *ddlJob = palloc0(sizeof(DDLJob));
			ddlJob->targetRelationId = relationId;
#if PG_VERSION_NUM >= 120000
			ddlJob->concurrentIndexCmd = reindexStatement->concurrent;
#else
			ddlJob->concurrentIndexCmd = false;
#endif
			ddlJob->commandString = reindexCommand;
			ddlJob->taskList = CreateReindexTaskList(relationId, reindexStatement);

			ddlJobs = list_make1(ddlJob);
		}
	}

	return ddlJobs;
}