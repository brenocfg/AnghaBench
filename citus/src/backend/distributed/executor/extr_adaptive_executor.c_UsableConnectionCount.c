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
struct TYPE_3__ {int activeConnectionCount; int failedConnectionCount; int idleConnectionCount; int /*<<< orphan*/  sessionList; } ;
typedef  TYPE_1__ WorkerPool ;

/* Variables and functions */
 int list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
UsableConnectionCount(WorkerPool *workerPool)
{
	int initiatedConnectionCount = list_length(workerPool->sessionList);
	int activeConnectionCount = workerPool->activeConnectionCount;
	int failedConnectionCount = workerPool->failedConnectionCount;
	int idleConnectionCount = workerPool->idleConnectionCount;

	/* connections that are still establishing will soon be available for tasks */
	int establishingConnectionCount =
		initiatedConnectionCount - activeConnectionCount - failedConnectionCount;

	int usableConnectionCount = idleConnectionCount + establishingConnectionCount;

	return usableConnectionCount;
}