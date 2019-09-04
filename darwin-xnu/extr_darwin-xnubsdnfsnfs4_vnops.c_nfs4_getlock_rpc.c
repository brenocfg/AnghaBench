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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct nfsreq_secinfo_args {int dummy; } ;
struct nfsmount {int /*<<< orphan*/  nm_minor_vers; } ;
struct nfsm_chain {int dummy; } ;
struct nfs_lock_owner {int dummy; } ;
struct flock {scalar_t__ l_type; scalar_t__ l_start; int /*<<< orphan*/  l_whence; scalar_t__ l_pid; scalar_t__ l_len; } ;
typedef  TYPE_2__* nfsnode_t ;
struct TYPE_11__ {int nva_flags; } ;
struct TYPE_12__ {int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_fhp; TYPE_1__ n_vattr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  EPROTO ; 
 scalar_t__ F_RDLCK ; 
 scalar_t__ F_UNLCK ; 
 scalar_t__ F_WRLCK ; 
 int NFSERR_DENIED ; 
 int /*<<< orphan*/  NFSPROC4_COMPOUND ; 
 int /*<<< orphan*/  NFSREQ_SECINFO_SET (struct nfsreq_secinfo_args*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int NFSX_UNSIGNED ; 
 int NFS_FFLAG_TRIGGER_REFERRAL ; 
 scalar_t__ NFS_LOCK_LENGTH (scalar_t__,scalar_t__) ; 
 int NFS_LOCK_TYPE_READ ; 
 int NFS_LOCK_TYPE_WRITE ; 
 int NFS_OP_GETATTR ; 
 int NFS_OP_LOCKT ; 
 int NFS_OP_PUTFH ; 
 int /*<<< orphan*/  NFS_VER4 ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  nfs_getattr_bitmap ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_node_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 int nfs_request (TYPE_2__*,int /*<<< orphan*/ *,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsreq_secinfo_args*,struct nfsm_chain*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  nfsm_assert (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_64 (int,struct nfsm_chain*,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_add_bitmap_supported (int,struct nfsm_chain*,int /*<<< orphan*/ ,struct nfsmount*,TYPE_2__*) ; 
 int /*<<< orphan*/  nfsm_chain_add_compound_header (int,struct nfsm_chain*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_lock_owner4 (int,struct nfsm_chain*,struct nfsmount*,struct nfs_lock_owner*) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_get_64 (int,struct nfsm_chain*,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_loadattr (int,struct nfsm_chain*,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_op_check (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_skip_tag (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 

int
nfs4_getlock_rpc(
	nfsnode_t np,
	struct nfs_lock_owner *nlop,
	struct flock *fl,
	uint64_t start,
	uint64_t end,
	vfs_context_t ctx)
{
	struct nfsmount *nmp;
	struct nfsm_chain nmreq, nmrep;
	uint64_t xid, val64 = 0;
	uint32_t val = 0;
	int error = 0, lockerror, numops, status;
	struct nfsreq_secinfo_args si;

	nmp = NFSTONMP(np);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	if (np->n_vattr.nva_flags & NFS_FFLAG_TRIGGER_REFERRAL)
		return (EINVAL);

	lockerror = ENOENT;
	NFSREQ_SECINFO_SET(&si, np, NULL, 0, NULL, 0);
	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	// PUTFH, GETATTR, LOCKT
	numops = 3;
	nfsm_chain_build_alloc_init(error, &nmreq, 26 * NFSX_UNSIGNED);
	nfsm_chain_add_compound_header(error, &nmreq, "locktest", nmp->nm_minor_vers, numops);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_PUTFH);
	nfsm_chain_add_fh(error, &nmreq, NFS_VER4, np->n_fhp, np->n_fhsize);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_GETATTR);
	nfsm_chain_add_bitmap_supported(error, &nmreq, nfs_getattr_bitmap, nmp, np);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_LOCKT);
	nfsm_chain_add_32(error, &nmreq, (fl->l_type == F_WRLCK) ? NFS_LOCK_TYPE_WRITE : NFS_LOCK_TYPE_READ);
	nfsm_chain_add_64(error, &nmreq, start);
	nfsm_chain_add_64(error, &nmreq, NFS_LOCK_LENGTH(start, end));
	nfsm_chain_add_lock_owner4(error, &nmreq, nmp, nlop);
	nfsm_chain_build_done(error, &nmreq);
	nfsm_assert(error, (numops == 0), EPROTO);
	nfsmout_if(error);

	error = nfs_request(np, NULL, &nmreq, NFSPROC4_COMPOUND, ctx, &si, &nmrep, &xid, &status);

	if ((lockerror = nfs_node_lock(np)))
		error = lockerror;
	nfsm_chain_skip_tag(error, &nmrep);
	nfsm_chain_get_32(error, &nmrep, numops);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_PUTFH);
	nfsmout_if(error);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_GETATTR);
	nfsm_chain_loadattr(error, &nmrep, np, NFS_VER4, &xid);
	nfsmout_if(error);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_LOCKT);
	if (error == NFSERR_DENIED) {
		error = 0;
		nfsm_chain_get_64(error, &nmrep, fl->l_start);
		nfsm_chain_get_64(error, &nmrep, val64);
		fl->l_len = (val64 == UINT64_MAX) ? 0 : val64;
		nfsm_chain_get_32(error, &nmrep, val);
		fl->l_type = (val == NFS_LOCK_TYPE_WRITE) ? F_WRLCK : F_RDLCK;
		fl->l_pid = 0;
		fl->l_whence = SEEK_SET;
	} else if (!error) {
		fl->l_type = F_UNLCK;
	}
nfsmout:
	if (!lockerror)
		nfs_node_unlock(np);
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);
	return (error);
}