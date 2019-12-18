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
struct TYPE_12__ {char* schemaname; } ;
struct TYPE_11__ {char const* commandString; int /*<<< orphan*/  taskList; scalar_t__ concurrentIndexCmd; int /*<<< orphan*/  targetRelationId; } ;
struct TYPE_10__ {char* idxname; scalar_t__ concurrent; TYPE_5__* relation; } ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_1__ IndexStmt ;
typedef  TYPE_2__ DDLJob ;

/* Variables and functions */
 int /*<<< orphan*/  CreateIndexTaskList (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ErrorIfUnsupportedIndexStmt (TYPE_1__*) ; 
 int /*<<< orphan*/ * GetMemoryChunkContext (TYPE_5__*) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int IsDistributedTable (int /*<<< orphan*/ ) ; 
 char* MemoryContextStrdup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetNamespace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShareLock ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_oid (char*,int) ; 
 int /*<<< orphan*/  get_relname_relid (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_openrv (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make1 (TYPE_2__*) ; 
 TYPE_2__* palloc0 (int) ; 

List *
PlanIndexStmt(IndexStmt *createIndexStatement, const char *createIndexCommand)
{
	List *ddlJobs = NIL;

	/*
	 * We first check whether a distributed relation is affected. For that, we need to
	 * open the relation. To prevent race conditions with later lookups, lock the table,
	 * and modify the rangevar to include the schema.
	 */
	if (createIndexStatement->relation != NULL)
	{
		Relation relation = NULL;
		Oid relationId = InvalidOid;
		bool isDistributedRelation = false;
		LOCKMODE lockmode = ShareLock;
		MemoryContext relationContext = NULL;

		/*
		 * We don't support concurrently creating indexes for distributed
		 * tables, but till this point, we don't know if it is a regular or a
		 * distributed table.
		 */
		if (createIndexStatement->concurrent)
		{
			lockmode = ShareUpdateExclusiveLock;
		}

		/*
		 * XXX: Consider using RangeVarGetRelidExtended with a permission
		 * checking callback. Right now we'll acquire the lock before having
		 * checked permissions, and will only fail when executing the actual
		 * index statements.
		 */
		relation = heap_openrv(createIndexStatement->relation, lockmode);
		relationId = RelationGetRelid(relation);

		isDistributedRelation = IsDistributedTable(relationId);

		if (createIndexStatement->relation->schemaname == NULL)
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
			relationContext = GetMemoryChunkContext(createIndexStatement->relation);
			createIndexStatement->relation->schemaname = MemoryContextStrdup(
				relationContext, namespaceName);
		}

		heap_close(relation, NoLock);

		if (isDistributedRelation)
		{
			Oid namespaceId = InvalidOid;
			Oid indexRelationId = InvalidOid;
			char *indexName = createIndexStatement->idxname;
			char *namespaceName = createIndexStatement->relation->schemaname;

			ErrorIfUnsupportedIndexStmt(createIndexStatement);

			namespaceId = get_namespace_oid(namespaceName, false);
			indexRelationId = get_relname_relid(indexName, namespaceId);

			/* if index does not exist, send the command to workers */
			if (!OidIsValid(indexRelationId))
			{
				DDLJob *ddlJob = palloc0(sizeof(DDLJob));
				ddlJob->targetRelationId = relationId;
				ddlJob->concurrentIndexCmd = createIndexStatement->concurrent;
				ddlJob->commandString = createIndexCommand;
				ddlJob->taskList = CreateIndexTaskList(relationId, createIndexStatement);

				ddlJobs = list_make1(ddlJob);
			}
		}
	}

	return ddlJobs;
}