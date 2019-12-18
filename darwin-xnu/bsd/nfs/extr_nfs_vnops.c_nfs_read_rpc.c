#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  scalar_t__ user_ssize_t ;
typedef  int /*<<< orphan*/  uio_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct nfsreq {int dummy; } ;
struct nfsmount {int nm_vers; size_t nm_rsize; scalar_t__ nm_stategenid; int /*<<< orphan*/  nm_state; int /*<<< orphan*/  nm_lock; TYPE_1__* nm_funcs; } ;
typedef  scalar_t__ off_t ;
typedef  TYPE_2__* nfsnode_t ;
struct TYPE_12__ {int n_flag; } ;
struct TYPE_11__ {int (* nf_read_rpc_async ) (TYPE_2__*,scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfsreq**) ;int (* nf_read_rpc_async_finish ) (TYPE_2__*,struct nfsreq*,int /*<<< orphan*/ ,size_t*,int*) ;} ;

/* Variables and functions */
 int EFBIG ; 
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  FSDBG (int,TYPE_2__*,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSDBG_BOT (int,TYPE_2__*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  FSDBG_TOP (int,TYPE_2__*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int NFSERR_GRACE ; 
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int NFS_VER2 ; 
 int NFS_VER4 ; 
 int /*<<< orphan*/  NP (TYPE_2__*,char*,int) ; 
 int NREVOKE ; 
 scalar_t__ PZERO ; 
 int hz ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 scalar_t__ nfs_mount_state_error_should_restart (int) ; 
 scalar_t__ nfs_mount_state_max_restarts (struct nfsmount*) ; 
 int nfs_mount_state_wait_for_recovery (struct nfsmount*) ; 
 int /*<<< orphan*/  nfs_need_recover (struct nfsmount*,int) ; 
 int stub1 (TYPE_2__*,scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfsreq**) ; 
 int stub2 (TYPE_2__*,struct nfsreq*,int /*<<< orphan*/ ,size_t*,int*) ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ *,scalar_t__,char*,int) ; 
 int uio_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ uio_resid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 

int
nfs_read_rpc(nfsnode_t np, uio_t uio, vfs_context_t ctx)
{
	struct nfsmount *nmp;
	int error = 0, nfsvers, eof = 0;
	size_t nmrsize, len, retlen;
	user_ssize_t tsiz;
	off_t txoffset;
	struct nfsreq rq, *req = &rq;
	uint32_t stategenid = 0, restart = 0;

	FSDBG_TOP(536, np, uio_offset(uio), uio_resid(uio), 0);
	nmp = NFSTONMP(np);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	nfsvers = nmp->nm_vers;
	nmrsize = nmp->nm_rsize;

	txoffset = uio_offset(uio);
	tsiz = uio_resid(uio);
	if ((nfsvers == NFS_VER2) && ((uint64_t)(txoffset + tsiz) > 0xffffffffULL)) {
		FSDBG_BOT(536, np, uio_offset(uio), uio_resid(uio), EFBIG);
		return (EFBIG);
	}

	while (tsiz > 0) {
		len = retlen = (tsiz > (user_ssize_t)nmrsize) ? nmrsize : (size_t)tsiz;
		FSDBG(536, np, txoffset, len, 0);
		if (np->n_flag & NREVOKE) {
			error = EIO;
			break;
		}
		if (nmp->nm_vers >= NFS_VER4)
			stategenid = nmp->nm_stategenid;
		error = nmp->nm_funcs->nf_read_rpc_async(np, txoffset, len,
				vfs_context_thread(ctx), vfs_context_ucred(ctx), NULL, &req);
		if (!error)
			error = nmp->nm_funcs->nf_read_rpc_async_finish(np, req, uio, &retlen, &eof);
		if ((nmp->nm_vers >= NFS_VER4) && nfs_mount_state_error_should_restart(error) &&
		    (++restart <= nfs_mount_state_max_restarts(nmp))) { /* guard against no progress */
			lck_mtx_lock(&nmp->nm_lock);
			if ((error != NFSERR_GRACE) && (stategenid == nmp->nm_stategenid)) {
				NP(np, "nfs_read_rpc: error %d, initiating recovery", error);
				nfs_need_recover(nmp, error);
			}
			lck_mtx_unlock(&nmp->nm_lock);
			if (np->n_flag & NREVOKE) {
				error = EIO;
			} else {
				if (error == NFSERR_GRACE)
					tsleep(&nmp->nm_state, (PZERO-1), "nfsgrace", 2*hz);
				if (!(error = nfs_mount_state_wait_for_recovery(nmp)))
					continue;
			}
		}
		if (error)
			break;
		txoffset += retlen;
		tsiz -= retlen;
		if (nfsvers != NFS_VER2) {
			if (eof || (retlen == 0))
				tsiz = 0;
		} else if (retlen < len)
			tsiz = 0;
	}

	FSDBG_BOT(536, np, eof, uio_resid(uio), error);
	return (error);
}