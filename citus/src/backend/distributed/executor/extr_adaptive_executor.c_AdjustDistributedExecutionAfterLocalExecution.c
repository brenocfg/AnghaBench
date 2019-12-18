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
struct TYPE_3__ {int /*<<< orphan*/  remoteTaskList; void* unfinishedTaskCount; void* totalTaskCount; int /*<<< orphan*/  tasksToExecute; } ;
typedef  TYPE_1__ DistributedExecution ;

/* Variables and functions */
 void* list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AdjustDistributedExecutionAfterLocalExecution(DistributedExecution *execution)
{
	/* we only need to execute the remote tasks */
	execution->tasksToExecute = execution->remoteTaskList;

	execution->totalTaskCount = list_length(execution->remoteTaskList);
	execution->unfinishedTaskCount = list_length(execution->remoteTaskList);
}