#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct nfsreq_secinfo_args {int dummy; } ;
struct nfsmount {scalar_t__ nm_stategenid; int /*<<< orphan*/  nm_minor_vers; } ;
struct nfsm_chain {int dummy; } ;
struct nfs_open_file {TYPE_6__* nof_owner; int /*<<< orphan*/  nof_stateid; } ;
struct nfs_lock_owner {scalar_t__ nlo_stategenid; int nlo_seqid; int /*<<< orphan*/  nlo_stateid; TYPE_6__* nlo_open_owner; } ;
struct nfs_file_lock {int nfl_flags; scalar_t__ nfl_type; int /*<<< orphan*/  nfl_end; int /*<<< orphan*/  nfl_start; struct nfs_lock_owner* nfl_owner; } ;
typedef  TYPE_2__* nfsnode_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_17__ {int noo_seqid; } ;
struct TYPE_15__ {int nva_flags; } ;
struct TYPE_16__ {int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_fhp; TYPE_1__ n_vattr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  EPROTO ; 
 scalar_t__ F_WRLCK ; 
 int /*<<< orphan*/  NFSPROC4_COMPOUND ; 
 int /*<<< orphan*/  NFSREQ_SECINFO_SET (struct nfsreq_secinfo_args*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int NFSX_UNSIGNED ; 
 int NFS_FFLAG_TRIGGER_REFERRAL ; 
 int NFS_FILE_LOCK_WAIT ; 
 int /*<<< orphan*/  NFS_LOCK_LENGTH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NFS_LOCK_TYPE_READ ; 
 int NFS_LOCK_TYPE_READW ; 
 int NFS_LOCK_TYPE_WRITE ; 
 int NFS_LOCK_TYPE_WRITEW ; 
 int NFS_OP_GETATTR ; 
 int NFS_OP_LOCK ; 
 int NFS_OP_PUTFH ; 
 int /*<<< orphan*/  NFS_VER4 ; 
 int R_NOINTR ; 
 int /*<<< orphan*/  nfs_getattr_bitmap ; 
 int /*<<< orphan*/  nfs_lock_owner_clear_busy (struct nfs_lock_owner*) ; 
 int nfs_lock_owner_set_busy (struct nfs_lock_owner*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_node_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_open_file_clear_busy (struct nfs_open_file*) ; 
 int nfs_open_file_set_busy (struct nfs_open_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_open_owner_clear_busy (TYPE_6__*) ; 
 int /*<<< orphan*/  nfs_open_owner_ref (TYPE_6__*) ; 
 int nfs_open_owner_set_busy (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_owner_seqid_increment (TYPE_6__*,struct nfs_lock_owner*,int) ; 
 int nfs_request2 (TYPE_2__*,int /*<<< orphan*/ *,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsreq_secinfo_args*,int,struct nfsm_chain*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nfsm_assert (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_64 (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_bitmap_supported (int,struct nfsm_chain*,int /*<<< orphan*/ ,struct nfsmount*,TYPE_2__*) ; 
 int /*<<< orphan*/  nfsm_chain_add_compound_header (int,struct nfsm_chain*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_lock_owner4 (int,struct nfsm_chain*,struct nfsmount*,struct nfs_lock_owner*) ; 
 int /*<<< orphan*/  nfsm_chain_add_stateid (int,struct nfsm_chain*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_get_stateid (int,struct nfsm_chain*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsm_chain_loadattr (int,struct nfsm_chain*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_op_check (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_skip_tag (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 

int
nfs4_setlock_rpc(
	nfsnode_t np,
	struct nfs_open_file *nofp,
	struct nfs_file_lock *nflp,
	int reclaim,
	int flags,
	thread_t thd,
	kauth_cred_t cred)
{
	struct nfs_lock_owner *nlop = nflp->nfl_owner;
	struct nfsmount *nmp;
	struct nfsm_chain nmreq, nmrep;
	uint64_t xid;
	uint32_t locktype;
	int error = 0, lockerror = ENOENT, newlocker, numops, status;
	struct nfsreq_secinfo_args si;

	nmp = NFSTONMP(np);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	if (np->n_vattr.nva_flags & NFS_FFLAG_TRIGGER_REFERRAL)
		return (EINVAL);

	newlocker = (nlop->nlo_stategenid != nmp->nm_stategenid);
	locktype = (nflp->nfl_flags & NFS_FILE_LOCK_WAIT) ?
			((nflp->nfl_type == F_WRLCK) ?
				NFS_LOCK_TYPE_WRITEW :
				NFS_LOCK_TYPE_READW) :
			((nflp->nfl_type == F_WRLCK) ?
				NFS_LOCK_TYPE_WRITE :
				NFS_LOCK_TYPE_READ);
	if (newlocker) {
		error = nfs_open_file_set_busy(nofp, thd);
		if (error)
			return (error);
		error = nfs_open_owner_set_busy(nofp->nof_owner, thd);
		if (error) {
			nfs_open_file_clear_busy(nofp);
			return (error);
		}
		if (!nlop->nlo_open_owner) {
			nfs_open_owner_ref(nofp->nof_owner);
			nlop->nlo_open_owner = nofp->nof_owner;
		}
	}
	error = nfs_lock_owner_set_busy(nlop, thd);
	if (error) {
		if (newlocker) {
			nfs_open_owner_clear_busy(nofp->nof_owner);
			nfs_open_file_clear_busy(nofp);
		}
		return (error);
	}

	NFSREQ_SECINFO_SET(&si, np, NULL, 0, NULL, 0);
	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	// PUTFH, GETATTR, LOCK
	numops = 3;
	nfsm_chain_build_alloc_init(error, &nmreq, 33 * NFSX_UNSIGNED);
	nfsm_chain_add_compound_header(error, &nmreq, "lock", nmp->nm_minor_vers, numops);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_PUTFH);
	nfsm_chain_add_fh(error, &nmreq, NFS_VER4, np->n_fhp, np->n_fhsize);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_GETATTR);
	nfsm_chain_add_bitmap_supported(error, &nmreq, nfs_getattr_bitmap, nmp, np);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_LOCK);
	nfsm_chain_add_32(error, &nmreq, locktype);
	nfsm_chain_add_32(error, &nmreq, reclaim);
	nfsm_chain_add_64(error, &nmreq, nflp->nfl_start);
	nfsm_chain_add_64(error, &nmreq, NFS_LOCK_LENGTH(nflp->nfl_start, nflp->nfl_end));
	nfsm_chain_add_32(error, &nmreq, newlocker);
	if (newlocker) {
		nfsm_chain_add_32(error, &nmreq, nofp->nof_owner->noo_seqid);
		nfsm_chain_add_stateid(error, &nmreq, &nofp->nof_stateid);
		nfsm_chain_add_32(error, &nmreq, nlop->nlo_seqid);
		nfsm_chain_add_lock_owner4(error, &nmreq, nmp, nlop);
	} else {
		nfsm_chain_add_stateid(error, &nmreq, &nlop->nlo_stateid);
		nfsm_chain_add_32(error, &nmreq, nlop->nlo_seqid);
	}
	nfsm_chain_build_done(error, &nmreq);
	nfsm_assert(error, (numops == 0), EPROTO);
	nfsmout_if(error);

	error = nfs_request2(np, NULL, &nmreq, NFSPROC4_COMPOUND, thd, cred, &si, flags|R_NOINTR, &nmrep, &xid, &status);

	if ((lockerror = nfs_node_lock(np)))
		error = lockerror;
	nfsm_chain_skip_tag(error, &nmrep);
	nfsm_chain_get_32(error, &nmrep, numops);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_PUTFH);
	nfsmout_if(error);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_GETATTR);
	nfsm_chain_loadattr(error, &nmrep, np, NFS_VER4, &xid);
	nfsmout_if(error);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_LOCK);
	nfs_owner_seqid_increment(newlocker ? nofp->nof_owner : NULL, nlop, error);
	nfsm_chain_get_stateid(error, &nmrep, &nlop->nlo_stateid);

	/* Update the lock owner's stategenid once it appears the server has state for it. */
	/* We determine this by noting the request was successful (we got a stateid). */
	if (newlocker && !error)
		nlop->nlo_stategenid = nmp->nm_stategenid;
nfsmout:
	if (!lockerror)
		nfs_node_unlock(np);
	nfs_lock_owner_clear_busy(nlop);
	if (newlocker) {
		nfs_open_owner_clear_busy(nofp->nof_owner);
		nfs_open_file_clear_busy(nofp);
	}
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);
	return (error);
}