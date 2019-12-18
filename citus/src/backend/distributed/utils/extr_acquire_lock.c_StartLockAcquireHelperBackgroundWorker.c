#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  worker ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_10__ {int DatabaseId; int bgw_flags; int /*<<< orphan*/  bgw_extra; scalar_t__ bgw_notify_pid; int /*<<< orphan*/  bgw_main_arg; int /*<<< orphan*/  bgw_function_name; int /*<<< orphan*/  bgw_library_name; int /*<<< orphan*/  bgw_restart_time; int /*<<< orphan*/  bgw_start_time; int /*<<< orphan*/  bgw_type; int /*<<< orphan*/  bgw_name; int /*<<< orphan*/  lock_cooldown; } ;
struct TYPE_9__ {int /*<<< orphan*/ * arg; int /*<<< orphan*/  func; } ;
typedef  TYPE_1__ MemoryContextCallback ;
typedef  TYPE_2__ LockAcquireHelperArgs ;
typedef  int /*<<< orphan*/  BackgroundWorkerHandle ;
typedef  TYPE_2__ BackgroundWorker ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BGWORKER_BACKEND_DATABASE_CONNECTION ; 
 int BGWORKER_SHMEM_ACCESS ; 
 int /*<<< orphan*/  BGW_MAXLEN ; 
 int /*<<< orphan*/  BGW_NEVER_RESTART ; 
 int /*<<< orphan*/  BgWorkerStart_RecoveryFinished ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EnsureStopLockAcquireHelper ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  MemoryContextRegisterResetCallback (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int MyDatabaseId ; 
 int /*<<< orphan*/  RegisterDynamicBackgroundWorker (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* palloc0 (int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

BackgroundWorkerHandle *
StartLockAcquireHelperBackgroundWorker(int backendToHelp, int32 lock_cooldown)
{
	BackgroundWorkerHandle *handle = NULL;
	LockAcquireHelperArgs args;
	BackgroundWorker worker;
	MemoryContextCallback *workerCleanup = NULL;
	memset(&args, 0, sizeof(args));
	memset(&worker, 0, sizeof(worker));

	/* collect the extra arguments required for the background worker */
	args.DatabaseId = MyDatabaseId;
	args.lock_cooldown = lock_cooldown;

	/* construct the background worker and start it */
	snprintf(worker.bgw_name, BGW_MAXLEN,
			 "Citus Lock Acquire Helper: %d/%u",
			 backendToHelp, MyDatabaseId);
	snprintf(worker.bgw_type, BGW_MAXLEN, "citus_lock_aqcuire");

	worker.bgw_flags = BGWORKER_SHMEM_ACCESS | BGWORKER_BACKEND_DATABASE_CONNECTION;
	worker.bgw_start_time = BgWorkerStart_RecoveryFinished;
	worker.bgw_restart_time = BGW_NEVER_RESTART;

	snprintf(worker.bgw_library_name, BGW_MAXLEN, "citus");
	snprintf(worker.bgw_function_name, BGW_MAXLEN, "LockAcquireHelperMain");
	worker.bgw_main_arg = Int32GetDatum(backendToHelp);
	worker.bgw_notify_pid = 0;

	/*
	 * we check if args fits in bgw_extra to make sure it is safe to copy the data. Once
	 * we exceed the size of data to copy this way we need to look into a different way of
	 * passing the arguments to the worker.
	 */
	Assert(sizeof(worker.bgw_extra) >= sizeof(args));
	memcpy(worker.bgw_extra, &args, sizeof(args));

	if (!RegisterDynamicBackgroundWorker(&worker, &handle))
	{
		ereport(ERROR, (errmsg("could not start lock acquiring background worker to "
							   "force the update"),
						errhint("Increasing max_worker_processes might help.")));
	}

	workerCleanup = palloc0(sizeof(MemoryContextCallback));
	workerCleanup->func = EnsureStopLockAcquireHelper;
	workerCleanup->arg = handle;

	MemoryContextRegisterResetCallback(CurrentMemoryContext, workerCleanup);

	return handle;
}