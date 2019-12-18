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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_6__ {scalar_t__ taskHashTrancheId; char* taskHashTrancheName; int conninfosValid; int /*<<< orphan*/  taskHashLock; } ;
typedef  TYPE_1__ WorkerTasksSharedStateData ;
struct TYPE_7__ {int keysize; int /*<<< orphan*/  hash; int /*<<< orphan*/  entrysize; } ;
typedef  TYPE_2__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  AddinShmemInitLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 int HASH_ELEM ; 
 int HASH_FUNCTION ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockInitialize (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LWLockNewTrancheId () ; 
 int /*<<< orphan*/  LWLockRegisterTranche (scalar_t__,char*) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 scalar_t__ MaxTrackedTasksPerNode ; 
 int /*<<< orphan*/ * ShmemInitHash (char*,long,long,TYPE_2__*,int) ; 
 scalar_t__ ShmemInitStruct (char*,int,int*) ; 
 int /*<<< orphan*/ * TaskTrackerTaskHash ; 
 int /*<<< orphan*/  WORKER_TASK_SIZE ; 
 TYPE_1__* WorkerTasksSharedState ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prev_shmem_startup_hook () ; 
 int /*<<< orphan*/  tag_hash ; 

__attribute__((used)) static void
TaskTrackerShmemInit(void)
{
	bool alreadyInitialized = false;
	HASHCTL info;
	int hashFlags = 0;
	long maxTableSize = 0;
	long initTableSize = 0;

	maxTableSize = (long) MaxTrackedTasksPerNode;
	initTableSize = maxTableSize / 8;

	/*
	 * Allocate the control structure for the hash table that maps unique task
	 * identifiers (uint64:uint32) to general task information, as well as the
	 * parameters needed to run the task.
	 */
	memset(&info, 0, sizeof(info));
	info.keysize = sizeof(uint64) + sizeof(uint32);
	info.entrysize = WORKER_TASK_SIZE;
	info.hash = tag_hash;
	hashFlags = (HASH_ELEM | HASH_FUNCTION);

	/*
	 * Currently the lock isn't required because allocation only happens at
	 * startup in postmaster, but it doesn't hurt, and makes things more
	 * consistent with other extensions.
	 */
	LWLockAcquire(AddinShmemInitLock, LW_EXCLUSIVE);

	/* allocate struct containing task tracker related shared state */
	WorkerTasksSharedState =
		(WorkerTasksSharedStateData *) ShmemInitStruct("Worker Task Control",
													   sizeof(WorkerTasksSharedStateData),
													   &alreadyInitialized);

	if (!alreadyInitialized)
	{
		WorkerTasksSharedState->taskHashTrancheId = LWLockNewTrancheId();
		WorkerTasksSharedState->taskHashTrancheName = "Worker Task Hash Tranche";
		LWLockRegisterTranche(WorkerTasksSharedState->taskHashTrancheId,
							  WorkerTasksSharedState->taskHashTrancheName);

		LWLockInitialize(&WorkerTasksSharedState->taskHashLock,
						 WorkerTasksSharedState->taskHashTrancheId);

		WorkerTasksSharedState->conninfosValid = true;
	}

	/*  allocate hash table */
	TaskTrackerTaskHash = ShmemInitHash("Worker Task Hash", initTableSize, maxTableSize,
										&info, hashFlags);

	LWLockRelease(AddinShmemInitLock);

	Assert(TaskTrackerTaskHash != NULL);
	Assert(WorkerTasksSharedState->taskHashTrancheId != 0);

	if (prev_shmem_startup_hook != NULL)
	{
		prev_shmem_startup_hook();
	}
}