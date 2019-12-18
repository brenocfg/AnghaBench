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
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * GetRemoteCommandResult (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReportConnectionError (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendRemoteCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_SHARD_STATISTICS_QUERY ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_1__* makeStringInfo () ; 
 int /*<<< orphan*/  masterConnection ; 

__attribute__((used)) static void
RemoteUpdateShardStatistics(uint64 shardId)
{
	PGresult *queryResult = NULL;
	bool raiseInterrupts = true;

	StringInfo updateShardStatisticsCommand = makeStringInfo();
	appendStringInfo(updateShardStatisticsCommand, UPDATE_SHARD_STATISTICS_QUERY,
					 shardId);

	if (!SendRemoteCommand(masterConnection, updateShardStatisticsCommand->data))
	{
		ReportConnectionError(masterConnection, ERROR);
	}
	queryResult = GetRemoteCommandResult(masterConnection, raiseInterrupts);
	if (PQresultStatus(queryResult) != PGRES_TUPLES_OK)
	{
		ereport(ERROR, (errmsg("could not update shard statistics")));
	}

	PQclear(queryResult);
	queryResult = GetRemoteCommandResult(masterConnection, raiseInterrupts);
	Assert(!queryResult);
}