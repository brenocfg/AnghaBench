#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CREATE_EMPTY_SHARD_QUERY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * GetRemoteCommandResult (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReportConnectionError (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportResultError (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendRemoteCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_1__* makeStringInfo () ; 
 int /*<<< orphan*/  masterConnection ; 
 int /*<<< orphan*/  strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64
RemoteCreateEmptyShard(char *relationName)
{
	int64 shardId = 0;
	PGresult *queryResult = NULL;
	bool raiseInterrupts = true;

	StringInfo createEmptyShardCommand = makeStringInfo();
	appendStringInfo(createEmptyShardCommand, CREATE_EMPTY_SHARD_QUERY, relationName);

	if (!SendRemoteCommand(masterConnection, createEmptyShardCommand->data))
	{
		ReportConnectionError(masterConnection, ERROR);
	}
	queryResult = GetRemoteCommandResult(masterConnection, raiseInterrupts);
	if (PQresultStatus(queryResult) == PGRES_TUPLES_OK)
	{
		char *shardIdString = PQgetvalue((PGresult *) queryResult, 0, 0);
		char *shardIdStringEnd = NULL;
		shardId = strtoul(shardIdString, &shardIdStringEnd, 0);
	}
	else
	{
		ReportResultError(masterConnection, queryResult, WARNING);
		ereport(ERROR, (errmsg("could not create a new empty shard on the remote node")));
	}

	PQclear(queryResult);
	queryResult = GetRemoteCommandResult(masterConnection, raiseInterrupts);
	Assert(!queryResult);

	return shardId;
}