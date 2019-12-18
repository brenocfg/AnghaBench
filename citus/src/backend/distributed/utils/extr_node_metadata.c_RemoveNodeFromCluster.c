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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_4__ {int /*<<< orphan*/  workerName; int /*<<< orphan*/  nodeId; int /*<<< orphan*/  groupId; } ;
typedef  TYPE_1__ WorkerNode ;

/* Variables and functions */
 int /*<<< orphan*/  CloseNodeConnectionsAfterTransaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteAllReferenceTablePlacementsFromNodeGroup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteNodeRow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* ModifiableWorkerNode (char*,int /*<<< orphan*/ ) ; 
 char* NodeDeleteCommand (int /*<<< orphan*/ ) ; 
 scalar_t__ NodeGroupHasShardPlacements (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NodeIsPrimary (TYPE_1__*) ; 
 int /*<<< orphan*/  SendCommandToWorkers (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WORKERS_WITH_METADATA ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
RemoveNodeFromCluster(char *nodeName, int32 nodePort)
{
	char *nodeDeleteCommand = NULL;
	WorkerNode *workerNode = ModifiableWorkerNode(nodeName, nodePort);

	if (NodeIsPrimary(workerNode))
	{
		bool onlyConsiderActivePlacements = false;

		/*
		 * Delete reference table placements so they are not taken into account
		 * for the check if there are placements after this
		 */
		DeleteAllReferenceTablePlacementsFromNodeGroup(workerNode->groupId);

		if (NodeGroupHasShardPlacements(workerNode->groupId,
										onlyConsiderActivePlacements))
		{
			ereport(ERROR, (errmsg("you cannot remove the primary node of a node group "
								   "which has shard placements")));
		}
	}

	DeleteNodeRow(workerNode->workerName, nodePort);

	nodeDeleteCommand = NodeDeleteCommand(workerNode->nodeId);

	/* make sure we don't have any lingering session lifespan connections */
	CloseNodeConnectionsAfterTransaction(workerNode->workerName, nodePort);

	SendCommandToWorkers(WORKERS_WITH_METADATA, nodeDeleteCommand);
}