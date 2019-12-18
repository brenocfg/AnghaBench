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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  text ;
struct TYPE_6__ {int /*<<< orphan*/  varattno; } ;
typedef  TYPE_1__ Var ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* StringInfo ;
typedef  int /*<<< orphan*/  ShardPlacement ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MultiConnection ;

/* Variables and functions */
 int CStoreTable (int /*<<< orphan*/ ) ; 
 char DISTRIBUTE_BY_APPEND ; 
 int ExecuteOptionalRemoteCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ForgetResults (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetPlacementConnection (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQgetisnull (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 TYPE_1__* PartitionColumn (int /*<<< orphan*/ ,int const) ; 
 char PartitionMethod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHARD_CSTORE_TABLE_SIZE_QUERY ; 
 int /*<<< orphan*/  SHARD_RANGE_QUERY ; 
 int /*<<< orphan*/  SHARD_TABLE_SIZE_QUERY ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * cstring_to_text (char*) ; 
 scalar_t__ errno ; 
 char* get_attname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* makeStringInfo () ; 
 int /*<<< orphan*/  pg_strtouint64 (char*,char**,int /*<<< orphan*/ ) ; 
 char* quote_literal_cstr (char*) ; 

__attribute__((used)) static bool
WorkerShardStats(ShardPlacement *placement, Oid relationId, char *shardName,
				 uint64 *shardSize, text **shardMinValue, text **shardMaxValue)
{
	char *quotedShardName = NULL;
	bool cstoreTable = false;
	StringInfo tableSizeQuery = makeStringInfo();

	const uint32 unusedTableId = 1;
	char partitionType = PartitionMethod(relationId);
	Var *partitionColumn = NULL;
	char *partitionColumnName = NULL;
	StringInfo partitionValueQuery = makeStringInfo();

	PGresult *queryResult = NULL;
	const int minValueIndex = 0;
	const int maxValueIndex = 1;

	uint64 tableSize = 0;
	char *tableSizeString = NULL;
	char *tableSizeStringEnd = NULL;
	bool minValueIsNull = false;
	bool maxValueIsNull = false;

	int connectionFlags = 0;
	int executeCommand = 0;

	MultiConnection *connection = GetPlacementConnection(connectionFlags, placement,
														 NULL);

	*shardSize = 0;
	*shardMinValue = NULL;
	*shardMaxValue = NULL;

	quotedShardName = quote_literal_cstr(shardName);

	cstoreTable = CStoreTable(relationId);
	if (cstoreTable)
	{
		appendStringInfo(tableSizeQuery, SHARD_CSTORE_TABLE_SIZE_QUERY, quotedShardName);
	}
	else
	{
		appendStringInfo(tableSizeQuery, SHARD_TABLE_SIZE_QUERY, quotedShardName);
	}

	executeCommand = ExecuteOptionalRemoteCommand(connection, tableSizeQuery->data,
												  &queryResult);
	if (executeCommand != 0)
	{
		return false;
	}

	tableSizeString = PQgetvalue(queryResult, 0, 0);
	if (tableSizeString == NULL)
	{
		PQclear(queryResult);
		ForgetResults(connection);
		return false;
	}

	errno = 0;
	tableSize = pg_strtouint64(tableSizeString, &tableSizeStringEnd, 0);
	if (errno != 0 || (*tableSizeStringEnd) != '\0')
	{
		PQclear(queryResult);
		ForgetResults(connection);
		return false;
	}

	*shardSize = tableSize;

	PQclear(queryResult);
	ForgetResults(connection);

	if (partitionType != DISTRIBUTE_BY_APPEND)
	{
		/* we don't need min/max for non-append distributed tables */
		return true;
	}

	/* fill in the partition column name and shard name in the query. */
	partitionColumn = PartitionColumn(relationId, unusedTableId);
	partitionColumnName = get_attname(relationId, partitionColumn->varattno, false);
	appendStringInfo(partitionValueQuery, SHARD_RANGE_QUERY,
					 partitionColumnName, partitionColumnName, shardName);

	executeCommand = ExecuteOptionalRemoteCommand(connection, partitionValueQuery->data,
												  &queryResult);
	if (executeCommand != 0)
	{
		return false;
	}

	minValueIsNull = PQgetisnull(queryResult, 0, minValueIndex);
	maxValueIsNull = PQgetisnull(queryResult, 0, maxValueIndex);

	if (!minValueIsNull && !maxValueIsNull)
	{
		char *minValueResult = PQgetvalue(queryResult, 0, minValueIndex);
		char *maxValueResult = PQgetvalue(queryResult, 0, maxValueIndex);

		*shardMinValue = cstring_to_text(minValueResult);
		*shardMaxValue = cstring_to_text(maxValueResult);
	}

	PQclear(queryResult);
	ForgetResults(connection);

	return true;
}