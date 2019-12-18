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
typedef  int /*<<< orphan*/ * vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnop_create_args {int /*<<< orphan*/ ** a_vpp; int /*<<< orphan*/ * a_dvp; struct vnode_attr* a_vap; struct componentname* a_cnp; int /*<<< orphan*/  a_context; } ;
struct vnode_attr {int va_vaflags; int va_mode; } ;
struct nfsmount {int dummy; } ;
struct nfs_open_owner {int dummy; } ;
struct nfs_open_file {int nof_flags; int /*<<< orphan*/  nof_creator; int /*<<< orphan*/  nof_stateid; } ;
struct componentname {int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/  cn_nameptr; } ;
typedef  scalar_t__ nfsnode_t ;

/* Variables and functions */
 int EACCES ; 
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/ * NFSTOV (scalar_t__) ; 
 int /*<<< orphan*/  NFS_OPEN_CREATE ; 
 int NFS_OPEN_FILE_CREATE ; 
 int NFS_OPEN_FILE_LOST ; 
 int NFS_OPEN_FILE_POSIXLOCK ; 
 int NFS_OPEN_FILE_REOPEN ; 
 int /*<<< orphan*/  NFS_OPEN_NOCREATE ; 
 int NFS_OPEN_SHARE_ACCESS_BOTH ; 
 int NFS_OPEN_SHARE_DENY_NONE ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 scalar_t__ VATTR_IS_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_SET (struct vnode_attr*,int /*<<< orphan*/ ,int) ; 
 int VA_EXCLUSIVE ; 
 scalar_t__ VREG ; 
 scalar_t__ VTONFS (int /*<<< orphan*/ *) ; 
 struct nfsmount* VTONMP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_thread () ; 
 int nfs4_open_rpc (struct nfs_open_file*,int /*<<< orphan*/ ,struct componentname*,struct vnode_attr*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int) ; 
 int nfs4_reopen (struct nfs_open_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_setattr_rpc (scalar_t__,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_avoid_needless_id_setting_on_create (scalar_t__,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int nfs_lookitup (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 scalar_t__ nfs_mount_state_in_use_end (struct nfsmount*,int) ; 
 int nfs_mount_state_in_use_start (struct nfsmount*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_node_unlock (scalar_t__) ; 
 int /*<<< orphan*/  nfs_open_file_add_open (struct nfs_open_file*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_open_file_clear_busy (struct nfs_open_file*) ; 
 int /*<<< orphan*/  nfs_open_file_destroy (struct nfs_open_file*) ; 
 int nfs_open_file_find (int /*<<< orphan*/ *,struct nfs_open_owner*,struct nfs_open_file**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nfs_open_file_find_internal (scalar_t__,struct nfs_open_owner*,struct nfs_open_file**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs_open_file_set_busy (struct nfs_open_file*,int /*<<< orphan*/ *) ; 
 struct nfs_open_owner* nfs_open_owner_find (struct nfsmount*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_open_owner_rele (struct nfs_open_owner*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  va_mode ; 
 int /*<<< orphan*/ * vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ *) ; 
 scalar_t__ vnode_vtype (int /*<<< orphan*/ *) ; 

int
nfs4_vnop_create(
	struct vnop_create_args /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_dvp;
		vnode_t *a_vpp;
		struct componentname *a_cnp;
		struct vnode_attr *a_vap;
		vfs_context_t a_context;
	} */ *ap)
{
	vfs_context_t ctx = ap->a_context;
	struct componentname *cnp = ap->a_cnp;
	struct vnode_attr *vap = ap->a_vap;
	vnode_t dvp = ap->a_dvp;
	vnode_t *vpp = ap->a_vpp;
	struct nfsmount *nmp;
	nfsnode_t np;
	int error = 0, busyerror = 0, accessMode, denyMode;
	struct nfs_open_owner *noop = NULL;
	struct nfs_open_file *newnofp = NULL, *nofp = NULL;

	nmp = VTONMP(dvp);
	if (nfs_mount_gone(nmp))
		return (ENXIO);

	if (vap)
		nfs_avoid_needless_id_setting_on_create(VTONFS(dvp), vap, ctx);

	noop = nfs_open_owner_find(nmp, vfs_context_ucred(ctx), 1);
	if (!noop)
		return (ENOMEM);

restart:
	error = nfs_mount_state_in_use_start(nmp, vfs_context_thread(ctx));
	if (error) {
		nfs_open_owner_rele(noop);
		return (error);
	}

	/* grab a provisional, nodeless open file */
	error = nfs_open_file_find(NULL, noop, &newnofp, 0, 0, 1);
	if (!error && (newnofp->nof_flags & NFS_OPEN_FILE_LOST)) {
		printf("nfs_vnop_create: LOST\n");
		error = EIO;
	}
	if (!error && (newnofp->nof_flags & NFS_OPEN_FILE_REOPEN)) {
		/* This shouldn't happen given that this is a new, nodeless nofp */
		nfs_mount_state_in_use_end(nmp, 0);
		error = nfs4_reopen(newnofp, vfs_context_thread(ctx));
		nfs_open_file_destroy(newnofp);
		newnofp = NULL;
		if (!error)
			goto restart;
	}
	if (!error)
		error = nfs_open_file_set_busy(newnofp, vfs_context_thread(ctx));
	if (error) {
		if (newnofp)
			nfs_open_file_destroy(newnofp);
		newnofp = NULL;
		goto out;
	}

	/*
	 * We're just trying to create the file.
	 * We'll create/open it RW, and set NFS_OPEN_FILE_CREATE.
	 */
	accessMode = NFS_OPEN_SHARE_ACCESS_BOTH;
	denyMode = NFS_OPEN_SHARE_DENY_NONE;

	/* Do the open/create */
	error = nfs4_open_rpc(newnofp, ctx, cnp, vap, dvp, vpp, NFS_OPEN_CREATE, accessMode, denyMode);
	if ((error == EACCES) && vap && !(vap->va_vaflags & VA_EXCLUSIVE) &&
	    VATTR_IS_ACTIVE(vap, va_mode) && !(vap->va_mode & S_IWUSR)) {
		/*
		 * Hmm... it looks like we may have a situation where the request was
		 * retransmitted because we didn't get the first response which successfully
		 * created/opened the file and then the second time we were denied the open
		 * because the mode the file was created with doesn't allow write access.
		 *
		 * We'll try to work around this by temporarily updating the mode and
		 * retrying the open.
		 */
		struct vnode_attr vattr;

		/* first make sure it's there */
		int error2 = nfs_lookitup(VTONFS(dvp), cnp->cn_nameptr, cnp->cn_namelen, ctx, &np);
		if (!error2 && np) {
			nfs_node_unlock(np);
			*vpp = NFSTOV(np);
			if (vnode_vtype(NFSTOV(np)) == VREG) {
				VATTR_INIT(&vattr);
				VATTR_SET(&vattr, va_mode, (vap->va_mode | S_IWUSR));
				if (!nfs4_setattr_rpc(np, &vattr, ctx)) {
					error2 = nfs4_open_rpc(newnofp, ctx, cnp, NULL, dvp, vpp, NFS_OPEN_NOCREATE, accessMode, denyMode);
					VATTR_INIT(&vattr);
					VATTR_SET(&vattr, va_mode, vap->va_mode);
					nfs4_setattr_rpc(np, &vattr, ctx);
					if (!error2)
						error = 0;
				}
			}
			if (error) {
				vnode_put(*vpp);
				*vpp = NULL;
			}
		}
	}
	if (!error && !*vpp) {
		printf("nfs4_open_rpc returned without a node?\n");
		/* Hmmm... with no node, we have no filehandle and can't close it */
		error = EIO;
	}
	if (error) {
		/* need to cleanup our temporary nofp */
		nfs_open_file_clear_busy(newnofp);
		nfs_open_file_destroy(newnofp);
		newnofp = NULL;
		goto out;
	}
	/* After we have a node, add our open file struct to the node */
	np = VTONFS(*vpp);
	nfs_open_file_add_open(newnofp, accessMode, denyMode, 0);
	nofp = newnofp;
	error = nfs_open_file_find_internal(np, noop, &nofp, 0, 0, 0);
	if (error) {
		/* This shouldn't happen, because we passed in a new nofp to use. */
		printf("nfs_open_file_find_internal failed! %d\n", error);
		goto out;
	} else if (nofp != newnofp) {
		/*
		 * Hmm... an open file struct already exists.
		 * Mark the existing one busy and merge our open into it.
		 * Then destroy the one we created.
		 * Note: there's no chance of an open confict because the
		 * open has already been granted.
		 */
		busyerror = nfs_open_file_set_busy(nofp, NULL);
		nfs_open_file_add_open(nofp, accessMode, denyMode, 0);
		nofp->nof_stateid = newnofp->nof_stateid;
		if (newnofp->nof_flags & NFS_OPEN_FILE_POSIXLOCK)
			nofp->nof_flags |= NFS_OPEN_FILE_POSIXLOCK;
		nfs_open_file_clear_busy(newnofp);
		nfs_open_file_destroy(newnofp);
	}
	newnofp = NULL;
	/* mark the node as holding a create-initiated open */
	nofp->nof_flags |= NFS_OPEN_FILE_CREATE;
	nofp->nof_creator = current_thread();
out:
	if (nofp && !busyerror)
		nfs_open_file_clear_busy(nofp);
	if (nfs_mount_state_in_use_end(nmp, error)) {
		nofp = newnofp = NULL;
		busyerror = 0;
		goto restart;
	}
	if (noop)
		nfs_open_owner_rele(noop);
	return (error);
}