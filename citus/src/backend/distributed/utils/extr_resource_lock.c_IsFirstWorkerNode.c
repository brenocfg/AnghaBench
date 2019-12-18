#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ groupId; } ;
typedef  TYPE_1__ WorkerNode ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * ActivePrimaryWorkerNodeList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CompareWorkerNodes ; 
 scalar_t__ GetLocalGroupId () ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/ * SortList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 scalar_t__ list_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
IsFirstWorkerNode()
{
	List *workerNodeList = ActivePrimaryWorkerNodeList(NoLock);
	WorkerNode *firstWorkerNode = NULL;

	workerNodeList = SortList(workerNodeList, CompareWorkerNodes);

	if (list_length(workerNodeList) == 0)
	{
		return false;
	}

	firstWorkerNode = (WorkerNode *) linitial(workerNodeList);

	if (firstWorkerNode->groupId == GetLocalGroupId())
	{
		return true;
	}

	return false;
}