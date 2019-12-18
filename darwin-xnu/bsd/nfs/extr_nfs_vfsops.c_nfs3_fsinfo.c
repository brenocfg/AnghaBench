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
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
struct TYPE_8__ {int nfsa_maxread; int nfsa_maxwrite; int /*<<< orphan*/  nfsa_bitmap; int /*<<< orphan*/  nfsa_flags; int /*<<< orphan*/  nfsa_maxfilesize; } ;
struct nfsmount {int nm_rsize; int nm_wsize; int nm_readdirsize; int /*<<< orphan*/  nm_lock; TYPE_1__ nm_fsattr; int /*<<< orphan*/  nm_state; int /*<<< orphan*/  nm_vers; } ;
struct nfsm_chain {int dummy; } ;
typedef  TYPE_2__* nfsnode_t ;
struct TYPE_9__ {int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_fhp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSPROC_FSINFO ; 
 int /*<<< orphan*/  NFSSTA_GOTFSINFO ; 
 int NFSV3FSINFO_CANSETTIME ; 
 int NFSV3FSINFO_HOMOGENEOUS ; 
 int NFSV3FSINFO_LINK ; 
 int NFSV3FSINFO_SYMLINK ; 
 int /*<<< orphan*/  NFSX_FH (int /*<<< orphan*/ ) ; 
 int NFSX_UNSIGNED ; 
 int /*<<< orphan*/  NFS_BITMAP_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NFS_FABLKSIZE ; 
 int /*<<< orphan*/  NFS_FATTR_CANSETTIME ; 
 int /*<<< orphan*/  NFS_FATTR_HOMOGENEOUS ; 
 int /*<<< orphan*/  NFS_FATTR_LINK_SUPPORT ; 
 int /*<<< orphan*/  NFS_FATTR_MAXFILESIZE ; 
 int /*<<< orphan*/  NFS_FATTR_MAXREAD ; 
 int /*<<< orphan*/  NFS_FATTR_MAXWRITE ; 
 int /*<<< orphan*/  NFS_FATTR_SYMLINK_SUPPORT ; 
 int /*<<< orphan*/  NFS_FSFLAG_HOMOGENEOUS ; 
 int /*<<< orphan*/  NFS_FSFLAG_LINK ; 
 int /*<<< orphan*/  NFS_FSFLAG_SET_TIME ; 
 int /*<<< orphan*/  NFS_FSFLAG_SYMLINK ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int nfs_node_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 int nfs_request (TYPE_2__*,int /*<<< orphan*/ *,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfsm_chain*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_adv (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_get_64 (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_postop_attr_update (int,struct nfsm_chain*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 

int
nfs3_fsinfo(struct nfsmount *nmp, nfsnode_t np, vfs_context_t ctx)
{
	int error = 0, lockerror, status, nmlocked = 0;
	u_int64_t xid;
	uint32_t val, prefsize, maxsize;
	struct nfsm_chain nmreq, nmrep;

	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	nfsm_chain_build_alloc_init(error, &nmreq, NFSX_FH(nmp->nm_vers));
	nfsm_chain_add_fh(error, &nmreq, nmp->nm_vers, np->n_fhp, np->n_fhsize);
	nfsm_chain_build_done(error, &nmreq);
	nfsmout_if(error);
	error = nfs_request(np, NULL, &nmreq, NFSPROC_FSINFO, ctx, NULL, &nmrep, &xid, &status);
	if ((lockerror = nfs_node_lock(np)))
		error = lockerror;
	nfsm_chain_postop_attr_update(error, &nmrep, np, &xid);
	if (!lockerror)
		nfs_node_unlock(np);
	if (!error)
		error = status;
	nfsmout_if(error);

	lck_mtx_lock(&nmp->nm_lock);
	nmlocked = 1;

	nfsm_chain_get_32(error, &nmrep, maxsize);
	nfsm_chain_get_32(error, &nmrep, prefsize);
	nfsmout_if(error);
	nmp->nm_fsattr.nfsa_maxread = maxsize;
	if (prefsize < nmp->nm_rsize)
		nmp->nm_rsize = (prefsize + NFS_FABLKSIZE - 1) &
			~(NFS_FABLKSIZE - 1);
	if ((maxsize > 0) && (maxsize < nmp->nm_rsize)) {
		nmp->nm_rsize = maxsize & ~(NFS_FABLKSIZE - 1);
		if (nmp->nm_rsize == 0)
			nmp->nm_rsize = maxsize;
	}
	nfsm_chain_adv(error, &nmrep, NFSX_UNSIGNED); // skip rtmult

	nfsm_chain_get_32(error, &nmrep, maxsize);
	nfsm_chain_get_32(error, &nmrep, prefsize);
	nfsmout_if(error);
	nmp->nm_fsattr.nfsa_maxwrite = maxsize;
	if (prefsize < nmp->nm_wsize)
		nmp->nm_wsize = (prefsize + NFS_FABLKSIZE - 1) &
			~(NFS_FABLKSIZE - 1);
	if ((maxsize > 0) && (maxsize < nmp->nm_wsize)) {
		nmp->nm_wsize = maxsize & ~(NFS_FABLKSIZE - 1);
		if (nmp->nm_wsize == 0)
			nmp->nm_wsize = maxsize;
	}
	nfsm_chain_adv(error, &nmrep, NFSX_UNSIGNED); // skip wtmult

	nfsm_chain_get_32(error, &nmrep, prefsize);
	nfsmout_if(error);
	if ((prefsize > 0) && (prefsize < nmp->nm_readdirsize))
		nmp->nm_readdirsize = prefsize;
	if ((nmp->nm_fsattr.nfsa_maxread > 0) &&
	    (nmp->nm_fsattr.nfsa_maxread < nmp->nm_readdirsize))
		nmp->nm_readdirsize = nmp->nm_fsattr.nfsa_maxread;

	nfsm_chain_get_64(error, &nmrep, nmp->nm_fsattr.nfsa_maxfilesize);

	nfsm_chain_adv(error, &nmrep, 2 * NFSX_UNSIGNED); // skip time_delta

	/* convert FS properties to our own flags */
	nfsm_chain_get_32(error, &nmrep, val);
	nfsmout_if(error);
	if (val & NFSV3FSINFO_LINK)
		nmp->nm_fsattr.nfsa_flags |= NFS_FSFLAG_LINK;
	if (val & NFSV3FSINFO_SYMLINK)
		nmp->nm_fsattr.nfsa_flags |= NFS_FSFLAG_SYMLINK;
	if (val & NFSV3FSINFO_HOMOGENEOUS)
		nmp->nm_fsattr.nfsa_flags |= NFS_FSFLAG_HOMOGENEOUS;
	if (val & NFSV3FSINFO_CANSETTIME)
		nmp->nm_fsattr.nfsa_flags |= NFS_FSFLAG_SET_TIME;
	nmp->nm_state |= NFSSTA_GOTFSINFO;
	NFS_BITMAP_SET(nmp->nm_fsattr.nfsa_bitmap, NFS_FATTR_MAXREAD);
	NFS_BITMAP_SET(nmp->nm_fsattr.nfsa_bitmap, NFS_FATTR_MAXWRITE);
	NFS_BITMAP_SET(nmp->nm_fsattr.nfsa_bitmap, NFS_FATTR_MAXFILESIZE);
	NFS_BITMAP_SET(nmp->nm_fsattr.nfsa_bitmap, NFS_FATTR_LINK_SUPPORT);
	NFS_BITMAP_SET(nmp->nm_fsattr.nfsa_bitmap, NFS_FATTR_SYMLINK_SUPPORT);
	NFS_BITMAP_SET(nmp->nm_fsattr.nfsa_bitmap, NFS_FATTR_HOMOGENEOUS);
	NFS_BITMAP_SET(nmp->nm_fsattr.nfsa_bitmap, NFS_FATTR_CANSETTIME);
nfsmout:
	if (nmlocked)
		lck_mtx_unlock(&nmp->nm_lock);
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);
	return (error);
}