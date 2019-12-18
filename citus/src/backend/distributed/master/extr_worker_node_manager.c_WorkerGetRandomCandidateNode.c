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
typedef  scalar_t__ uint32 ;
struct TYPE_4__ {char* workerRack; } ;
typedef  TYPE_1__ WorkerNode ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 TYPE_1__* FindRandomNodeFromList (int /*<<< orphan*/ *) ; 
 scalar_t__ OddNumber (scalar_t__) ; 
 int /*<<< orphan*/ * PrimaryNodesNotInList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WORKER_LENGTH ; 
 scalar_t__ WORKER_RACK_TRIES ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 scalar_t__ list_length (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 

WorkerNode *
WorkerGetRandomCandidateNode(List *currentNodeList)
{
	WorkerNode *workerNode = NULL;
	bool wantSameRack = false;
	uint32 tryCount = WORKER_RACK_TRIES;
	uint32 tryIndex = 0;

	uint32 currentNodeCount = list_length(currentNodeList);
	List *candidateWorkerNodeList = PrimaryNodesNotInList(currentNodeList);

	/* we check if the shard has already been placed on all nodes known to us */
	if (list_length(candidateWorkerNodeList) == 0)
	{
		return NULL;
	}

	/* if current node list is empty, randomly pick one node and return */
	if (currentNodeCount == 0)
	{
		workerNode = FindRandomNodeFromList(candidateWorkerNodeList);
		return workerNode;
	}

	/*
	 * If the current list has an odd number of nodes (1, 3, 5, etc), we want to
	 * place the shard on a different rack than the first node's rack.
	 * Otherwise, we want to place the shard on the same rack as the first node.
	 */
	if (OddNumber(currentNodeCount))
	{
		wantSameRack = false;
	}
	else
	{
		wantSameRack = true;
	}

	/*
	 * We try to find a worker node that fits our rack-aware placement strategy.
	 * If after a predefined number of tries, we still cannot find such a node,
	 * we simply give up and return the last worker node we found.
	 */
	for (tryIndex = 0; tryIndex < tryCount; tryIndex++)
	{
		WorkerNode *firstNode = (WorkerNode *) linitial(currentNodeList);
		char *firstRack = firstNode->workerRack;
		char *workerRack = NULL;
		bool sameRack = false;

		workerNode = FindRandomNodeFromList(candidateWorkerNodeList);
		workerRack = workerNode->workerRack;

		sameRack = (strncmp(workerRack, firstRack, WORKER_LENGTH) == 0);
		if ((sameRack && wantSameRack) || (!sameRack && !wantSameRack))
		{
			break;
		}
	}

	return workerNode;
}