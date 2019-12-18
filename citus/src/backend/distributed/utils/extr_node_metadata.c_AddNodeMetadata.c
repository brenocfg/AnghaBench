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
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_8__ {int nodeId; } ;
typedef  TYPE_1__ WorkerNode ;
struct TYPE_9__ {scalar_t__ groupId; int shouldHaveShards; int hasMetadata; scalar_t__ nodeRole; int /*<<< orphan*/  nodeCluster; } ;
typedef  TYPE_2__ NodeMetadata ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ COORDINATOR_GROUP_ID ; 
 scalar_t__ CountPrimariesWithMetadata () ; 
 int /*<<< orphan*/  DistNodeRelationId () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnsureCoordinator () ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 TYPE_1__* FindWorkerNodeAnyCluster (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ GetNextGroupId () ; 
 int GetNextNodeId () ; 
 scalar_t__ INVALID_GROUP_ID ; 
 int /*<<< orphan*/  InsertNodeRow (int,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* NodeDeleteCommand (int) ; 
 char* NodeListInsertCommand (int /*<<< orphan*/ *) ; 
 TYPE_1__* PrimaryNodeForGroup (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ PrimaryNodeRoleId () ; 
 int /*<<< orphan*/  SendCommandToWorkers (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WORKERS_WITH_METADATA ; 
 int /*<<< orphan*/  WORKER_DEFAULT_CLUSTER ; 
 int /*<<< orphan*/  WORKER_LENGTH ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/ * list_make1 (TYPE_1__*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
AddNodeMetadata(char *nodeName, int32 nodePort,
				NodeMetadata *nodeMetadata,
				bool *nodeAlreadyExists)
{
	int nextNodeIdInt = 0;
	WorkerNode *workerNode = NULL;
	char *nodeDeleteCommand = NULL;
	uint32 primariesWithMetadata = 0;

	EnsureCoordinator();

	*nodeAlreadyExists = false;

	/*
	 * Take an exclusive lock on pg_dist_node to serialize node changes.
	 * We may want to relax or have more fine-grained locking in the future
	 * to allow users to add multiple nodes concurrently.
	 */
	LockRelationOid(DistNodeRelationId(), ExclusiveLock);

	workerNode = FindWorkerNodeAnyCluster(nodeName, nodePort);
	if (workerNode != NULL)
	{
		/* fill return data and return */
		*nodeAlreadyExists = true;

		return workerNode->nodeId;
	}

	/* user lets Citus to decide on the group that the newly added node should be in */
	if (nodeMetadata->groupId == INVALID_GROUP_ID)
	{
		nodeMetadata->groupId = GetNextGroupId();
	}

	/* if this is a coordinator, we shouldn't place shards on it */
	if (nodeMetadata->groupId == COORDINATOR_GROUP_ID)
	{
		nodeMetadata->shouldHaveShards = false;
		nodeMetadata->hasMetadata = true;
	}

	/* if nodeRole hasn't been added yet there's a constraint for one-node-per-group */
	if (nodeMetadata->nodeRole != InvalidOid && nodeMetadata->nodeRole ==
		PrimaryNodeRoleId())
	{
		WorkerNode *existingPrimaryNode = PrimaryNodeForGroup(nodeMetadata->groupId,
															  NULL);

		if (existingPrimaryNode != NULL)
		{
			ereport(ERROR, (errmsg("group %d already has a primary node",
								   nodeMetadata->groupId)));
		}
	}

	if (nodeMetadata->nodeRole == PrimaryNodeRoleId())
	{
		if (strncmp(nodeMetadata->nodeCluster,
					WORKER_DEFAULT_CLUSTER,
					WORKER_LENGTH) != 0)
		{
			ereport(ERROR, (errmsg("primaries must be added to the default cluster")));
		}
	}

	/* generate the new node id from the sequence */
	nextNodeIdInt = GetNextNodeId();

	InsertNodeRow(nextNodeIdInt, nodeName, nodePort, nodeMetadata);

	workerNode = FindWorkerNodeAnyCluster(nodeName, nodePort);

	/* send the delete command to all primary nodes with metadata */
	nodeDeleteCommand = NodeDeleteCommand(workerNode->nodeId);
	SendCommandToWorkers(WORKERS_WITH_METADATA, nodeDeleteCommand);

	/* finally prepare the insert command and send it to all primary nodes */
	primariesWithMetadata = CountPrimariesWithMetadata();
	if (primariesWithMetadata != 0)
	{
		List *workerNodeList = list_make1(workerNode);
		char *nodeInsertCommand = NodeListInsertCommand(workerNodeList);

		SendCommandToWorkers(WORKERS_WITH_METADATA, nodeInsertCommand);
	}

	return workerNode->nodeId;
}