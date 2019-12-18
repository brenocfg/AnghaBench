#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnop_open_args {int a_mode; int /*<<< orphan*/  a_vp; int /*<<< orphan*/  a_context; } ;
struct nfsmount {scalar_t__ nm_vers; scalar_t__ nm_curdeadtimeout; scalar_t__ nm_deadtimeout; int /*<<< orphan*/  nm_lock; int /*<<< orphan*/  nm_writers; scalar_t__ nm_deadto_start; int /*<<< orphan*/  nm_state; } ;
struct nfs_open_owner {int /*<<< orphan*/  noo_cred; } ;
struct nfs_open_file {int nof_flags; TYPE_1__* nof_owner; int /*<<< orphan*/ * nof_creator; } ;
typedef  TYPE_2__* nfsnode_t ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;
struct TYPE_14__ {int n_flag; int n_lastrahead; int /*<<< orphan*/  n_openlock; int /*<<< orphan*/  n_openrefcnt; } ;
struct TYPE_13__ {int /*<<< orphan*/  noo_cred; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 int FREAD ; 
 int FWRITE ; 
 scalar_t__ ISSET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSSTA_SQUISHY ; 
 int NFS_OPEN_FILE_CREATE ; 
 int NFS_OPEN_FILE_LOST ; 
 int NFS_OPEN_FILE_REOPEN ; 
 int NFS_OPEN_SHARE_ACCESS_BOTH ; 
 int NFS_OPEN_SHARE_ACCESS_READ ; 
 int NFS_OPEN_SHARE_ACCESS_WRITE ; 
 int NFS_OPEN_SHARE_DENY_BOTH ; 
 int NFS_OPEN_SHARE_DENY_NONE ; 
 int NFS_OPEN_SHARE_DENY_WRITE ; 
 scalar_t__ NFS_VER4 ; 
 int /*<<< orphan*/  NGA_UNCACHED ; 
 int NMODIFIED ; 
 int NNEEDINVALIDATE ; 
 int /*<<< orphan*/  NP (TYPE_2__*,char*,int,...) ; 
 int NREVOKE ; 
 int /*<<< orphan*/  NUPDATESIZE ; 
 int O_EXLOCK ; 
 int O_SHLOCK ; 
 int VDIR ; 
 int VLNK ; 
 int VREG ; 
 TYPE_2__* VTONFS (int /*<<< orphan*/ ) ; 
 struct nfsmount* VTONMP (int /*<<< orphan*/ ) ; 
 int V_IGNORE_WRITEERR ; 
 int V_SAVE ; 
 int /*<<< orphan*/ * current_thread () ; 
 int /*<<< orphan*/  kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int nfs4_open (TYPE_2__*,struct nfs_open_file*,int,int,int /*<<< orphan*/ ) ; 
 int nfs4_reopen (struct nfs_open_file*,int /*<<< orphan*/ ) ; 
 int nfs_close (TYPE_2__*,struct nfs_open_file*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_data_update_size (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int nfs_getattr (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_invaldir (TYPE_2__*) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int /*<<< orphan*/  nfs_mount_state_error_should_restart (int) ; 
 scalar_t__ nfs_mount_state_in_use_end (struct nfsmount*,int) ; 
 int nfs_mount_state_in_use_start (struct nfsmount*,int /*<<< orphan*/ ) ; 
 int nfs_node_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_open_file_add_open (struct nfs_open_file*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_open_file_clear_busy (struct nfs_open_file*) ; 
 int nfs_open_file_find (TYPE_2__*,struct nfs_open_owner*,struct nfs_open_file**,int,int,int) ; 
 int nfs_open_file_set_busy (struct nfs_open_file*,int /*<<< orphan*/ ) ; 
 struct nfs_open_owner* nfs_open_owner_find (struct nfsmount*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_open_owner_rele (struct nfs_open_owner*) ; 
 int nfs_vinvalbuf (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int vnode_vtype (int /*<<< orphan*/ ) ; 

int
nfs_vnop_open(
	struct vnop_open_args /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_vp;
		int a_mode;
		vfs_context_t a_context;
	} */ *ap)
{
	vfs_context_t ctx = ap->a_context;
	vnode_t vp = ap->a_vp;
	nfsnode_t np = VTONFS(vp);
	struct nfsmount *nmp;
	int error, accessMode, denyMode, opened = 0;
	struct nfs_open_owner *noop = NULL;
	struct nfs_open_file *nofp = NULL;
	enum vtype vtype;

	if (!(ap->a_mode & (FREAD|FWRITE)))
		return (EINVAL);

	nmp = VTONMP(vp);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	if (np->n_flag & NREVOKE)
		return (EIO);

	vtype = vnode_vtype(vp);
	if ((vtype != VREG) && (vtype != VDIR) && (vtype != VLNK))
		return (EACCES);

	/* First, check if we need to update/invalidate */
	if (ISSET(np->n_flag, NUPDATESIZE))
		nfs_data_update_size(np, 0);
	if ((error = nfs_node_lock(np)))
		return (error);
	if (np->n_flag & NNEEDINVALIDATE) {
		np->n_flag &= ~NNEEDINVALIDATE;
		if (vtype == VDIR)
			nfs_invaldir(np);
		nfs_node_unlock(np);
		nfs_vinvalbuf(vp, V_SAVE|V_IGNORE_WRITEERR, ctx, 1);
		if ((error = nfs_node_lock(np)))
			return (error);
	}
	if (vtype == VREG)
		np->n_lastrahead = -1;
	if (np->n_flag & NMODIFIED) {
		if (vtype == VDIR)
			nfs_invaldir(np);
		nfs_node_unlock(np);
		if ((error = nfs_vinvalbuf(vp, V_SAVE|V_IGNORE_WRITEERR, ctx, 1)))
			return (error);
	} else {
		nfs_node_unlock(np);
	}

	/* nfs_getattr() will check changed and purge caches */
	if ((error = nfs_getattr(np, NULL, ctx, NGA_UNCACHED)))
		return (error);

	if (vtype != VREG) {
		/* Just mark that it was opened */
		lck_mtx_lock(&np->n_openlock);
		np->n_openrefcnt++;
		lck_mtx_unlock(&np->n_openlock);
		return (0);
	}

	/* mode contains some combination of: FREAD, FWRITE, O_SHLOCK, O_EXLOCK */
	accessMode = 0;
	if (ap->a_mode & FREAD)
		accessMode |= NFS_OPEN_SHARE_ACCESS_READ;
	if (ap->a_mode & FWRITE)
		accessMode |= NFS_OPEN_SHARE_ACCESS_WRITE;
	if (ap->a_mode & O_EXLOCK)
		denyMode = NFS_OPEN_SHARE_DENY_BOTH;
	else if (ap->a_mode & O_SHLOCK)
		denyMode = NFS_OPEN_SHARE_DENY_WRITE;
	else
		denyMode = NFS_OPEN_SHARE_DENY_NONE;
	// XXX don't do deny modes just yet (and never do it for !v4)
	denyMode = NFS_OPEN_SHARE_DENY_NONE;

	noop = nfs_open_owner_find(nmp, vfs_context_ucred(ctx), 1);
	if (!noop)
		return (ENOMEM);

restart:
	error = nfs_mount_state_in_use_start(nmp, vfs_context_thread(ctx));
	if (error) {
		nfs_open_owner_rele(noop);
		return (error);
	}
	if (np->n_flag & NREVOKE) {
		error = EIO;
		nfs_mount_state_in_use_end(nmp, 0);
		nfs_open_owner_rele(noop);
		return (error);
	}

	error = nfs_open_file_find(np, noop, &nofp, accessMode, denyMode, 1);
	if (!error && (nofp->nof_flags & NFS_OPEN_FILE_LOST)) {
		NP(np, "nfs_vnop_open: LOST %d", kauth_cred_getuid(nofp->nof_owner->noo_cred));
		error = EIO;
	}
	if (!error && (nofp->nof_flags & NFS_OPEN_FILE_REOPEN)) {
		nfs_mount_state_in_use_end(nmp, 0);
		error = nfs4_reopen(nofp, vfs_context_thread(ctx));
		nofp = NULL;
		if (!error)
			goto restart;
	}
	if (!error)
		error = nfs_open_file_set_busy(nofp, vfs_context_thread(ctx));
	if (error) {
		nofp = NULL;
		goto out;
	}

	if (nmp->nm_vers < NFS_VER4) {
		/*
		 * NFS v2/v3 opens are always allowed - so just add it.
		 */
		nfs_open_file_add_open(nofp, accessMode, denyMode, 0);
		goto out;
	}

	/*
	 * If we just created the file and the modes match, then we simply use
	 * the open performed in the create.  Otherwise, send the request.
	 */
	if ((nofp->nof_flags & NFS_OPEN_FILE_CREATE) &&
	    (nofp->nof_creator == current_thread()) &&
	    (accessMode == NFS_OPEN_SHARE_ACCESS_BOTH) &&
	    (denyMode == NFS_OPEN_SHARE_DENY_NONE)) {
		nofp->nof_flags &= ~NFS_OPEN_FILE_CREATE;
		nofp->nof_creator = NULL;
	} else {
		if (!opened)
			error = nfs4_open(np, nofp, accessMode, denyMode, ctx);
		if ((error == EACCES) && (nofp->nof_flags & NFS_OPEN_FILE_CREATE) &&
		    (nofp->nof_creator == current_thread())) {
			/*
			 * Ugh.  This can happen if we just created the file with read-only
			 * perms and we're trying to open it for real with different modes
			 * (e.g. write-only or with a deny mode) and the server decides to
			 * not allow the second open because of the read-only perms.
			 * The best we can do is to just use the create's open.
			 * We may have access we don't need or we may not have a requested
			 * deny mode.  We may log complaints later, but we'll try to avoid it.
			 */
			if (denyMode != NFS_OPEN_SHARE_DENY_NONE)
				NP(np, "nfs_vnop_open: deny mode foregone on create, %d", kauth_cred_getuid(nofp->nof_owner->noo_cred));
			nofp->nof_creator = NULL;
			error = 0;
		}
		if (error)
			goto out;
		opened = 1;
		/*
		 * If we had just created the file, we already had it open.
		 * If the actual open mode is less than what we grabbed at
		 * create time, then we'll downgrade the open here.
		 */
		if ((nofp->nof_flags & NFS_OPEN_FILE_CREATE) &&
		    (nofp->nof_creator == current_thread())) {
			error = nfs_close(np, nofp, NFS_OPEN_SHARE_ACCESS_BOTH, NFS_OPEN_SHARE_DENY_NONE, ctx);
			if (error)
				NP(np, "nfs_vnop_open: create close error %d, %d", error, kauth_cred_getuid(nofp->nof_owner->noo_cred));
			if (!nfs_mount_state_error_should_restart(error)) {
				error = 0;
				nofp->nof_flags &= ~NFS_OPEN_FILE_CREATE;
			}
		}
	}

out:
	if (nofp)
		nfs_open_file_clear_busy(nofp);
	if (nfs_mount_state_in_use_end(nmp, error)) {
		nofp = NULL;
		goto restart;
	}
	if (error)
		NP(np, "nfs_vnop_open: error %d, %d", error, kauth_cred_getuid(noop->noo_cred));
	if (noop)
		nfs_open_owner_rele(noop);
	if (!error && vtype == VREG && (ap->a_mode & FWRITE)) {
		lck_mtx_lock(&nmp->nm_lock);
		nmp->nm_state &= ~NFSSTA_SQUISHY;
		nmp->nm_curdeadtimeout = nmp->nm_deadtimeout;
		if (nmp->nm_curdeadtimeout <= 0)
			nmp->nm_deadto_start = 0;
		nmp->nm_writers++;
		lck_mtx_unlock(&nmp->nm_lock);
	}
		
	return (error);
}