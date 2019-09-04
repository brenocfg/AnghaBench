#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct nfsreq_secinfo_args {int dummy; } ;
struct nfsreq {int dummy; } ;
struct nfsmount {int /*<<< orphan*/  nm_mountp; int /*<<< orphan*/  nm_minor_vers; } ;
struct nfsm_chain {int dummy; } ;
struct nfs_fs_locations {int dummy; } ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_4__ {int n_fhsize; int /*<<< orphan*/ * n_fhp; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EPROTO ; 
 int /*<<< orphan*/  NFSPROC4_COMPOUND ; 
 int /*<<< orphan*/  NFSREQ_SECINFO_SET (struct nfsreq_secinfo_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ) ; 
 int NFSX_UNSIGNED ; 
 int NFS_ATTR_BITMAP_LEN ; 
 int /*<<< orphan*/  NFS_BITMAP_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_CLEAR_ATTRIBUTES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS_FATTR_FS_LOCATIONS ; 
 int /*<<< orphan*/  NFS_OP_GETATTR ; 
 int /*<<< orphan*/  NFS_OP_LOOKUP ; 
 int /*<<< orphan*/  NFS_OP_PUTFH ; 
 int /*<<< orphan*/  NFS_VER4 ; 
 int nfs4_parsefattr (struct nfsm_chain*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nfs_fs_locations*) ; 
 int nfs_request_async (TYPE_1__*,int /*<<< orphan*/ ,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsreq_secinfo_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfsreq**) ; 
 int nfs_request_async_finish (struct nfsreq*,struct nfsm_chain*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nfsm_assert (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_bitmap (int,struct nfsm_chain*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_compound_header (int,struct nfsm_chain*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_name (int,struct nfsm_chain*,char const*,int /*<<< orphan*/ ,struct nfsmount*) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_op_check (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_skip_tag (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 

int
nfs4_get_fs_locations(
	struct nfsmount *nmp,
	nfsnode_t dnp,
	u_char *fhp,
	int fhsize,
	const char *name,
	vfs_context_t ctx,
	struct nfs_fs_locations *nfslsp)
{
	int error = 0, numops, status;
	uint32_t bitmap[NFS_ATTR_BITMAP_LEN];
	struct nfsreq rq, *req = &rq;
	struct nfsreq_secinfo_args si;
	struct nfsm_chain nmreq, nmrep;
	uint64_t xid;

	if (!fhp && dnp) {
		fhp = dnp->n_fhp;
		fhsize = dnp->n_fhsize;
	}
	if (!fhp)
		return (EINVAL);

	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	NFSREQ_SECINFO_SET(&si, NULL, fhp, fhsize, name, 0);
	numops = 3;
	nfsm_chain_build_alloc_init(error, &nmreq, 18 * NFSX_UNSIGNED);
	nfsm_chain_add_compound_header(error, &nmreq, "fs_locations", nmp->nm_minor_vers, numops);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_PUTFH);
	nfsm_chain_add_fh(error, &nmreq, NFS_VER4, fhp, fhsize);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_LOOKUP);
	nfsm_chain_add_name(error, &nmreq, name, strlen(name), nmp);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_GETATTR);
	NFS_CLEAR_ATTRIBUTES(bitmap);
	NFS_BITMAP_SET(bitmap, NFS_FATTR_FS_LOCATIONS);
	nfsm_chain_add_bitmap(error, &nmreq, bitmap, NFS_ATTR_BITMAP_LEN);
	nfsm_chain_build_done(error, &nmreq);
	nfsm_assert(error, (numops == 0), EPROTO);
	nfsmout_if(error);
	error = nfs_request_async(dnp, nmp->nm_mountp, &nmreq, NFSPROC4_COMPOUND,
			vfs_context_thread(ctx), vfs_context_ucred(ctx), &si, 0, NULL, &req);
	if (!error)
		error = nfs_request_async_finish(req, &nmrep, &xid, &status);
	nfsm_chain_skip_tag(error, &nmrep);
	nfsm_chain_get_32(error, &nmrep, numops);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_PUTFH);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_LOOKUP);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_GETATTR);
	nfsmout_if(error);
	error = nfs4_parsefattr(&nmrep, NULL, NULL, NULL, NULL, nfslsp);
nfsmout:
	nfsm_chain_cleanup(&nmrep);
	nfsm_chain_cleanup(&nmreq);
	return (error);
}