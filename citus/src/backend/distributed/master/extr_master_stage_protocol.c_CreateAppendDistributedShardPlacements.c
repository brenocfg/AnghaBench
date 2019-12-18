#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_5__ {char* workerName; int /*<<< orphan*/  workerPort; int /*<<< orphan*/  groupId; } ;
typedef  TYPE_1__ WorkerNode ;
struct TYPE_6__ {int /*<<< orphan*/  pgConn; } ;
typedef  int /*<<< orphan*/  RelayFileState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ MultiConnection ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ CONNECTION_OK ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecuteCriticalRemoteCommandList (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_FINALIZED ; 
 int /*<<< orphan*/  FOR_DDL ; 
 TYPE_2__* GetNodeUserDatabaseConnection (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetTableDDLEvents (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * GetTableForeignConstraintCommands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVALID_PLACEMENT_ID ; 
 int /*<<< orphan*/  InsertShardPlacementRow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ ) ; 
 char* TableOwner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/ * WorkerCreateShardCommandList (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 scalar_t__ list_nth (int /*<<< orphan*/ *,int) ; 

void
CreateAppendDistributedShardPlacements(Oid relationId, int64 shardId,
									   List *workerNodeList, int replicationFactor)
{
	int attemptCount = replicationFactor;
	int workerNodeCount = list_length(workerNodeList);
	int placementsCreated = 0;
	int attemptNumber = 0;
	List *foreignConstraintCommandList = GetTableForeignConstraintCommands(relationId);
	bool includeSequenceDefaults = false;
	List *ddlCommandList = GetTableDDLEvents(relationId, includeSequenceDefaults);
	uint32 connectionFlag = FOR_DDL;
	char *relationOwner = TableOwner(relationId);

	/* if we have enough nodes, add an extra placement attempt for backup */
	if (workerNodeCount > replicationFactor)
	{
		attemptCount++;
	}

	for (attemptNumber = 0; attemptNumber < attemptCount; attemptNumber++)
	{
		int workerNodeIndex = attemptNumber % workerNodeCount;
		WorkerNode *workerNode = (WorkerNode *) list_nth(workerNodeList, workerNodeIndex);
		uint32 nodeGroupId = workerNode->groupId;
		char *nodeName = workerNode->workerName;
		uint32 nodePort = workerNode->workerPort;
		int shardIndex = -1; /* not used in this code path */
		const RelayFileState shardState = FILE_FINALIZED;
		const uint64 shardSize = 0;
		MultiConnection *connection =
			GetNodeUserDatabaseConnection(connectionFlag, nodeName, nodePort,
										  relationOwner, NULL);
		List *commandList = NIL;

		if (PQstatus(connection->pgConn) != CONNECTION_OK)
		{
			ereport(WARNING, (errmsg("could not connect to node \"%s:%u\"", nodeName,
									 nodePort)));

			continue;
		}

		commandList = WorkerCreateShardCommandList(relationId, shardIndex, shardId,
												   ddlCommandList,
												   foreignConstraintCommandList);

		ExecuteCriticalRemoteCommandList(connection, commandList);

		InsertShardPlacementRow(shardId, INVALID_PLACEMENT_ID, shardState, shardSize,
								nodeGroupId);
		placementsCreated++;

		if (placementsCreated >= replicationFactor)
		{
			break;
		}
	}

	/* check if we created enough shard replicas */
	if (placementsCreated < replicationFactor)
	{
		ereport(ERROR, (errmsg("could only create %u of %u of required shard replicas",
							   placementsCreated, replicationFactor)));
	}
}