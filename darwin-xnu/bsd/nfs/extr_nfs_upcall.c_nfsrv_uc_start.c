#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ucq_thd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 scalar_t__ NFS_UC_HASH_SZ ; 
 int /*<<< orphan*/  PSOCK ; 
 int kernel_thread_start (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 unsigned long long nfsrv_uc_queue_count ; 
 unsigned long long nfsrv_uc_queue_max_seen ; 
 TYPE_1__* nfsrv_uc_queue_tbl ; 
 scalar_t__ nfsrv_uc_shutdown ; 
 int /*<<< orphan*/  nfsrv_uc_shutdown_lock ; 
 int /*<<< orphan*/  nfsrv_uc_thread ; 
 size_t nfsrv_uc_thread_count ; 
 int /*<<< orphan*/  nfsrv_uc_use_proxy ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
nfsrv_uc_start(void)
{
	int32_t i;
	int error;

#ifdef NFS_UC_Q_DEBUG
	if (!nfsrv_uc_use_proxy)
		return;
#endif
	DPRINT("nfsrv_uc_start\n");

	/* Wait until previous shutdown finishes */
	lck_mtx_lock(nfsrv_uc_shutdown_lock);
	while (nfsrv_uc_shutdown || nfsrv_uc_thread_count > 0)
		msleep(&nfsrv_uc_thread_count, nfsrv_uc_shutdown_lock, PSOCK, "nfsd_upcall_shutdown_wait", NULL);

	/* Start up-call threads */
	for (i = 0; i < NFS_UC_HASH_SZ; i++) {
		error = kernel_thread_start(nfsrv_uc_thread, (void *)(uintptr_t)i, &nfsrv_uc_queue_tbl[nfsrv_uc_thread_count].ucq_thd);
		if (!error) {
			nfsrv_uc_thread_count++;
		} else {
			printf("nfsd: Could not start nfsrv_uc_thread: %d\n", error);
		}
	}
	if (nfsrv_uc_thread_count == 0) {
		printf("nfsd: Could not start nfsd proxy up-call service. Falling back\n");
		goto out;
	}

out:
#ifdef NFS_UC_Q_DEBUG
	nfsrv_uc_queue_count = 0ULL;
	nfsrv_uc_queue_max_seen = 0ULL;
#endif
	lck_mtx_unlock(nfsrv_uc_shutdown_lock);
}