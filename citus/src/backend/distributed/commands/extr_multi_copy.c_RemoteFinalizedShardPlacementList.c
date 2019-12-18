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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_7__ {char* nodeName; int nodeId; int /*<<< orphan*/  nodePort; int /*<<< orphan*/  placementId; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  TYPE_2__ ShardPlacement ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FINALIZED_SHARD_PLACEMENTS_QUERY ; 
 int /*<<< orphan*/ * GetRemoteCommandResult (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReportConnectionError (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendRemoteCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  atoll (char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__* makeStringInfo () ; 
 int /*<<< orphan*/  masterConnection ; 
 scalar_t__ palloc0 (int) ; 
 char* pstrdup (char*) ; 

__attribute__((used)) static List *
RemoteFinalizedShardPlacementList(uint64 shardId)
{
	List *finalizedPlacementList = NIL;
	PGresult *queryResult = NULL;
	bool raiseInterrupts = true;

	StringInfo shardPlacementsCommand = makeStringInfo();
	appendStringInfo(shardPlacementsCommand, FINALIZED_SHARD_PLACEMENTS_QUERY, shardId);

	if (!SendRemoteCommand(masterConnection, shardPlacementsCommand->data))
	{
		ReportConnectionError(masterConnection, ERROR);
	}
	queryResult = GetRemoteCommandResult(masterConnection, raiseInterrupts);
	if (PQresultStatus(queryResult) == PGRES_TUPLES_OK)
	{
		int rowCount = PQntuples(queryResult);
		int rowIndex = 0;

		for (rowIndex = 0; rowIndex < rowCount; rowIndex++)
		{
			char *placementIdString = PQgetvalue(queryResult, rowIndex, 0);
			char *nodeName = pstrdup(PQgetvalue(queryResult, rowIndex, 1));
			char *nodePortString = pstrdup(PQgetvalue(queryResult, rowIndex, 2));
			uint32 nodePort = atoi(nodePortString);
			uint64 placementId = atoll(placementIdString);

			ShardPlacement *shardPlacement =
				(ShardPlacement *) palloc0(sizeof(ShardPlacement));

			shardPlacement->placementId = placementId;
			shardPlacement->nodeName = nodeName;
			shardPlacement->nodePort = nodePort;

			/*
			 * We cannot know the nodeId, but it is not necessary at this point either.
			 * This is only used to to look up the connection for a group of co-located
			 * placements, but append-distributed tables are never co-located.
			 */
			shardPlacement->nodeId = -1;

			finalizedPlacementList = lappend(finalizedPlacementList, shardPlacement);
		}
	}
	else
	{
		ereport(ERROR, (errmsg("could not get shard placements from the master node")));
	}

	PQclear(queryResult);
	queryResult = GetRemoteCommandResult(masterConnection, raiseInterrupts);
	Assert(!queryResult);

	return finalizedPlacementList;
}