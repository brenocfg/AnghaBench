#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_7__ {int kind; scalar_t__ options; int /*<<< orphan*/  name; TYPE_1__* relation; scalar_t__ concurrent; } ;
struct TYPE_6__ {char* relname; int /*<<< orphan*/  schemaname; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_2__ ReindexStmt ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AppendShardIdToName (char**,int /*<<< orphan*/ ) ; 
 scalar_t__ REINDEXOPT_VERBOSE ; 
#define  REINDEX_OBJECT_DATABASE 132 
#define  REINDEX_OBJECT_INDEX 131 
#define  REINDEX_OBJECT_SCHEMA 130 
#define  REINDEX_OBJECT_SYSTEM 129 
#define  REINDEX_OBJECT_TABLE 128 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* copyObject (TYPE_2__*) ; 
 int /*<<< orphan*/  quote_identifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quote_qualified_identifier (int /*<<< orphan*/ ,char*) ; 

void
deparse_shard_reindex_statement(ReindexStmt *origStmt, Oid distrelid, int64 shardid,
								StringInfo buffer)
{
	ReindexStmt *reindexStmt = copyObject(origStmt); /* copy to avoid modifications */
	char *relationName = NULL;
#if PG_VERSION_NUM >= 120000
	const char *concurrentlyString = reindexStmt->concurrent ? "CONCURRENTLY " : "";
#else
	const char *concurrentlyString = "";
#endif


	if (reindexStmt->kind == REINDEX_OBJECT_INDEX ||
		reindexStmt->kind == REINDEX_OBJECT_TABLE)
	{
		relationName = reindexStmt->relation->relname;

		/* extend relation and index name using shard identifier */
		AppendShardIdToName(&relationName, shardid);
	}

	appendStringInfoString(buffer, "REINDEX ");

	if (reindexStmt->options == REINDEXOPT_VERBOSE)
	{
		appendStringInfoString(buffer, "(VERBOSE) ");
	}

	switch (reindexStmt->kind)
	{
		case REINDEX_OBJECT_INDEX:
		{
			appendStringInfo(buffer, "INDEX %s%s", concurrentlyString,
							 quote_qualified_identifier(reindexStmt->relation->schemaname,
														relationName));
			break;
		}

		case REINDEX_OBJECT_TABLE:
		{
			appendStringInfo(buffer, "TABLE %s%s", concurrentlyString,
							 quote_qualified_identifier(reindexStmt->relation->schemaname,
														relationName));
			break;
		}

		case REINDEX_OBJECT_SCHEMA:
		{
			appendStringInfo(buffer, "SCHEMA %s%s", concurrentlyString,
							 quote_identifier(reindexStmt->name));
			break;
		}

		case REINDEX_OBJECT_SYSTEM:
		{
			appendStringInfo(buffer, "SYSTEM %s%s", concurrentlyString,
							 quote_identifier(reindexStmt->name));
			break;
		}

		case REINDEX_OBJECT_DATABASE:
		{
			appendStringInfo(buffer, "DATABASE %s%s", concurrentlyString,
							 quote_identifier(reindexStmt->name));
			break;
		}
	}
}