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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_5__ {int /*<<< orphan*/  workerPort; int /*<<< orphan*/  workerName; } ;
typedef  TYPE_1__ WorkerNode ;
typedef  int /*<<< orphan*/  HTAB ;

/* Variables and functions */
 int /*<<< orphan*/ * GetWorkerNodeHash () ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  WORKER_LENGTH ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

WorkerNode *
FindWorkerNode(char *nodeName, int32 nodePort)
{
	WorkerNode *cachedWorkerNode = NULL;
	HTAB *workerNodeHash = GetWorkerNodeHash();
	bool handleFound = false;
	void *hashKey = NULL;

	WorkerNode *searchedNode = (WorkerNode *) palloc0(sizeof(WorkerNode));
	strlcpy(searchedNode->workerName, nodeName, WORKER_LENGTH);
	searchedNode->workerPort = nodePort;

	hashKey = (void *) searchedNode;
	cachedWorkerNode = (WorkerNode *) hash_search(workerNodeHash, hashKey, HASH_FIND,
												  &handleFound);
	if (handleFound)
	{
		WorkerNode *workerNode = (WorkerNode *) palloc(sizeof(WorkerNode));
		memcpy(workerNode, cachedWorkerNode, sizeof(WorkerNode));
		return workerNode;
	}

	return NULL;
}