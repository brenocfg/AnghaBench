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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_3__ {int /*<<< orphan*/  groupId; } ;
typedef  TYPE_1__ WorkerNode ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* FindWorkerNode (char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,int) ; 

uint32
GroupForNode(char *nodeName, int nodePort)
{
	WorkerNode *workerNode = FindWorkerNode(nodeName, nodePort);

	if (workerNode == NULL)
	{
		ereport(ERROR, (errmsg("node at \"%s:%u\" does not exist", nodeName, nodePort)));
	}

	return workerNode->groupId;
}