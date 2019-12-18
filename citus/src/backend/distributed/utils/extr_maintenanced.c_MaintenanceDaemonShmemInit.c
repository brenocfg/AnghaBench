#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hashInfo ;
struct TYPE_7__ {int keysize; int entrysize; int /*<<< orphan*/  hash; } ;
struct TYPE_6__ {char* lockTrancheName; int /*<<< orphan*/  trancheId; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MaintenanceDaemonDBData ;
typedef  TYPE_1__ MaintenanceDaemonControlData ;
typedef  TYPE_2__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  AddinShmemInitLock ; 
 int HASH_ELEM ; 
 int HASH_FUNCTION ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockInitialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockNewTrancheId () ; 
 int /*<<< orphan*/  LWLockRegisterTranche (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_1__* MaintenanceDaemonControl ; 
 int /*<<< orphan*/  MaintenanceDaemonDBHash ; 
 int /*<<< orphan*/  MaintenanceDaemonShmemSize () ; 
 int /*<<< orphan*/  ShmemInitHash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 scalar_t__ ShmemInitStruct (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  max_worker_processes ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prev_shmem_startup_hook () ; 
 int /*<<< orphan*/  tag_hash ; 

__attribute__((used)) static void
MaintenanceDaemonShmemInit(void)
{
	bool alreadyInitialized = false;
	HASHCTL hashInfo;
	int hashFlags = 0;

	LWLockAcquire(AddinShmemInitLock, LW_EXCLUSIVE);

	MaintenanceDaemonControl =
		(MaintenanceDaemonControlData *) ShmemInitStruct("Citus Maintenance Daemon",
														 MaintenanceDaemonShmemSize(),
														 &alreadyInitialized);

	/*
	 * Might already be initialized on EXEC_BACKEND type platforms that call
	 * shared library initialization functions in every backend.
	 */
	if (!alreadyInitialized)
	{
		MaintenanceDaemonControl->trancheId = LWLockNewTrancheId();
		MaintenanceDaemonControl->lockTrancheName = "Citus Maintenance Daemon";
		LWLockRegisterTranche(MaintenanceDaemonControl->trancheId,
							  MaintenanceDaemonControl->lockTrancheName);

		LWLockInitialize(&MaintenanceDaemonControl->lock,
						 MaintenanceDaemonControl->trancheId);
	}


	memset(&hashInfo, 0, sizeof(hashInfo));
	hashInfo.keysize = sizeof(Oid);
	hashInfo.entrysize = sizeof(MaintenanceDaemonDBData);
	hashInfo.hash = tag_hash;
	hashFlags = (HASH_ELEM | HASH_FUNCTION);

	MaintenanceDaemonDBHash = ShmemInitHash("Maintenance Database Hash",
											max_worker_processes, max_worker_processes,
											&hashInfo, hashFlags);

	LWLockRelease(AddinShmemInitLock);

	if (prev_shmem_startup_hook != NULL)
	{
		prev_shmem_startup_hook();
	}
}