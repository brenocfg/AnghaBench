#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nodeId; } ;
typedef  TYPE_1__ WorkerNode ;

/* Variables and functions */
 int /*<<< orphan*/  DistNodeRelationId () ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PropagateRolesToNewNode (TYPE_1__*) ; 
 TYPE_1__* SetNodeState (char*,int,int) ; 
 int /*<<< orphan*/  SetUpDistributedTableDependencies (TYPE_1__*) ; 

__attribute__((used)) static int
ActivateNode(char *nodeName, int nodePort)
{
	WorkerNode *newWorkerNode = NULL;
	bool isActive = true;

	/* take an exclusive lock on pg_dist_node to serialize pg_dist_node changes */
	LockRelationOid(DistNodeRelationId(), ExclusiveLock);

	newWorkerNode = SetNodeState(nodeName, nodePort, isActive);

	PropagateRolesToNewNode(newWorkerNode);
	SetUpDistributedTableDependencies(newWorkerNode);
	return newWorkerNode->nodeId;
}