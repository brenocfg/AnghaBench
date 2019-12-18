#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  workerPort; int /*<<< orphan*/  workerName; int /*<<< orphan*/  groupId; } ;
typedef  TYPE_1__ WorkerNode ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 char* CitusExtensionOwnerName () ; 
 char* LocalGroupIdUpdateCommand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MetadataCreateCommands () ; 
 int /*<<< orphan*/ * MetadataDropCommands () ; 
 int /*<<< orphan*/  SendCommandListToWorkerInSingleTransaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int SendOptionalCommandListToWorkerInTransaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_make1 (char*) ; 

__attribute__((used)) static bool
SyncMetadataSnapshotToNode(WorkerNode *workerNode, bool raiseOnError)
{
	char *extensionOwner = CitusExtensionOwnerName();

	/* generate and add the local group id's update query */
	char *localGroupIdUpdateCommand = LocalGroupIdUpdateCommand(workerNode->groupId);

	/* generate the queries which drop the metadata */
	List *dropMetadataCommandList = MetadataDropCommands();

	/* generate the queries which create the metadata from scratch */
	List *createMetadataCommandList = MetadataCreateCommands();

	List *recreateMetadataSnapshotCommandList = list_make1(localGroupIdUpdateCommand);
	recreateMetadataSnapshotCommandList = list_concat(recreateMetadataSnapshotCommandList,
													  dropMetadataCommandList);
	recreateMetadataSnapshotCommandList = list_concat(recreateMetadataSnapshotCommandList,
													  createMetadataCommandList);

	/*
	 * Send the snapshot recreation commands in a single remote transaction and
	 * if requested, error out in any kind of failure. Note that it is not
	 * required to send createMetadataSnapshotCommandList in the same transaction
	 * that we send nodeDeleteCommand and nodeInsertCommand commands below.
	 */
	if (raiseOnError)
	{
		SendCommandListToWorkerInSingleTransaction(workerNode->workerName,
												   workerNode->workerPort,
												   extensionOwner,
												   recreateMetadataSnapshotCommandList);
		return true;
	}
	else
	{
		bool success =
			SendOptionalCommandListToWorkerInTransaction(workerNode->workerName,
														 workerNode->workerPort,
														 extensionOwner,
														 recreateMetadataSnapshotCommandList);
		return success;
	}
}