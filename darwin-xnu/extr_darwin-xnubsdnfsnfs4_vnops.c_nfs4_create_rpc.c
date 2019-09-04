#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
struct vnode_attr {int /*<<< orphan*/  va_rdev; } ;
struct nfsreq_secinfo_args {int dummy; } ;
struct nfsreq {int /*<<< orphan*/  r_auth; } ;
struct TYPE_31__ {int nfsa_flags; } ;
struct nfsmount {int nm_vers; int /*<<< orphan*/  nm_minor_vers; TYPE_1__ nm_fsattr; } ;
struct nfsm_chain {int dummy; } ;
struct nfs_vattr {int /*<<< orphan*/  nva_bitmap; } ;
struct nfs_dulookup {int dummy; } ;
struct componentname {char* cn_nameptr; int /*<<< orphan*/  cn_namelen; } ;
typedef  TYPE_3__* nfsnode_t ;
struct TYPE_34__ {int specdata1; int specdata2; } ;
typedef  TYPE_4__ nfs_specdata ;
struct TYPE_35__ {scalar_t__ fh_len; int /*<<< orphan*/  fh_data; } ;
typedef  TYPE_5__ fhandle_t ;
struct TYPE_32__ {int nva_flags; } ;
struct TYPE_33__ {int n_flag; int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_fhp; TYPE_2__ n_vattr; } ;

/* Variables and functions */
 int EBADRPC ; 
 int EEXIST ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  EPROTO ; 
 int /*<<< orphan*/  NATTRINVALIDATE (TYPE_3__*) ; 
