#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_6__ {int /*<<< orphan*/  workerPort; int /*<<< orphan*/  workerName; int /*<<< orphan*/  isActive; } ;
typedef  TYPE_1__ WorkerNode ;

/* Variables and functions */
 int /*<<< orphan*/  CheckCitusVersion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DistNodeRelationId () ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnsureCoordinator () ; 
 int /*<<< orphan*/  EnsureModificationsCanRun () ; 
 int /*<<< orphan*/  EnsureSuperUser () ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 TYPE_1__* FindWorkerNode (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkNodeHasMetadata (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MarkNodeMetadataSynced (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NOTICE ; 
 scalar_t__ NodeIsCoordinator (TYPE_1__*) ; 
 int /*<<< orphan*/  NodeIsPrimary (TYPE_1__*) ; 
 int /*<<< orphan*/  PreventInTransactionBlock (int,char*) ; 
 int /*<<< orphan*/  SyncMetadataSnapshotToNode (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 char* quote_literal_cstr (char*) ; 

void
StartMetadatSyncToNode(char *nodeNameString, int32 nodePort)
{
	WorkerNode *workerNode = NULL;
	char *escapedNodeName = quote_literal_cstr(nodeNameString);

	/* fail if metadata synchronization doesn't succeed */
	bool raiseInterrupts = true;

	EnsureCoordinator();
	EnsureSuperUser();
	EnsureModificationsCanRun();
	CheckCitusVersion(ERROR);

	PreventInTransactionBlock(true, "start_metadata_sync_to_node");

	LockRelationOid(DistNodeRelationId(), ExclusiveLock);

	workerNode = FindWorkerNode(nodeNameString, nodePort);
	if (workerNode == NULL)
	{
		ereport(ERROR, (errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
						errmsg("you cannot sync metadata to a non-existent node"),
						errhint("First, add the node with SELECT master_add_node"
								"(%s,%d)", escapedNodeName, nodePort)));
	}

	if (!workerNode->isActive)
	{
		ereport(ERROR, (errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
						errmsg("you cannot sync metadata to an inactive node"),
						errhint("First, activate the node with "
								"SELECT master_activate_node(%s,%d)",
								escapedNodeName, nodePort)));
	}

	if (NodeIsCoordinator(workerNode))
	{
		ereport(NOTICE, (errmsg("%s:%d is the coordinator and already contains "
								"metadata, skipping syncing the metadata",
								nodeNameString, nodePort)));
		return;
	}

	MarkNodeHasMetadata(nodeNameString, nodePort, true);

	if (!NodeIsPrimary(workerNode))
	{
		/*
		 * If this is a secondary node we can't actually sync metadata to it; we assume
		 * the primary node is receiving metadata.
		 */
		return;
	}

	SyncMetadataSnapshotToNode(workerNode, raiseInterrupts);
	MarkNodeMetadataSynced(workerNode->workerName, workerNode->workerPort, true);
}