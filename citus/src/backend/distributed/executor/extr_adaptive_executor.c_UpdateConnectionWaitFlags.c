#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* workerPool; TYPE_3__* connection; } ;
typedef  TYPE_2__ WorkerSession ;
struct TYPE_9__ {int waitFlagsChanged; } ;
struct TYPE_8__ {int waitFlags; } ;
struct TYPE_6__ {TYPE_4__* distributedExecution; } ;
typedef  TYPE_3__ MultiConnection ;
typedef  TYPE_4__ DistributedExecution ;

/* Variables and functions */

__attribute__((used)) static void
UpdateConnectionWaitFlags(WorkerSession *session, int waitFlags)
{
	MultiConnection *connection = session->connection;
	DistributedExecution *execution = session->workerPool->distributedExecution;

	/* do not take any actions if the flags not changed */
	if (connection->waitFlags == waitFlags)
	{
		return;
	}

	connection->waitFlags = waitFlags;

	/* without signalling the execution, the flag changes won't be reflected */
	execution->waitFlagsChanged = true;
}