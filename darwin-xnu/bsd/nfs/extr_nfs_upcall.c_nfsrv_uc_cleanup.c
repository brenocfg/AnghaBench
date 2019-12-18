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
struct nfsrv_uc_queue {int /*<<< orphan*/  ucq_lock; int /*<<< orphan*/  ucq_queue; } ;
struct nfsrv_uc_arg {int /*<<< orphan*/  nua_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int NFS_UC_HASH_SZ ; 
 int /*<<< orphan*/  NFS_UC_QUEUED ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ ) ; 
 struct nfsrv_uc_arg* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ ,struct nfsrv_uc_arg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 struct nfsrv_uc_queue* nfsrv_uc_queue_tbl ; 
 int /*<<< orphan*/  nfsrv_uc_stop () ; 
 int /*<<< orphan*/  nua_svcq ; 

void
nfsrv_uc_cleanup(void)
{
	int i;

	DPRINT("Entering nfsrv_uc_cleanup\n");

	/*
	 * Every thing should be dequeued at this point or will be as sockets are closed
	 * but to be safe, we'll make sure.
	 */
	for (i = 0; i < NFS_UC_HASH_SZ; i++) {
		struct nfsrv_uc_queue *queue = &nfsrv_uc_queue_tbl[i];

		lck_mtx_lock(queue->ucq_lock);
		while (!TAILQ_EMPTY(queue->ucq_queue)) {
			struct nfsrv_uc_arg *ep = TAILQ_FIRST(queue->ucq_queue);
			TAILQ_REMOVE(queue->ucq_queue, ep, nua_svcq);
			ep->nua_flags &= ~NFS_UC_QUEUED;
		}
		lck_mtx_unlock(queue->ucq_lock);
	}

	nfsrv_uc_stop();
}