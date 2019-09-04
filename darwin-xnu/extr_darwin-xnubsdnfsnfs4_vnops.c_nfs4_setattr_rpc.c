#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int uint32_t ;
typedef  scalar_t__ u_int64_t ;
struct vnode_attr {int va_flags; int va_active; scalar_t__ va_uid; scalar_t__ va_gid; int /*<<< orphan*/  va_guuid; int /*<<< orphan*/  va_uuuid; } ;
struct nfsreq_secinfo_args {int dummy; } ;
struct nfsmount {int nm_vers; int /*<<< orphan*/  nm_minor_vers; } ;
struct nfsm_chain {int dummy; } ;
typedef  TYPE_2__* nfsnode_t ;
struct TYPE_20__ {scalar_t__* other; scalar_t__ seqid; } ;
typedef  TYPE_3__ nfs_stateid ;
struct TYPE_18__ {int nva_flags; scalar_t__ nva_uid; scalar_t__ nva_gid; int /*<<< orphan*/  nva_guuid; int /*<<< orphan*/  nva_uuuid; } ;
struct TYPE_19__ {scalar_t__ n_xid; int /*<<< orphan*/  n_lastio; TYPE_1__ n_vattr; int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_fhp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACLONLY ; 
 int EBADRPC ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOTSUP ; 
 int ENXIO ; 
 int /*<<< orphan*/  EPROTO ; 
 int /*<<< orphan*/  NACLINVALIDATE (TYPE_2__*) ; 
 scalar_t__ NACLVALID (TYPE_2__*) ; 
 int /*<<< orphan*/  NATTRINVALIDATE (TYPE_2__*) ; 
 int /*<<< orphan*/  NFSPROC4_COMPOUND ; 
 int /*<<< orphan*/  NFSREQ_SECINFO_SET (struct nfsreq_secinfo_args*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int NFSX_UNSIGNED ; 
 int NFS_ATTR_BITMAP_LEN ; 
 scalar_t__ NFS_BITMAP_ISSET (int*,int) ; 
 int /*<<< orphan*/  NFS_BITMAP_SET (int*,int) ; 
 int /*<<< orphan*/  NFS_COPY_ATTRIBUTES (int /*<<< orphan*/ ,int*) ; 
 int NFS_FATTR_ACL ; 
 int NFS_FATTR_MODE ; 
 int NFS_FFLAG_IS_ATTR ; 
 int NFS_FFLAG_TRIGGER_REFERRAL ; 
 int /*<<< orphan*/  NFS_OP_GETATTR ; 
 int /*<<< orphan*/  NFS_OP_PUTFH ; 
 int /*<<< orphan*/  NFS_OP_SETATTR ; 
 int /*<<< orphan*/  NMFLAG (struct nfsmount*,int /*<<< orphan*/ ) ; 
 int SF_ARCHIVED ; 
 int UF_HIDDEN ; 
 int /*<<< orphan*/  VATTR_CLEAR_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VATTR_IS_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int VNODE_ATTR_va_flags ; 
 scalar_t__ kauth_guid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  microuptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_get_stateid (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  nfs_get_xid (scalar_t__*) ; 
 int /*<<< orphan*/  nfs_getattr_bitmap ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_node_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 int nfs_request (TYPE_2__*,int /*<<< orphan*/ *,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsreq_secinfo_args*,struct nfsm_chain*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  nfs_vattr_set_bitmap (struct nfsmount*,int*,struct vnode_attr*) ; 
 int /*<<< orphan*/  nfs_vattr_set_supported (int*,struct vnode_attr*) ; 
 int /*<<< orphan*/  nfsm_assert (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_bitmap_supported (int,struct nfsm_chain*,int*,struct nfsmount*,TYPE_2__*) ; 
 int /*<<< orphan*/  nfsm_chain_add_compound_header (int,struct nfsm_chain*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_fattr4 (int,struct nfsm_chain*,struct vnode_attr*,struct nfsmount*) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_stateid (int,struct nfsm_chain*,TYPE_3__*) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_get_bitmap (int,struct nfsm_chain*,int*,int) ; 
 int /*<<< orphan*/  nfsm_chain_loadattr (int,struct nfsm_chain*,TYPE_2__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_op_check (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_skip_tag (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 int /*<<< orphan*/  va_acl ; 
 int /*<<< orphan*/  va_data_size ; 
 int /*<<< orphan*/  va_flags ; 
 int /*<<< orphan*/  va_gid ; 
 int /*<<< orphan*/  va_guuid ; 
 int /*<<< orphan*/  va_mode ; 
 int /*<<< orphan*/  va_uid ; 
 int /*<<< orphan*/  va_uuuid ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 

int
nfs4_setattr_rpc(
	nfsnode_t np,
	struct vnode_attr *vap,
	vfs_context_t ctx)
{
	struct nfsmount *nmp = NFSTONMP(np);
	int error = 0, setattr_error = 0, lockerror = ENOENT, status, nfsvers, numops;
	u_int64_t xid, nextxid;
	struct nfsm_chain nmreq, nmrep;
	uint32_t bitmap[NFS_ATTR_BITMAP_LEN], bmlen;
	uint32_t getbitmap[NFS_ATTR_BITMAP_LEN];
	uint32_t setbitmap[NFS_ATTR_BITMAP_LEN];
	nfs_stateid stateid;
	struct nfsreq_secinfo_args si;

	if (nfs_mount_gone(nmp))
		return (ENXIO);
	nfsvers = nmp->nm_vers;
	if (np->n_vattr.nva_flags & NFS_FFLAG_TRIGGER_REFERRAL)
		return (EINVAL);

	if (VATTR_IS_ACTIVE(vap, va_flags) && (vap->va_flags & ~(SF_ARCHIVED|UF_HIDDEN))) {
		/* we don't support setting unsupported flags (duh!) */
		if (vap->va_active & ~VNODE_ATTR_va_flags)
			return (EINVAL);	/* return EINVAL if other attributes also set */
		else
			return (ENOTSUP);	/* return ENOTSUP for chflags(2) */
	}

	/* don't bother requesting some changes if they don't look like they are changing */
	if (VATTR_IS_ACTIVE(vap, va_uid) && (vap->va_uid == np->n_vattr.nva_uid))
		VATTR_CLEAR_ACTIVE(vap, va_uid);
	if (VATTR_IS_ACTIVE(vap, va_gid) && (vap->va_gid == np->n_vattr.nva_gid))
		VATTR_CLEAR_ACTIVE(vap, va_gid);
	if (VATTR_IS_ACTIVE(vap, va_uuuid) && kauth_guid_equal(&vap->va_uuuid, &np->n_vattr.nva_uuuid))
		VATTR_CLEAR_ACTIVE(vap, va_uuuid);
	if (VATTR_IS_ACTIVE(vap, va_guuid) && kauth_guid_equal(&vap->va_guuid, &np->n_vattr.nva_guuid))
		VATTR_CLEAR_ACTIVE(vap, va_guuid);

tryagain:
	/* do nothing if no attributes will be sent */
	nfs_vattr_set_bitmap(nmp, bitmap, vap);
	if (!bitmap[0] && !bitmap[1])
		return (0);

	NFSREQ_SECINFO_SET(&si, np, NULL, 0, NULL, 0);
	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	/*
	 * Prepare GETATTR bitmap: if we are setting the ACL or mode, we
	 * need to invalidate any cached ACL.  And if we had an ACL cached,
	 * we might as well also fetch the new value.
	 */
	NFS_COPY_ATTRIBUTES(nfs_getattr_bitmap, getbitmap);
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_ACL) ||
	    NFS_BITMAP_ISSET(bitmap, NFS_FATTR_MODE)) {
		if (NACLVALID(np))
			NFS_BITMAP_SET(getbitmap, NFS_FATTR_ACL);
		NACLINVALIDATE(np);
	}

	// PUTFH, SETATTR, GETATTR
	numops = 3;
	nfsm_chain_build_alloc_init(error, &nmreq, 40 * NFSX_UNSIGNED);
	nfsm_chain_add_compound_header(error, &nmreq, "setattr", nmp->nm_minor_vers, numops);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_PUTFH);
	nfsm_chain_add_fh(error, &nmreq, nfsvers, np->n_fhp, np->n_fhsize);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_SETATTR);
	if (VATTR_IS_ACTIVE(vap, va_data_size))
		nfs_get_stateid(np, vfs_context_thread(ctx), vfs_context_ucred(ctx), &stateid);
	else
		stateid.seqid = stateid.other[0] = stateid.other[1] = stateid.other[2] = 0;
	nfsm_chain_add_stateid(error, &nmreq, &stateid);
	nfsm_chain_add_fattr4(error, &nmreq, vap, nmp);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_GETATTR);
	nfsm_chain_add_bitmap_supported(error, &nmreq, getbitmap, nmp, np);
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
	nfsm_chain_op_check(error, &nmrep, NFS_OP_SETATTR);
	nfsmout_if(error == EBADRPC);
	setattr_error = error;
	error = 0;
	bmlen = NFS_ATTR_BITMAP_LEN;
	nfsm_chain_get_bitmap(error, &nmrep, setbitmap, bmlen);
	if (!error) {
		if (VATTR_IS_ACTIVE(vap, va_data_size) && (np->n_vattr.nva_flags & NFS_FFLAG_IS_ATTR))
			microuptime(&np->n_lastio);
		nfs_vattr_set_supported(setbitmap, vap);
		error = setattr_error;
	}
	nfsm_chain_op_check(error, &nmrep, NFS_OP_GETATTR);
	nfsm_chain_loadattr(error, &nmrep, np, nfsvers, &xid);
	if (error)
		NATTRINVALIDATE(np);
	/*
	 * We just changed the attributes and we want to make sure that we
	 * see the latest attributes.  Get the next XID.  If it's not the
	 * next XID after the SETATTR XID, then it's possible that another
	 * RPC was in flight at the same time and it might put stale attributes
	 * in the cache.  In that case, we invalidate the attributes and set
	 * the attribute cache XID to guarantee that newer attributes will
	 * get loaded next.
	 */
	nextxid = 0;
	nfs_get_xid(&nextxid);
	if (nextxid != (xid + 1)) {
		np->n_xid = nextxid;
		NATTRINVALIDATE(np);
	}
nfsmout:
	if (!lockerror)
		nfs_node_unlock(np);
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);
	if ((setattr_error == EINVAL) && VATTR_IS_ACTIVE(vap, va_acl) && VATTR_IS_ACTIVE(vap, va_mode) && !NMFLAG(nmp, ACLONLY)) {
		/*
		 * Some server's may not like ACL/mode combos that get sent.
		 * If it looks like that's what the server choked on, try setting
		 * just the ACL and not the mode (unless it looks like everything
		 * but mode was already successfully set).
		 */
		if (((bitmap[0] & setbitmap[0]) != bitmap[0]) ||
		    ((bitmap[1] & (setbitmap[1]|NFS_FATTR_MODE)) != bitmap[1])) {
			VATTR_CLEAR_ACTIVE(vap, va_mode);
			error = 0;
			goto tryagain;
		}
	}
	return (error);
}