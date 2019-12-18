#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {scalar_t__ workerPid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ MaintenanceDaemonDBData ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_2__* MaintenanceDaemonControl ; 
 int /*<<< orphan*/  MaintenanceDaemonDBHash ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 

void
StopMaintenanceDaemon(Oid databaseId)
{
	bool found = false;
	MaintenanceDaemonDBData *dbData = NULL;
	pid_t workerPid = 0;

	LWLockAcquire(&MaintenanceDaemonControl->lock, LW_EXCLUSIVE);

	dbData = (MaintenanceDaemonDBData *) hash_search(MaintenanceDaemonDBHash,
													 &databaseId, HASH_REMOVE, &found);
	if (found)
	{
		workerPid = dbData->workerPid;
	}

	LWLockRelease(&MaintenanceDaemonControl->lock);

	if (workerPid > 0)
	{
		kill(workerPid, SIGTERM);
	}
}