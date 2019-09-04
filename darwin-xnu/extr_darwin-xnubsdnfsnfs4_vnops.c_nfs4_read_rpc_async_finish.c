#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uio_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
struct nfsreq {int dummy; } ;
struct nfsmount {int nm_vers; } ;
struct nfsm_chain {int dummy; } ;
typedef  TYPE_2__* nfsnode_t ;
struct TYPE_8__ {int nva_flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  n_lastio; TYPE_1__ n_vattr; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int ENXIO ; 
 size_t MIN (size_t,size_t) ; 
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int NFS_FFLAG_IS_ATTR ; 
 int /*<<< orphan*/  NFS_OP_GETATTR ; 
 int /*<<< orphan*/  NFS_OP_PUTFH ; 
 int /*<<< orphan*/  NFS_OP_READ ; 
 int /*<<< orphan*/  microuptime (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_node_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_request_async_cancel (struct nfsreq*) ; 
 int nfs_request_async_finish (struct nfsreq*,struct nfsm_chain*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,size_t) ; 
 int nfsm_chain_get_uio (struct nfsm_chain*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_loadattr (int,struct nfsm_chain*,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_op_check (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_skip_tag (int,struct nfsm_chain*) ; 

int
nfs4_read_rpc_async_finish(
	nfsnode_t np,
	struct nfsreq *req,
	uio_t uio,
	size_t *lenp,
	int *eofp)
{
	struct nfsmount *nmp;
	int error = 0, lockerror, nfsvers, numops, status, eof = 0;
	size_t retlen = 0;
	u_int64_t xid;
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

	if ((lockerror = nfs_node_lock(np)))
		error = lockerror;
	nfsm_chain_skip_tag(error, &nmrep);
	nfsm_chain_get_32(error, &nmrep, numops);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_PUTFH);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_READ);
	nfsm_chain_get_32(error, &nmrep, eof);
	nfsm_chain_get_32(error, &nmrep, retlen);
	if (!error) {
		*lenp = MIN(retlen, *lenp);
		error = nfsm_chain_get_uio(&nmrep, *lenp, uio);
	}
	nfsm_chain_op_check(error, &nmrep, NFS_OP_GETATTR);
	nfsm_chain_loadattr(error, &nmrep, np, nfsvers, &xid);
	if (!lockerror)
		nfs_node_unlock(np);
	if (eofp) {
		if (!eof && !retlen)
			eof = 1;
		*eofp = eof;
	}
	nfsm_chain_cleanup(&nmrep);
	if (np->n_vattr.nva_flags & NFS_FFLAG_IS_ATTR)
		microuptime(&np->n_lastio);
	return (error);
}