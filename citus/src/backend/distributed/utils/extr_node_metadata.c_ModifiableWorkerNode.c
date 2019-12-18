#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  WorkerNode ;

/* Variables and functions */
 int /*<<< orphan*/  CheckCitusVersion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DistNodeRelationId () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnsureCoordinator () ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/ * FindWorkerNodeAnyCluster (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WorkerNode *
ModifiableWorkerNode(const char *nodeName, int32 nodePort)
{
	WorkerNode *workerNode = NULL;

	CheckCitusVersion(ERROR);

	EnsureCoordinator();

	/* take an exclusive lock on pg_dist_node to serialize pg_dist_node changes */
	LockRelationOid(DistNodeRelationId(), ExclusiveLock);

	workerNode = FindWorkerNodeAnyCluster(nodeName, nodePort);
	if (workerNode == NULL)
	{
		ereport(ERROR, (errmsg("node at \"%s:%u\" does not exist", nodeName, nodePort)));
	}

	return workerNode;
}