#define  NFBLK 133 
#define  NFCHR 132 
#define  NFDIR 131 
#define  NFFIFO 130 
#define  NFLNK 129 
#define  NFSOCK 128 
 int /*<<< orphan*/  NFSPROC4_COMPOUND ; 
 int /*<<< orphan*/  NFSREQ_SECINFO_SET (struct nfsreq_secinfo_args*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSTOMP (TYPE_3__*) ; 
 struct nfsmount* NFSTONMP (TYPE_3__*) ; 
 int /*<<< orphan*/ * NFSTOV (TYPE_3__*) ; 
 int NFSX_UNSIGNED ; 
 int NFS_ATTR_BITMAP_LEN ; 
 int /*<<< orphan*/  NFS_BITMAP_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_BITMAP_SET (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_COPY_ATTRIBUTES (int*,int*) ; 
 int /*<<< orphan*/  NFS_FATTR_FILEHANDLE ; 
 int NFS_FFLAG_TRIGGER_REFERRAL ; 
 int NFS_FSFLAG_NAMED_ATTR ; 
 int NFS_OP_CREATE ; 
 int NFS_OP_GETATTR ; 
 int NFS_OP_PUTFH ; 
 int NFS_OP_RESTOREFH ; 
 int NFS_OP_SAVEFH ; 
 int /*<<< orphan*/  NGA_CACHED ; 
 int /*<<< orphan*/  NG_MAKEENTRY ; 
 int NMODIFIED ; 
 int NNEGNCENTRIES ; 
 int /*<<< orphan*/  NVATTR_CLEANUP (struct nfs_vattr*) ; 
 int /*<<< orphan*/  NVATTR_INIT (struct nfs_vattr*) ; 
 int /*<<< orphan*/  VATTR_IS_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_purge_negatives (int /*<<< orphan*/ *) ; 
 int major (int /*<<< orphan*/ ) ; 
 int minor (int /*<<< orphan*/ ) ; 
 int nfs4_parsefattr (struct nfsm_chain*,int /*<<< orphan*/ *,struct nfs_vattr*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_avoid_needless_id_setting_on_create (TYPE_3__*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_dulookup_finish (struct nfs_dulookup*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_dulookup_init (struct nfs_dulookup*,TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_dulookup_start (struct nfs_dulookup*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_getattr (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* nfs_getattr_bitmap ; 
 int nfs_lookitup (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_nget (int /*<<< orphan*/ ,TYPE_3__*,struct componentname*,int /*<<< orphan*/ ,scalar_t__,struct nfs_vattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  nfs_node_clear_busy (TYPE_3__*) ; 
 int nfs_node_lock (TYPE_3__*) ; 
 int nfs_node_set_busy (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_3__*) ; 
 int nfs_request_async (TYPE_3__*,int /*<<< orphan*/ *,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsreq_secinfo_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfsreq**) ; 
 int nfs_request_async_finish (struct nfsreq*,struct nfsm_chain*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nfs_vattr_set_supported (int*,struct vnode_attr*) ; 
 int /*<<< orphan*/  nfsm_assert (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_bitmap_supported (int,struct nfsm_chain*,int*,struct nfsmount*,TYPE_3__*) ; 
 int /*<<< orphan*/  nfsm_chain_add_compound_header (int,struct nfsm_chain*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_fattr4 (int,struct nfsm_chain*,struct vnode_attr*,struct nfsmount*) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_name (int,struct nfsm_chain*,char*,int /*<<< orphan*/ ,struct nfsmount*) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_check_change_info (int,struct nfsm_chain*,TYPE_3__*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_get_bitmap (int,struct nfsm_chain*,int*,int) ; 
 int /*<<< orphan*/  nfsm_chain_loadattr (int,struct nfsm_chain*,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_op_check (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_skip_tag (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 scalar_t__ nfstov_type (int,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  va_rdev ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ *) ; 
 scalar_t__ vnode_vtype (int /*<<< orphan*/ *) ; 

int
nfs4_create_rpc(
	vfs_context_t ctx,
	nfsnode_t dnp,
	struct componentname *cnp,
	struct vnode_attr *vap,
	int type,
	char *link,
	nfsnode_t *npp)
{
	struct nfsmount *nmp;
	struct nfs_vattr nvattr;
	int error = 0, create_error = EIO, lockerror = ENOENT, busyerror = ENOENT, status;
	int nfsvers, namedattrs, numops;
	u_int64_t xid, savedxid = 0;
	nfsnode_t np = NULL;
	vnode_t newvp = NULL;
	struct nfsm_chain nmreq, nmrep;
	uint32_t bitmap[NFS_ATTR_BITMAP_LEN], bmlen;
	const char *tag;
	nfs_specdata sd;
	fhandle_t fh;
	struct nfsreq rq, *req = &rq;
	struct nfs_dulookup dul;
	struct nfsreq_secinfo_args si;

	nmp = NFSTONMP(dnp);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	nfsvers = nmp->nm_vers;
	namedattrs = (nmp->nm_fsattr.nfsa_flags & NFS_FSFLAG_NAMED_ATTR);
	if (dnp->n_vattr.nva_flags & NFS_FFLAG_TRIGGER_REFERRAL)
		return (EINVAL);

	sd.specdata1 = sd.specdata2 = 0;

	switch (type) {
	case NFLNK:
		tag = "symlink";
		break;
	case NFBLK:
	case NFCHR:
		tag = "mknod";
		if (!VATTR_IS_ACTIVE(vap, va_rdev))
			return (EINVAL);
		sd.specdata1 = major(vap->va_rdev);
		sd.specdata2 = minor(vap->va_rdev);
		break;
	case NFSOCK:
	case NFFIFO:
		tag = "mknod";
		break;
	case NFDIR:
		tag = "mkdir";
		break;
	default:
		return (EINVAL);
	}

	nfs_avoid_needless_id_setting_on_create(dnp, vap, ctx);

	error = busyerror = nfs_node_set_busy(dnp, vfs_context_thread(ctx));
	if (!namedattrs)
		nfs_dulookup_init(&dul, dnp, cnp->cn_nameptr, cnp->cn_namelen, ctx);

	NFSREQ_SECINFO_SET(&si, dnp, NULL, 0, NULL, 0);
	NVATTR_INIT(&nvattr);
	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	// PUTFH, SAVEFH, CREATE, GETATTR(FH), RESTOREFH, GETATTR
	numops = 6;
	nfsm_chain_build_alloc_init(error, &nmreq, 66 * NFSX_UNSIGNED);
	nfsm_chain_add_compound_header(error, &nmreq, tag, nmp->nm_minor_vers, numops);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_PUTFH);
	nfsm_chain_add_fh(error, &nmreq, nfsvers, dnp->n_fhp, dnp->n_fhsize);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_SAVEFH);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_CREATE);
	nfsm_chain_add_32(error, &nmreq, type);
	if (type == NFLNK) {
		nfsm_chain_add_name(error, &nmreq, link, strlen(link), nmp);
	} else if ((type == NFBLK) || (type == NFCHR)) {
		nfsm_chain_add_32(error, &nmreq, sd.specdata1);
		nfsm_chain_add_32(error, &nmreq, sd.specdata2);
	}
	nfsm_chain_add_name(error, &nmreq, cnp->cn_nameptr, cnp->cn_namelen, nmp);
	nfsm_chain_add_fattr4(error, &nmreq, vap, nmp);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_GETATTR);
	NFS_COPY_ATTRIBUTES(nfs_getattr_bitmap, bitmap);
	NFS_BITMAP_SET(bitmap, NFS_FATTR_FILEHANDLE);
	nfsm_chain_add_bitmap_supported(error, &nmreq, bitmap, nmp, NULL);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_RESTOREFH);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_GETATTR);
	nfsm_chain_add_bitmap_supported(error, &nmreq, nfs_getattr_bitmap, nmp, dnp);
	nfsm_chain_build_done(error, &nmreq);
	nfsm_assert(error, (numops == 0), EPROTO);
	nfsmout_if(error);

	error = nfs_request_async(dnp, NULL, &nmreq, NFSPROC4_COMPOUND,
			vfs_context_thread(ctx), vfs_context_ucred(ctx), &si, 0, NULL, &req);
	if (!error) {
		if (!namedattrs)
			nfs_dulookup_start(&dul, dnp, ctx);
		error = nfs_request_async_finish(req, &nmrep, &xid, &status);
	}

	if ((lockerror = nfs_node_lock(dnp)))
		error = lockerror;
	nfsm_chain_skip_tag(error, &nmrep);
	nfsm_chain_get_32(error, &nmrep, numops);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_PUTFH);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_SAVEFH);
	nfsmout_if(error);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_CREATE);
	nfsm_chain_check_change_info(error, &nmrep, dnp);
	bmlen = NFS_ATTR_BITMAP_LEN;
	nfsm_chain_get_bitmap(error, &nmrep, bitmap, bmlen);
	/* At this point if we have no error, the object was created. */
	/* if we don't get attributes, then we should lookitup. */
	create_error = error;
	nfsmout_if(error);
	nfs_vattr_set_supported(bitmap, vap);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_GETATTR);
	nfsmout_if(error);
	error = nfs4_parsefattr(&nmrep, NULL, &nvattr, &fh, NULL, NULL);
	nfsmout_if(error);
	if (!NFS_BITMAP_ISSET(nvattr.nva_bitmap, NFS_FATTR_FILEHANDLE)) {
		printf("nfs: create/%s didn't return filehandle? %s\n", tag, cnp->cn_nameptr);
		error = EBADRPC;
		goto nfsmout;
	}
	/* directory attributes: if we don't get them, make sure to invalidate */
	nfsm_chain_op_check(error, &nmrep, NFS_OP_RESTOREFH);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_GETATTR);
	savedxid = xid;
	nfsm_chain_loadattr(error, &nmrep, dnp, nfsvers, &xid);
	if (error)
		NATTRINVALIDATE(dnp);

nfsmout:
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);

	if (!lockerror) {
		if (!create_error && (dnp->n_flag & NNEGNCENTRIES)) {
			dnp->n_flag &= ~NNEGNCENTRIES;
			cache_purge_negatives(NFSTOV(dnp));
		}
		dnp->n_flag |= NMODIFIED;
		nfs_node_unlock(dnp);
		/* nfs_getattr() will check changed and purge caches */
		nfs_getattr(dnp, NULL, ctx, NGA_CACHED);
	}

	if (!error && fh.fh_len) {
		/* create the vnode with the filehandle and attributes */
		xid = savedxid;
		error = nfs_nget(NFSTOMP(dnp), dnp, cnp, fh.fh_data, fh.fh_len, &nvattr, &xid, rq.r_auth, NG_MAKEENTRY, &np);
		if (!error)
			newvp = NFSTOV(np);
	}
	NVATTR_CLEANUP(&nvattr);

	if (!namedattrs)
		nfs_dulookup_finish(&dul, dnp, ctx);

	/*
	 * Kludge: Map EEXIST => 0 assuming that you have a reply to a retry
	 * if we can succeed in looking up the object.
	 */
	if ((create_error == EEXIST) || (!create_error && !newvp)) {
		error = nfs_lookitup(dnp, cnp->cn_nameptr, cnp->cn_namelen, ctx, &np);
		if (!error) {
			newvp = NFSTOV(np);
			if (vnode_vtype(newvp) != nfstov_type(type, nfsvers))
				error = EEXIST;
		}
	}
	if (!busyerror)
		nfs_node_clear_busy(dnp);
	if (error) {
		if (newvp) {
			nfs_node_unlock(np);
			vnode_put(newvp);
		}
	} else {
		nfs_node_unlock(np);
		*npp = np;
	}
	return (error);
}