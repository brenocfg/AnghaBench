#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_9__ {char* idxname; scalar_t__ indexParams; scalar_t__ indexIncludingParams; int /*<<< orphan*/ * whereClause; int /*<<< orphan*/  options; int /*<<< orphan*/  accessMethod; TYPE_1__* relation; scalar_t__ if_not_exists; scalar_t__ concurrent; scalar_t__ unique; } ;
struct TYPE_8__ {char* relname; int /*<<< orphan*/  schemaname; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ IndexStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AppendShardIdToName (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AppendStorageParametersToString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* copyObject (TYPE_2__*) ; 
 int /*<<< orphan*/ * deparse_context_for (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deparse_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  deparse_index_columns (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quote_identifier (char*) ; 
 int /*<<< orphan*/  quote_qualified_identifier (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* transformIndexStmt (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

void
deparse_shard_index_statement(IndexStmt *origStmt, Oid distrelid, int64 shardid,
							  StringInfo buffer)
{
	IndexStmt *indexStmt = copyObject(origStmt); /* copy to avoid modifications */
	char *relationName = indexStmt->relation->relname;
	char *indexName = indexStmt->idxname;
	List *deparseContext = NULL;

	/* extend relation and index name using shard identifier */
	AppendShardIdToName(&relationName, shardid);
	AppendShardIdToName(&indexName, shardid);

	/* use extended shard name and transformed stmt for deparsing */
	deparseContext = deparse_context_for(relationName, distrelid);
	indexStmt = transformIndexStmt(distrelid, indexStmt, NULL);

	appendStringInfo(buffer, "CREATE %s INDEX %s %s %s ON %s USING %s ",
					 (indexStmt->unique ? "UNIQUE" : ""),
					 (indexStmt->concurrent ? "CONCURRENTLY" : ""),
					 (indexStmt->if_not_exists ? "IF NOT EXISTS" : ""),
					 quote_identifier(indexName),
					 quote_qualified_identifier(indexStmt->relation->schemaname,
												relationName),
					 indexStmt->accessMethod);

	/* index column or expression list begins here */
	appendStringInfoChar(buffer, '(');
	deparse_index_columns(buffer, indexStmt->indexParams, deparseContext);
	appendStringInfoString(buffer, ") ");

	/* column/expressions for INCLUDE list */
	if (indexStmt->indexIncludingParams != NIL)
	{
		appendStringInfoString(buffer, "INCLUDE (");
		deparse_index_columns(buffer, indexStmt->indexIncludingParams, deparseContext);
		appendStringInfoChar(buffer, ')');
	}

	AppendStorageParametersToString(buffer, indexStmt->options);

	if (indexStmt->whereClause != NULL)
	{
		appendStringInfo(buffer, "WHERE %s", deparse_expression(indexStmt->whereClause,
																deparseContext, false,
																false));
	}
}