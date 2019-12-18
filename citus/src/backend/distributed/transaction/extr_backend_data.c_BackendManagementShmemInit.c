#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int initiatorNodeIdentifier; } ;
struct TYPE_10__ {int /*<<< orphan*/  mutex; TYPE_1__ citusBackend; } ;
struct TYPE_8__ {int /*<<< orphan*/  trancheId; } ;
struct TYPE_9__ {TYPE_4__* backends; int /*<<< orphan*/  nextTransactionNumber; int /*<<< orphan*/  lock; TYPE_2__ namedLockTranche; } ;
typedef  TYPE_2__ NamedLWLockTranche ;
typedef  TYPE_3__ BackendManagementShmemData ;
typedef  TYPE_4__ BackendData ;

/* Variables and functions */
 int /*<<< orphan*/  AddinShmemInitLock ; 
 int /*<<< orphan*/  BackendManagementShmemSize () ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockInitialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockNewTrancheId () ; 
 int /*<<< orphan*/  LWLockRegisterTranche (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 scalar_t__ ShmemInitStruct (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SpinLockInit (int /*<<< orphan*/ *) ; 
 int TotalProcCount () ; 
 TYPE_3__* backendManagementShmemData ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_atomic_init_u64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prev_shmem_startup_hook () ; 

__attribute__((used)) static void
BackendManagementShmemInit(void)
{
	bool alreadyInitialized = false;

	/* we may update the shmem, acquire lock exclusively */
	LWLockAcquire(AddinShmemInitLock, LW_EXCLUSIVE);

	backendManagementShmemData =
		(BackendManagementShmemData *) ShmemInitStruct(
			"Backend Management Shmem",
			BackendManagementShmemSize(),
			&alreadyInitialized);

	if (!alreadyInitialized)
	{
		int backendIndex = 0;
		int totalProcs = 0;
		char *trancheName = "Backend Management Tranche";

		NamedLWLockTranche *namedLockTranche =
			&backendManagementShmemData->namedLockTranche;

		/* start by zeroing out all the memory */
		memset(backendManagementShmemData, 0,
			   BackendManagementShmemSize());

		namedLockTranche->trancheId = LWLockNewTrancheId();

		LWLockRegisterTranche(namedLockTranche->trancheId, trancheName);
		LWLockInitialize(&backendManagementShmemData->lock,
						 namedLockTranche->trancheId);

		/* start the distributed transaction ids from 1 */
		pg_atomic_init_u64(&backendManagementShmemData->nextTransactionNumber, 1);

		/*
		 * We need to init per backend's spinlock before any backend
		 * starts its execution. Note that we initialize TotalProcs (e.g., not
		 * MaxBackends) since some of the blocking processes could be prepared
		 * transactions, which aren't covered by MaxBackends.
		 *
		 * We also initiate initiatorNodeIdentifier to -1, which can never be
		 * used as a node id.
		 */
		totalProcs = TotalProcCount();
		for (backendIndex = 0; backendIndex < totalProcs; ++backendIndex)
		{
			BackendData *backendData =
				&backendManagementShmemData->backends[backendIndex];
			backendData->citusBackend.initiatorNodeIdentifier = -1;
			SpinLockInit(&backendData->mutex);
		}
	}

	LWLockRelease(AddinShmemInitLock);

	if (prev_shmem_startup_hook != NULL)
	{
		prev_shmem_startup_hook();
	}
}