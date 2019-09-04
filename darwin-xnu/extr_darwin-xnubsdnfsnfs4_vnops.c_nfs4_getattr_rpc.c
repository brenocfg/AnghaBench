#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int /*<<< orphan*/  u_char ;
struct nfsreq_secinfo_args {int dummy; } ;
struct TYPE_9__ {int nfsa_flags; } ;
struct nfsmount {int nm_vers; int /*<<< orphan*/  nm_minor_vers; TYPE_1__ nm_fsattr; } ;
struct nfsm_chain {int dummy; } ;
struct nfs_vattr {int /*<<< orphan*/ * nva_acl; int /*<<< orphan*/ * nva_bitmap; } ;
typedef  TYPE_3__* nfsnode_t ;
typedef  scalar_t__ mount_t ;
struct TYPE_10__ {int nva_flags; } ;
struct TYPE_11__ {int /*<<< orphan*/  n_parent; TYPE_2__ n_vattr; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  EPROTO ; 
 int /*<<< orphan*/  NFSPROC4_COMPOUND ; 
 int /*<<< orphan*/  NFSREQ_SECINFO_SET (struct nfsreq_secinfo_args*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfsmount* NFSTONMP (TYPE_3__*) ; 
 int NFSX_UNSIGNED ; 
 int NFS_ATTR_BITMAP_LEN ; 
 int /*<<< orphan*/  NFS_BITMAP_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_BITMAP_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_COPY_ATTRIBUTES (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS_FATTR_ACL ; 
 int NFS_FFLAG_TRIGGER_REFERRAL ; 
 int NFS_FSFLAG_ACL ; 
 int /*<<< orphan*/  NFS_OP_GETATTR ; 
 int /*<<< orphan*/  NFS_OP_PUTFH ; 
 int NGA_ACL ; 
 int NGA_MONITOR ; 
 int NGA_SOFT ; 
 int R_RECOVER ; 
 int R_SOFT ; 
 struct nfsmount* VFSTONFS (scalar_t__) ; 
 int /*<<< orphan*/  VTONFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_default_attrs_for_referral_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nfs_vattr*,int /*<<< orphan*/ *) ; 
 int nfs4_parsefattr (struct nfsm_chain*,int /*<<< orphan*/ *,struct nfs_vattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_getattr_bitmap ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_request2 (TYPE_3__*,scalar_t__,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct nfsm_chain*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nfsm_assert (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_bitmap_supported (int,struct nfsm_chain*,int /*<<< orphan*/ *,struct nfsmount*,TYPE_3__*) ; 
 int /*<<< orphan*/  nfsm_chain_add_compound_header (int,struct nfsm_chain*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_op_check (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_skip_tag (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 

int
nfs4_getattr_rpc(
	nfsnode_t np,
	mount_t mp,
	u_char *fhp,
	size_t fhsize,
	int flags,
	vfs_context_t ctx,
	struct nfs_vattr *nvap,
	u_int64_t *xidp)
{
	struct nfsmount *nmp = mp ? VFSTONFS(mp) : NFSTONMP(np);
	int error = 0, status, nfsvers, numops, rpcflags = 0, acls;
	uint32_t bitmap[NFS_ATTR_BITMAP_LEN];
	struct nfsm_chain nmreq, nmrep;
	struct nfsreq_secinfo_args si;

	if (nfs_mount_gone(nmp))
		return (ENXIO);
	nfsvers = nmp->nm_vers;
	acls = (nmp->nm_fsattr.nfsa_flags & NFS_FSFLAG_ACL);

	if (np && (np->n_vattr.nva_flags & NFS_FFLAG_TRIGGER_REFERRAL)) {
		nfs4_default_attrs_for_referral_trigger(VTONFS(np->n_parent), NULL, 0, nvap, NULL);
		return (0);
	}

	if (flags & NGA_MONITOR) /* vnode monitor requests should be soft */
		rpcflags = R_RECOVER;

	if (flags & NGA_SOFT) /* Return ETIMEDOUT if server not responding */
		rpcflags |= R_SOFT;

	NFSREQ_SECINFO_SET(&si, np, NULL, 0, NULL, 0);
	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	// PUTFH, GETATTR
	numops = 2;
	nfsm_chain_build_alloc_init(error, &nmreq, 15 * NFSX_UNSIGNED);
	nfsm_chain_add_compound_header(error, &nmreq, "getattr", nmp->nm_minor_vers, numops);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_PUTFH);
	nfsm_chain_add_fh(error, &nmreq, nfsvers, fhp, fhsize);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_GETATTR);
	NFS_COPY_ATTRIBUTES(nfs_getattr_bitmap, bitmap);
	if ((flags & NGA_ACL) && acls)
		NFS_BITMAP_SET(bitmap, NFS_FATTR_ACL);
	nfsm_chain_add_bitmap_supported(error, &nmreq, bitmap, nmp, np);
	nfsm_chain_build_done(error, &nmreq);
	nfsm_assert(error, (numops == 0), EPROTO);
	nfsmout_if(error);
	error = nfs_request2(np, mp, &nmreq, NFSPROC4_COMPOUND, 
			vfs_context_thread(ctx), vfs_context_ucred(ctx),
			NULL, rpcflags, &nmrep, xidp, &status);

	nfsm_chain_skip_tag(error, &nmrep);
	nfsm_chain_get_32(error, &nmrep, numops);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_PUTFH);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_GETATTR);
	nfsmout_if(error);
	error = nfs4_parsefattr(&nmrep, NULL, nvap, NULL, NULL, NULL);
	nfsmout_if(error);
	if ((flags & NGA_ACL) && acls && !NFS_BITMAP_ISSET(nvap->nva_bitmap, NFS_FATTR_ACL)) {
		/* we asked for the ACL but didn't get one... assume there isn't one */
		NFS_BITMAP_SET(nvap->nva_bitmap, NFS_FATTR_ACL);
		nvap->nva_acl = NULL;
	}
nfsmout:
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);
	return (error);
}