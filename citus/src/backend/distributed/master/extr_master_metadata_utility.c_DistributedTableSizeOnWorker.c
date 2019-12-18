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
struct TYPE_6__ {char* workerName; int /*<<< orphan*/  workerPort; } ;
typedef  TYPE_1__ WorkerNode ;
struct TYPE_7__ {char* data; } ;
typedef  TYPE_2__* StringInfo ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MultiConnection ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ClearResults (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERRCODE_CONNECTION_FAILURE ; 
 int /*<<< orphan*/  ERROR ; 
 int ExecuteOptionalRemoteCommand (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 TYPE_2__* GenerateSizeQueryOnMultiplePlacements (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * GetNodeConnection (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ReadFirstColumnAsText (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ShardIntervalsOnWorkerGroup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atol (char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64
DistributedTableSizeOnWorker(WorkerNode *workerNode, Oid relationId, char *sizeQuery)
{
	StringInfo tableSizeQuery = NULL;
	StringInfo tableSizeStringInfo = NULL;
	char *workerNodeName = workerNode->workerName;
	uint32 workerNodePort = workerNode->workerPort;
	char *tableSizeString;
	uint64 tableSize = 0;
	MultiConnection *connection = NULL;
	uint32 connectionFlag = 0;
	PGresult *result = NULL;
	int queryResult = 0;
	List *sizeList = NIL;
	bool raiseErrors = true;

	List *shardIntervalsOnNode = ShardIntervalsOnWorkerGroup(workerNode, relationId);

	tableSizeQuery = GenerateSizeQueryOnMultiplePlacements(relationId,
														   shardIntervalsOnNode,
														   sizeQuery);

	connection = GetNodeConnection(connectionFlag, workerNodeName, workerNodePort);
	queryResult = ExecuteOptionalRemoteCommand(connection, tableSizeQuery->data, &result);

	if (queryResult != 0)
	{
		ereport(ERROR, (errcode(ERRCODE_CONNECTION_FAILURE),
						errmsg("cannot get the size because of a connection error")));
	}

	sizeList = ReadFirstColumnAsText(result);
	tableSizeStringInfo = (StringInfo) linitial(sizeList);
	tableSizeString = tableSizeStringInfo->data;
	tableSize = atol(tableSizeString);

	PQclear(result);
	ClearResults(connection, raiseErrors);

	return tableSize;
}