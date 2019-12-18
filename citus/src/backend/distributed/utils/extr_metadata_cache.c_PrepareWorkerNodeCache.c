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

/* Variables and functions */
 int /*<<< orphan*/  AcceptInvalidationMessages () ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  DistNodeRelationId () ; 
 int /*<<< orphan*/  InitializeCaches () ; 
 int /*<<< orphan*/  InitializeWorkerNodeCache () ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int workerNodeHashValid ; 

__attribute__((used)) static void
PrepareWorkerNodeCache(void)
{
	InitializeCaches(); /* ensure relevant callbacks are registered */

	/*
	 * Simulate a SELECT from pg_dist_node, ensure pg_dist_node doesn't change while our
	 * caller is using WorkerNodeHash.
	 */
	LockRelationOid(DistNodeRelationId(), AccessShareLock);

	/*
	 * We might have some concurrent metadata changes. In order to get the changes,
	 * we first need to accept the cache invalidation messages.
	 */
	AcceptInvalidationMessages();

	if (!workerNodeHashValid)
	{
		InitializeWorkerNodeCache();

		workerNodeHashValid = true;
	}
}