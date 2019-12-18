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
struct nfsreq {int r_flags; struct nfsmount* r_nmp; } ;
struct nfsmount {int /*<<< orphan*/  nm_lock; int /*<<< orphan*/  nm_resendq; } ;

/* Variables and functions */
 int R_RESENDQ ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct nfsreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_gss_clnt_rpcdone (struct nfsreq*) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int /*<<< orphan*/  nfs_mount_sock_thread_wake (struct nfsmount*) ; 
 int /*<<< orphan*/  nfs_request_ref (struct nfsreq*,int) ; 
 int /*<<< orphan*/  r_rchain ; 

void
nfs_asyncio_resend(struct nfsreq *req)
{
	struct nfsmount *nmp = req->r_nmp;

	if (nfs_mount_gone(nmp))
		return;

	nfs_gss_clnt_rpcdone(req);
	lck_mtx_lock(&nmp->nm_lock);
	if (!(req->r_flags & R_RESENDQ)) {
		TAILQ_INSERT_TAIL(&nmp->nm_resendq, req, r_rchain);
		req->r_flags |= R_RESENDQ;
		/*
		 * We take a reference on this request so that it can't be
		 * destroyed while a resend is queued or in progress.
		 */
		nfs_request_ref(req, 1);
	}
	nfs_mount_sock_thread_wake(nmp);
	lck_mtx_unlock(&nmp->nm_lock);
}