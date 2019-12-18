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
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  scalar_t__ uint32_t ;
struct nfs_open_file {scalar_t__ nof_access; scalar_t__ nof_deny; int nof_rw; int nof_d_rw; scalar_t__ nof_w_dw; scalar_t__ nof_d_w_dw; scalar_t__ nof_w_drw; scalar_t__ nof_d_w_drw; int nof_opencnt; int nof_flags; TYPE_1__* nof_owner; int /*<<< orphan*/  nof_lock; scalar_t__ nof_d_rw_drw; scalar_t__ nof_rw_drw; scalar_t__ nof_d_r_drw; scalar_t__ nof_r_drw; scalar_t__ nof_d_rw_dw; scalar_t__ nof_rw_dw; scalar_t__ nof_d_r_dw; scalar_t__ nof_r_dw; int /*<<< orphan*/  nof_d_w; int /*<<< orphan*/  nof_w; int /*<<< orphan*/  nof_d_r; int /*<<< orphan*/  nof_r; scalar_t__ nof_mmap_deny; scalar_t__ nof_mmap_access; int /*<<< orphan*/  nof_creator; } ;
struct nfs_lock_owner {int dummy; } ;
typedef  int /*<<< orphan*/  nfsnode_t ;
struct TYPE_4__ {scalar_t__ nm_vers; } ;
struct TYPE_3__ {int /*<<< orphan*/  noo_cred; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int NFSERR_LOCKS_HELD ; 
 TYPE_2__* NFSTONMP (int /*<<< orphan*/ ) ; 
 int NFS_OPEN_FILE_CREATE ; 
 int NFS_OPEN_FILE_LOST ; 
 scalar_t__ NFS_OPEN_SHARE_ACCESS_BOTH ; 
 scalar_t__ NFS_OPEN_SHARE_ACCESS_WRITE ; 
 scalar_t__ NFS_OPEN_SHARE_DENY_NONE ; 
 scalar_t__ NFS_OPEN_SHARE_DENY_WRITE ; 
 scalar_t__ NFS_VER4 ; 
 int /*<<< orphan*/  NP (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_claim_delegated_state_for_open_file (struct nfs_open_file*,int /*<<< orphan*/ ) ; 
 int nfs4_close_rpc (int /*<<< orphan*/ ,struct nfs_open_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs4_open_downgrade_rpc (int /*<<< orphan*/ ,struct nfs_open_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_unlock_rpc (int /*<<< orphan*/ ,struct nfs_lock_owner*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfs_lock_owner* nfs_lock_owner_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_lock_owner_rele (struct nfs_lock_owner*) ; 
 int /*<<< orphan*/  nfs_open_file_add_open (struct nfs_open_file*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  nfs_open_file_remove_open (struct nfs_open_file*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nfs_open_file_remove_open_find (struct nfs_open_file*,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  nfs_wait_bufs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 

int
nfs_close(
	nfsnode_t np,
	struct nfs_open_file *nofp,
	uint32_t accessMode,
	uint32_t denyMode,
	vfs_context_t ctx)
{
	struct nfs_lock_owner *nlop;
	int error = 0, changed = 0, delegated = 0, closed = 0, downgrade = 0;
	uint32_t newAccessMode, newDenyMode;
	
	/* warn if modes don't match current state */
	if (((accessMode & nofp->nof_access) != accessMode) || ((denyMode & nofp->nof_deny) != denyMode))
		NP(np, "nfs_close: mode mismatch %d %d, current %d %d, %d",
			accessMode, denyMode, nofp->nof_access, nofp->nof_deny,
			kauth_cred_getuid(nofp->nof_owner->noo_cred));

	/*
	 * If we're closing a write-only open, we may not have a write-only count
	 * if we also grabbed read access.  So, check the read-write count.
	 */
	if (denyMode == NFS_OPEN_SHARE_DENY_NONE) {
		if ((accessMode == NFS_OPEN_SHARE_ACCESS_WRITE) &&
		    (nofp->nof_w == 0) && (nofp->nof_d_w == 0) &&
		    (nofp->nof_rw || nofp->nof_d_rw))
			accessMode = NFS_OPEN_SHARE_ACCESS_BOTH;
	} else if (denyMode == NFS_OPEN_SHARE_DENY_WRITE) {
		if ((accessMode == NFS_OPEN_SHARE_ACCESS_WRITE) &&
		    (nofp->nof_w_dw == 0) && (nofp->nof_d_w_dw == 0) &&
		    (nofp->nof_rw_dw || nofp->nof_d_rw_dw))
			accessMode = NFS_OPEN_SHARE_ACCESS_BOTH;
	} else { /* NFS_OPEN_SHARE_DENY_BOTH */
		if ((accessMode == NFS_OPEN_SHARE_ACCESS_WRITE) &&
		    (nofp->nof_w_drw == 0) && (nofp->nof_d_w_drw == 0) &&
		    (nofp->nof_rw_drw || nofp->nof_d_rw_drw))
			accessMode = NFS_OPEN_SHARE_ACCESS_BOTH;
	}

	nfs_open_file_remove_open_find(nofp, accessMode, denyMode, &newAccessMode, &newDenyMode, &delegated);
	if ((newAccessMode != nofp->nof_access) || (newDenyMode != nofp->nof_deny))
		changed = 1;
	else
		changed = 0;

	if (NFSTONMP(np)->nm_vers < NFS_VER4) /* NFS v2/v3 closes simply need to remove the open. */
		goto v3close;

	if ((newAccessMode == 0) || (nofp->nof_opencnt == 1)) {
		/*
		 * No more access after this close, so clean up and close it.
		 * Don't send a close RPC if we're closing a delegated open.
		 */
		nfs_wait_bufs(np);
		closed = 1;
		if (!delegated && !(nofp->nof_flags & NFS_OPEN_FILE_LOST))
			error = nfs4_close_rpc(np, nofp, vfs_context_thread(ctx), vfs_context_ucred(ctx), 0);
		if (error == NFSERR_LOCKS_HELD) {
			/*
			 * Hmm... the server says we have locks we need to release first
			 * Find the lock owner and try to unlock everything.
			 */
			nlop = nfs_lock_owner_find(np, vfs_context_proc(ctx), 0);
			if (nlop) {
				nfs4_unlock_rpc(np, nlop, F_WRLCK, 0, UINT64_MAX,
					0, vfs_context_thread(ctx), vfs_context_ucred(ctx));
				nfs_lock_owner_rele(nlop);
			}
			error = nfs4_close_rpc(np, nofp, vfs_context_thread(ctx), vfs_context_ucred(ctx), 0);
		}
	} else if (changed) {
		/*
		 * File is still open but with less access, so downgrade the open.
		 * Don't send a downgrade RPC if we're closing a delegated open.
		 */
		if (!delegated && !(nofp->nof_flags & NFS_OPEN_FILE_LOST)) {
			downgrade = 1;
			/*
			 * If we have delegated opens, we should probably claim them before sending
			 * the downgrade because the server may not know the open we are downgrading to.
			 */
			if (nofp->nof_d_rw_drw || nofp->nof_d_w_drw || nofp->nof_d_r_drw ||
			    nofp->nof_d_rw_dw || nofp->nof_d_w_dw || nofp->nof_d_r_dw ||
			    nofp->nof_d_rw || nofp->nof_d_w || nofp->nof_d_r)
				nfs4_claim_delegated_state_for_open_file(nofp, 0);
			/* need to remove the open before sending the downgrade */
			nfs_open_file_remove_open(nofp, accessMode, denyMode);
			error = nfs4_open_downgrade_rpc(np, nofp, ctx);
			if (error) /* Hmm.. that didn't work. Add the open back in. */
				nfs_open_file_add_open(nofp, accessMode, denyMode, delegated);
		}
	}

	if (error) {
		NP(np, "nfs_close: error %d, %d", error, kauth_cred_getuid(nofp->nof_owner->noo_cred));
		return (error);
	}

v3close:
	if (!downgrade)
		nfs_open_file_remove_open(nofp, accessMode, denyMode);

	if (closed) {
		lck_mtx_lock(&nofp->nof_lock);
		if (nofp->nof_r || nofp->nof_d_r || nofp->nof_w || nofp->nof_d_w || nofp->nof_d_rw ||
		    (nofp->nof_rw && !((nofp->nof_flags & NFS_OPEN_FILE_CREATE) && !nofp->nof_creator && (nofp->nof_rw == 1))) ||
		    nofp->nof_r_dw || nofp->nof_d_r_dw || nofp->nof_w_dw || nofp->nof_d_w_dw ||
		    nofp->nof_rw_dw || nofp->nof_d_rw_dw || nofp->nof_r_drw || nofp->nof_d_r_drw ||
		    nofp->nof_w_drw || nofp->nof_d_w_drw || nofp->nof_rw_drw || nofp->nof_d_rw_drw)
			NP(np, "nfs_close: unexpected count: %u.%u %u.%u %u.%u dw %u.%u %u.%u %u.%u drw %u.%u %u.%u %u.%u flags 0x%x, %d",
				nofp->nof_r, nofp->nof_d_r, nofp->nof_w, nofp->nof_d_w,
				nofp->nof_rw, nofp->nof_d_rw, nofp->nof_r_dw, nofp->nof_d_r_dw,
				nofp->nof_w_dw, nofp->nof_d_w_dw, nofp->nof_rw_dw, nofp->nof_d_rw_dw,
				nofp->nof_r_drw, nofp->nof_d_r_drw, nofp->nof_w_drw, nofp->nof_d_w_drw,
				nofp->nof_rw_drw, nofp->nof_d_rw_drw, nofp->nof_flags,
				kauth_cred_getuid(nofp->nof_owner->noo_cred));
		/* clear out all open info, just to be safe */
		nofp->nof_access = nofp->nof_deny = 0;
		nofp->nof_mmap_access = nofp->nof_mmap_deny = 0;
		nofp->nof_r = nofp->nof_d_r = 0;
		nofp->nof_w = nofp->nof_d_w = 0;
		nofp->nof_rw = nofp->nof_d_rw = 0;
		nofp->nof_r_dw = nofp->nof_d_r_dw = 0;
		nofp->nof_w_dw = nofp->nof_d_w_dw = 0;
		nofp->nof_rw_dw = nofp->nof_d_rw_dw = 0;
		nofp->nof_r_drw = nofp->nof_d_r_drw = 0;
		nofp->nof_w_drw = nofp->nof_d_w_drw = 0;
		nofp->nof_rw_drw = nofp->nof_d_rw_drw = 0;
		nofp->nof_flags &= ~NFS_OPEN_FILE_CREATE;
		lck_mtx_unlock(&nofp->nof_lock);
		/* XXX we may potentially want to clean up idle/unused open file structures */
	}
	if (nofp->nof_flags & NFS_OPEN_FILE_LOST) {
		error = EIO;
		NP(np, "nfs_close: LOST%s, %d", !nofp->nof_opencnt ? " (last)" : "",
			kauth_cred_getuid(nofp->nof_owner->noo_cred));
	}
		
	return (error);
}