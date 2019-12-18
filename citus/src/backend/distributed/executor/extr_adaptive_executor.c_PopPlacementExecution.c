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
struct TYPE_4__ {scalar_t__ commandsSent; int /*<<< orphan*/ * workerPool; } ;
typedef  TYPE_1__ WorkerSession ;
typedef  int /*<<< orphan*/  WorkerPool ;
typedef  int /*<<< orphan*/  TaskPlacementExecution ;

/* Variables and functions */
 int /*<<< orphan*/ * PopAssignedPlacementExecution (TYPE_1__*) ; 
 int /*<<< orphan*/ * PopUnassignedPlacementExecution (int /*<<< orphan*/ *) ; 
 scalar_t__ UseConnectionPerPlacement () ; 

__attribute__((used)) static TaskPlacementExecution *
PopPlacementExecution(WorkerSession *session)
{
	TaskPlacementExecution *placementExecution = NULL;
	WorkerPool *workerPool = session->workerPool;

	placementExecution = PopAssignedPlacementExecution(session);
	if (placementExecution == NULL)
	{
		if (session->commandsSent > 0 && UseConnectionPerPlacement())
		{
			/*
			 * Only send one command per connection if force_max_query_parallelisation
			 * is enabled, unless it's an assigned placement execution.
			 */
			return NULL;
		}

		/* no more assigned tasks, pick an unassigned task */
		placementExecution = PopUnassignedPlacementExecution(workerPool);
	}

	return placementExecution;
}