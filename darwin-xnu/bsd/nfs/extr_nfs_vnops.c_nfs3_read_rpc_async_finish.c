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
typedef  int /*<<< orphan*/  uio_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct nfsreq {int dummy; } ;
struct nfsmount {int nm_vers; } ;
struct nfsm_chain {int dummy; } ;
typedef  int /*<<< orphan*/  nfsnode_t ;

/* Variables and functions */
 int EBADRPC ; 
 int EINPROGRESS ; 
 int ENXIO ; 
 size_t MIN (size_t,size_t) ; 
 struct nfsmount* NFSTONMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSX_UNSIGNED ; 
 int NFS_VER2 ; 
 int NFS_VER3 ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_node_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_node_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_request_async_cancel (struct nfsreq*) ; 
 int nfs_request_async_finish (struct nfsreq*,struct nfsm_chain*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nfsm_chain_adv (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,size_t) ; 
 int nfsm_chain_get_uio (struct nfsm_chain*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_loadattr (int,struct nfsm_chain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_postop_attr_update (int,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 

int
nfs3_read_rpc_async_finish(
	nfsnode_t np,
	struct nfsreq *req,
	uio_t uio,
	size_t *lenp,
	int *eofp)
{
	int error = 0, lockerror, nfsvers, status, eof = 0;
	size_t retlen = 0;
	uint64_t xid;
	struct nfsmount *nmp;
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
	if (nfsvers == NFS_VER3)
		nfsm_chain_postop_attr_update(error, &nmrep, np, &xid);
	if (!error)
		error = status;
	if (nfsvers == NFS_VER3) {
		nfsm_chain_adv(error, &nmrep, NFSX_UNSIGNED);
		nfsm_chain_get_32(error, &nmrep, eof);
	} else {
		nfsm_chain_loadattr(error, &nmrep, np, nfsvers, &xid);
	}
	if (!lockerror)
		nfs_node_unlock(np);
	nfsm_chain_get_32(error, &nmrep, retlen);
	if ((nfsvers == NFS_VER2) && (retlen > *lenp))
		error = EBADRPC;
	nfsmout_if(error);
	error = nfsm_chain_get_uio(&nmrep, MIN(retlen, *lenp), uio);
	if (eofp) {
		if (nfsvers == NFS_VER3) {
			if (!eof && !retlen)
				eof = 1;
		} else if (retlen < *lenp) {
			eof = 1;
		}
		*eofp = eof;
	}
	*lenp = MIN(retlen, *lenp);
nfsmout:
	nfsm_chain_cleanup(&nmrep);
	return (error);
}