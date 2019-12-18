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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  WorkerNode ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int list_length (int /*<<< orphan*/ *) ; 
 scalar_t__ list_nth (int /*<<< orphan*/ *,int) ; 
 int random () ; 

__attribute__((used)) static WorkerNode *
FindRandomNodeFromList(List *candidateWorkerNodeList)
{
	uint32 candidateNodeCount = list_length(candidateWorkerNodeList);

	/* nb, the random seed has already been set by the postmaster when starting up */
	uint32 workerPosition = (random() % candidateNodeCount);

	WorkerNode *workerNode =
		(WorkerNode *) list_nth(candidateWorkerNodeList, workerPosition);

	return workerNode;
}