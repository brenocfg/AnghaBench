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
struct TYPE_4__ {int /*<<< orphan*/  workerPort; int /*<<< orphan*/  workerName; } ;
typedef  TYPE_1__ WorkerNode ;

/* Variables and functions */
 scalar_t__ ClusterHasDistributedFunctionWithDistArgument () ; 
 int /*<<< orphan*/  EnsureNoModificationsHaveBeenDone () ; 
 int /*<<< orphan*/  MarkNodeHasMetadata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 scalar_t__ NodeIsPrimary (TYPE_1__*) ; 
 int /*<<< orphan*/  ReplicateAllDependenciesToNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReplicateAllReferenceTablesToNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TriggerMetadataSync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SetUpDistributedTableDependencies(WorkerNode *newWorkerNode)
{
	if (NodeIsPrimary(newWorkerNode))
	{
		EnsureNoModificationsHaveBeenDone();
		ReplicateAllDependenciesToNode(newWorkerNode->workerName,
									   newWorkerNode->workerPort);
		ReplicateAllReferenceTablesToNode(newWorkerNode->workerName,
										  newWorkerNode->workerPort);

		/*
		 * Let the maintenance daemon do the hard work of syncing the metadata.
		 * We prefer this because otherwise node activation might fail within
		 * transaction blocks.
		 */
		if (ClusterHasDistributedFunctionWithDistArgument())
		{
			MarkNodeHasMetadata(newWorkerNode->workerName, newWorkerNode->workerPort,
								true);
			TriggerMetadataSync(MyDatabaseId);
		}
	}
}