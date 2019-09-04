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
typedef  int /*<<< orphan*/  thread_t ;
struct nfsreq_secinfo_args {int dummy; } ;
struct nfsreq_cbinfo {int dummy; } ;
struct nfsreq {int dummy; } ;
struct nfsmount {int nm_vers; int /*<<< orphan*/  nm_minor_vers; } ;
struct nfsm_chain {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  TYPE_2__* nfsnode_t ;
typedef  int /*<<< orphan*/  nfs_stateid ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_9__ {int nva_flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_fhp; TYPE_1__ n_vattr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  EPROTO ; 
 int /*<<< orphan*/  NFSPROC4_COMPOUND ; 
 int /*<<< orphan*/  NFSREQ_SECINFO_SET (struct nfsreq_secinfo_args*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int NFSX_UNSIGNED ; 
 int NFS_FFLAG_TRIGGER_REFERRAL ; 
 size_t NFS_OP_GETATTR ; 
 size_t NFS_OP_PUTFH ; 
 size_t NFS_OP_READ ; 
 int /*<<< orphan*/  nfs_get_stateid (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_getattr_bitmap ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_request_async (TYPE_2__*,int /*<<< orphan*/ *,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsreq_secinfo_args*,int /*<<< orphan*/ ,struct nfsreq_cbinfo*,struct nfsreq**) ; 
 int /*<<< orphan*/  nfsm_assert (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (int,struct nfsm_chain*,size_t) ; 
 int /*<<< orphan*/  nfsm_chain_add_64 (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_bitmap_supported (int,struct nfsm_chain*,int /*<<< orphan*/ ,struct nfsmount*,TYPE_2__*) ; 
 int /*<<< orphan*/  nfsm_chain_add_compound_header (int,struct nfsm_chain*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_stateid (int,struct nfsm_chain*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 

int
nfs4_read_rpc_async(
	nfsnode_t np,
	off_t offset,
	size_t len,
	thread_t thd,
	kauth_cred_t cred,
	struct nfsreq_cbinfo *cb,
	struct nfsreq **reqp)
{
	struct nfsmount *nmp;
	int error = 0, nfsvers, numops;
	nfs_stateid stateid;
	struct nfsm_chain nmreq;
	struct nfsreq_secinfo_args si;

	nmp = NFSTONMP(np);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	nfsvers = nmp->nm_vers;
	if (np->n_vattr.nva_flags & NFS_FFLAG_TRIGGER_REFERRAL)
		return (EINVAL);

	NFSREQ_SECINFO_SET(&si, np, NULL, 0, NULL, 0);
	nfsm_chain_null(&nmreq);

	// PUTFH, READ, GETATTR
	numops = 3;
	nfsm_chain_build_alloc_init(error, &nmreq, 22 * NFSX_UNSIGNED);
	nfsm_chain_add_compound_header(error, &nmreq, "read", nmp->nm_minor_vers, numops);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_PUTFH);
	nfsm_chain_add_fh(error, &nmreq, nfsvers, np->n_fhp, np->n_fhsize);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_READ);
	nfs_get_stateid(np, thd, cred, &stateid);
	nfsm_chain_add_stateid(error, &nmreq, &stateid);
	nfsm_chain_add_64(error, &nmreq, offset);
	nfsm_chain_add_32(error, &nmreq, len);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_GETATTR);
	nfsm_chain_add_bitmap_supported(error, &nmreq, nfs_getattr_bitmap, nmp, np);
	nfsm_chain_build_done(error, &nmreq);
	nfsm_assert(error, (numops == 0), EPROTO);
	nfsmout_if(error);
	error = nfs_request_async(np, NULL, &nmreq, NFSPROC4_COMPOUND, thd, cred, &si, 0, cb, reqp);
nfsmout:
	nfsm_chain_cleanup(&nmreq);
	return (error);
}