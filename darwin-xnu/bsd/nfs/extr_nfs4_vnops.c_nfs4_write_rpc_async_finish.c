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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ u_int64_t ;
struct nfsreq {int dummy; } ;
struct nfsmount {int nm_vers; int nm_state; scalar_t__ nm_verf; int /*<<< orphan*/  nm_lock; } ;
struct nfsm_chain {int dummy; } ;
typedef  TYPE_2__* nfsnode_t ;
typedef  int /*<<< orphan*/  mount_t ;
struct TYPE_9__ {int nva_flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  n_lastio; TYPE_1__ n_vattr; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int ENOENT ; 
 int ENXIO ; 
 int MNT_ASYNC ; 
 int NFSERR_IO ; 
 int NFSSTA_HASWRITEVERF ; 
 int /*<<< orphan*/  NFSTOMP (TYPE_2__*) ; 
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int NFS_FFLAG_IS_ATTR ; 
 int /*<<< orphan*/  NFS_OP_GETATTR ; 
 int /*<<< orphan*/  NFS_OP_PUTFH ; 
 int /*<<< orphan*/  NFS_OP_WRITE ; 
 int NFS_WRITE_FILESYNC ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  microuptime (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_allow_async ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_node_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_request_async_cancel (struct nfsreq*) ; 
 int nfs_request_async_finish (struct nfsreq*,struct nfsm_chain*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_get_64 (int,struct nfsm_chain*,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_loadattr (int,struct nfsm_chain*,TYPE_2__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_op_check (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_skip_tag (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 int vfs_flags (int /*<<< orphan*/ ) ; 

int
nfs4_write_rpc_async_finish(
	nfsnode_t np,
	struct nfsreq *req,
	int *iomodep,
	size_t *rlenp,
	uint64_t *wverfp)
{
	struct nfsmount *nmp;
	int error = 0, lockerror = ENOENT, nfsvers, numops, status;
	int committed = NFS_WRITE_FILESYNC;
	size_t rlen = 0;
	u_int64_t xid, wverf;
	mount_t mp;
	struct nfsm_chain nmrep;

	nmp = NFSTONMP(np);
	if (nfs_mount_gone(nmp)) {
		nfs_request_async_cancel(req);
		return (ENXIO);
	}
	nfsvers = nmp->nm_vers;

	nfsm_chain_null(&nmrep);

	error = nfs_request_async_finish(req, &nmrep, &xid, &status);
	if (error == EINPROGRESS) /* async request restarted */
		return (error);
	nmp = NFSTONMP(np);
	if (nfs_mount_gone(nmp))
		error = ENXIO;
	if (!error && (lockerror = nfs_node_lock(np)))
		error = lockerror;
	nfsm_chain_skip_tag(error, &nmrep);
	nfsm_chain_get_32(error, &nmrep, numops);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_PUTFH);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_WRITE);
	nfsm_chain_get_32(error, &nmrep, rlen);
	nfsmout_if(error);
	*rlenp = rlen;
	if (rlen <= 0)
		error = NFSERR_IO;
	nfsm_chain_get_32(error, &nmrep, committed);
	nfsm_chain_get_64(error, &nmrep, wverf);
	nfsmout_if(error);
	if (wverfp)
		*wverfp = wverf;
	lck_mtx_lock(&nmp->nm_lock);
	if (!(nmp->nm_state & NFSSTA_HASWRITEVERF)) {
		nmp->nm_verf = wverf;
		nmp->nm_state |= NFSSTA_HASWRITEVERF;
	} else if (nmp->nm_verf != wverf) {
		nmp->nm_verf = wverf;
	}
	lck_mtx_unlock(&nmp->nm_lock);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_GETATTR);
	nfsm_chain_loadattr(error, &nmrep, np, nfsvers, &xid);
nfsmout:
	if (!lockerror)
		nfs_node_unlock(np);
	nfsm_chain_cleanup(&nmrep);
	if ((committed != NFS_WRITE_FILESYNC) && nfs_allow_async &&
	    ((mp = NFSTOMP(np))) && (vfs_flags(mp) & MNT_ASYNC))
		committed = NFS_WRITE_FILESYNC;
	*iomodep = committed;
	if (np->n_vattr.nva_flags & NFS_FFLAG_IS_ATTR)
		microuptime(&np->n_lastio);
	return (error);
}