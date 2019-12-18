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
 int MaxConnections ; 
 int NUM_AUXILIARY_PROCS ; 
 int autovacuum_max_workers ; 
 int max_prepared_xacts ; 
 scalar_t__ max_wal_senders ; 
 int max_worker_processes ; 

int
TotalProcCount(void)
{
	int maxBackends = 0;
	int totalProcs = 0;

#ifdef WIN32

	/* autovacuum_max_workers is not PGDLLIMPORT, so use a high estimate for windows */
	int estimatedMaxAutovacuumWorkers = 30;
	maxBackends =
		MaxConnections + estimatedMaxAutovacuumWorkers + 1 + max_worker_processes;
#else

	/*
	 * We're simply imitating Postgrsql's InitializeMaxBackends(). Given that all
	 * the items used here PGC_POSTMASTER, should be safe to access them
	 * anytime during the execution even before InitializeMaxBackends() is called.
	 */
	maxBackends = MaxConnections + autovacuum_max_workers + 1 + max_worker_processes;
#endif

	/*
	 * We prefer to maintain space for auxiliary procs or preperad transactions in
	 * the backend space because they could be blocking processes and our current
	 * implementation of distributed deadlock detection could process them
	 * as a regular backend. In the future, we could consider changing deadlock
	 * detection algorithm to ignore auxiliary procs or prepared transactions and
	 * save some space.
	 */
	totalProcs = maxBackends + NUM_AUXILIARY_PROCS + max_prepared_xacts;

#if PG_VERSION_NUM >= 120000
	totalProcs += max_wal_senders;
#endif

	return totalProcs;
}