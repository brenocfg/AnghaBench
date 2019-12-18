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
typedef  int /*<<< orphan*/  WorkerNode ;

/* Variables and functions */
 scalar_t__ NodeIsPrimary (int /*<<< orphan*/ *) ; 
 scalar_t__ NodeIsSecondary (int /*<<< orphan*/ *) ; 
 scalar_t__ ReadFromSecondaries ; 
 scalar_t__ USE_SECONDARY_NODES_ALWAYS ; 
 scalar_t__ USE_SECONDARY_NODES_NEVER ; 

bool
NodeIsReadable(WorkerNode *workerNode)
{
	if (ReadFromSecondaries == USE_SECONDARY_NODES_NEVER &&
		NodeIsPrimary(workerNode))
	{
		return true;
	}

	if (ReadFromSecondaries == USE_SECONDARY_NODES_ALWAYS &&
		NodeIsSecondary(workerNode))
	{
		return true;
	}

	return false;
}