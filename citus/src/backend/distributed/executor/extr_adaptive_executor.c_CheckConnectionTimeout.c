#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ poolStartTime; int activeConnectionCount; int checkForPoolTimeout; int /*<<< orphan*/  nodePort; int /*<<< orphan*/  nodeName; int /*<<< orphan*/  sessionList; TYPE_2__* distributedExecution; } ;
typedef  TYPE_1__ WorkerPool ;
typedef  scalar_t__ TimestampTz ;
struct TYPE_6__ {scalar_t__ failed; scalar_t__ errorOnAnyFailure; } ;
typedef  TYPE_2__ DistributedExecution ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_CONNECTION_FAILURE ; 
 int ERROR ; 
 scalar_t__ GetCurrentTimestamp () ; 
 int /*<<< orphan*/  NodeConnectionTimeout ; 
 scalar_t__ TimestampDifferenceExceeds (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ UseConnectionPerPlacement () ; 
 int WARNING ; 
 int /*<<< orphan*/  WorkerPoolFailed (TYPE_1__*) ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CheckConnectionTimeout(WorkerPool *workerPool)
{
	DistributedExecution *execution = workerPool->distributedExecution;
	TimestampTz poolStartTime = workerPool->poolStartTime;
	TimestampTz now = GetCurrentTimestamp();

	int initiatedConnectionCount = list_length(workerPool->sessionList);
	int activeConnectionCount = workerPool->activeConnectionCount;
	int requiredActiveConnectionCount = 1;

	if (initiatedConnectionCount == 0)
	{
		/* no connection has been planned for the pool yet */
		Assert(poolStartTime == 0);
		return;
	}

	/*
	 * This is a special case where we assign tasks to sessions even before
	 * the connections are established. So, make sure to apply similar
	 * restrictions. In this case, make sure that we get all the connections
	 * established.
	 */
	if (UseConnectionPerPlacement())
	{
		requiredActiveConnectionCount = initiatedConnectionCount;
	}

	if (TimestampDifferenceExceeds(poolStartTime, now, NodeConnectionTimeout))
	{
		if (activeConnectionCount < requiredActiveConnectionCount)
		{
			int logLevel = WARNING;

			/*
			 * First fail the pool and create an opportunity to execute tasks
			 * over other pools when tasks have more than one placement to execute.
			 */
			WorkerPoolFailed(workerPool);

			/*
			 * The enforcement is not always erroring out. For example, if a SELECT task
			 * has two different placements, we'd warn the user, fail the pool and continue
			 * with the next placement.
			 */
			if (execution->errorOnAnyFailure || execution->failed)
			{
				logLevel = ERROR;
			}

			ereport(logLevel, (errcode(ERRCODE_CONNECTION_FAILURE),
							   errmsg("could not establish any connections to the node "
									  "%s:%d after %u ms", workerPool->nodeName,
									  workerPool->nodePort,
									  NodeConnectionTimeout)));
		}
		else
		{
			/* stop interrupting WaitEventSetWait for timeouts */
			workerPool->checkForPoolTimeout = false;
		}
	}
}