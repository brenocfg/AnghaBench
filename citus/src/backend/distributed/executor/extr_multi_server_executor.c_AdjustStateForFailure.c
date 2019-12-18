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
struct TYPE_3__ {int nodeCount; int currentNodeIndex; int /*<<< orphan*/  failureCount; } ;
typedef  TYPE_1__ TaskExecution ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 

void
AdjustStateForFailure(TaskExecution *taskExecution)
{
	int maxNodeIndex = taskExecution->nodeCount - 1;
	Assert(maxNodeIndex >= 0);

	if (taskExecution->currentNodeIndex < maxNodeIndex)
	{
		taskExecution->currentNodeIndex++;   /* try next worker node */
	}
	else
	{
		taskExecution->currentNodeIndex = 0; /* go back to the first worker node */
	}

	taskExecution->failureCount++;          /* record failure */
}