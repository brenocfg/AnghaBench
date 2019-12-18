#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  worker ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int bgw_flags; int bgw_restart_time; int /*<<< orphan*/  bgw_notify_pid; int /*<<< orphan*/  bgw_extra; int /*<<< orphan*/  bgw_main_arg; int /*<<< orphan*/  bgw_function_name; int /*<<< orphan*/  bgw_library_name; int /*<<< orphan*/  bgw_start_time; int /*<<< orphan*/  bgw_name; } ;
struct TYPE_6__ {int daemonStarted; int userOid; int triggerMetadataSync; scalar_t__ latch; scalar_t__ workerPid; } ;
typedef  int Oid ;
typedef  TYPE_1__ MaintenanceDaemonDBData ;
typedef  int /*<<< orphan*/  BackgroundWorkerHandle ;
typedef  TYPE_2__ BackgroundWorker ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BGWORKER_BACKEND_DATABASE_CONNECTION ; 
 int BGWORKER_SHMEM_ACCESS ; 
 int /*<<< orphan*/  BGW_MAXLEN ; 
 int /*<<< orphan*/  BgWorkerStart_ConsistentState ; 
 int CitusExtensionOwner () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_ENTER_NULL ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_5__* MaintenanceDaemonControl ; 
 int /*<<< orphan*/  MaintenanceDaemonDBHash ; 
 int MyDatabaseId ; 
 int /*<<< orphan*/  MyProcPid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int) ; 
 int /*<<< orphan*/  RegisterDynamicBackgroundWorker (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SetLatch (scalar_t__) ; 
 int /*<<< orphan*/  WaitForBackgroundWorkerStartup (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

void
InitializeMaintenanceDaemonBackend(void)
{
	MaintenanceDaemonDBData *dbData = NULL;
	Oid extensionOwner = CitusExtensionOwner();
	bool found;

	LWLockAcquire(&MaintenanceDaemonControl->lock, LW_EXCLUSIVE);

	dbData = (MaintenanceDaemonDBData *) hash_search(MaintenanceDaemonDBHash,
													 &MyDatabaseId,
													 HASH_ENTER_NULL, &found);

	if (dbData == NULL)
	{
		/* FIXME: better message, reference relevant guc in hint */
		ereport(ERROR, (errmsg("ran out of database slots")));
	}

	if (!found || !dbData->daemonStarted)
	{
		BackgroundWorker worker;
		BackgroundWorkerHandle *handle = NULL;
		int pid = 0;

		dbData->userOid = extensionOwner;

		memset(&worker, 0, sizeof(worker));

		snprintf(worker.bgw_name, BGW_MAXLEN,
				 "Citus Maintenance Daemon: %u/%u",
				 MyDatabaseId, extensionOwner);

		/* request ability to connect to target database */
		worker.bgw_flags = BGWORKER_SHMEM_ACCESS | BGWORKER_BACKEND_DATABASE_CONNECTION;

		/*
		 * No point in getting started before able to run query, but we do
		 * want to get started on Hot-Stanby standbys.
		 */
		worker.bgw_start_time = BgWorkerStart_ConsistentState;

		/*
		 * Restart after a bit after errors, but don't bog the system.
		 */
		worker.bgw_restart_time = 5;
		sprintf(worker.bgw_library_name, "citus");
		sprintf(worker.bgw_function_name, "CitusMaintenanceDaemonMain");
		worker.bgw_main_arg = ObjectIdGetDatum(MyDatabaseId);
		memcpy(worker.bgw_extra, &extensionOwner, sizeof(Oid));
		worker.bgw_notify_pid = MyProcPid;

		if (!RegisterDynamicBackgroundWorker(&worker, &handle))
		{
			ereport(ERROR, (errmsg("could not start maintenance background worker"),
							errhint("Increasing max_worker_processes might help.")));
		}

		dbData->daemonStarted = true;
		dbData->workerPid = 0;
		dbData->triggerMetadataSync = false;
		LWLockRelease(&MaintenanceDaemonControl->lock);

		WaitForBackgroundWorkerStartup(handle, &pid);
	}
	else
	{
		Assert(dbData->daemonStarted);

		/*
		 * If owner of extension changed, wake up daemon. It'll notice and
		 * restart.
		 */
		if (dbData->userOid != extensionOwner)
		{
			dbData->userOid = extensionOwner;
			if (dbData->latch)
			{
				SetLatch(dbData->latch);
			}
		}
		LWLockRelease(&MaintenanceDaemonControl->lock);
	}
}