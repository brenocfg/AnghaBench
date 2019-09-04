#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int uint64_t ;
typedef  scalar_t__ u_quad_t ;
struct vnop_advlock_args {int a_op; int a_flags; int /*<<< orphan*/  a_vp; int /*<<< orphan*/  a_context; struct flock* a_fl; } ;
struct nfsmount {scalar_t__ nm_vers; scalar_t__ nm_lockmode; int /*<<< orphan*/  nm_lock; } ;
struct nfs_open_owner {int /*<<< orphan*/  noo_cred; } ;
struct nfs_open_file {int nof_flags; TYPE_1__* nof_owner; } ;
struct nfs_lock_owner {int dummy; } ;
struct flock {int l_whence; scalar_t__ l_start; int l_len; int /*<<< orphan*/  l_type; } ;
typedef  scalar_t__ off_t ;
typedef  TYPE_2__* nfsnode_t ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;
struct TYPE_16__ {int n_flag; scalar_t__ n_size; } ;
struct TYPE_15__ {int /*<<< orphan*/  noo_cred; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ENOTSUP ; 
 int ENXIO ; 
 int EOVERFLOW ; 
 int EPERM ; 
 int F_FLOCK ; 
 int F_GETLK ; 
 int F_SETLK ; 
 int F_SETLKW ; 
 int F_UNLCK ; 
 int F_WAIT ; 
 int INT32_MAX ; 
 int /*<<< orphan*/  NFS_DATA_LOCK_SHARED ; 
 int NFS_FILE_LOCK_STYLE_FLOCK ; 
 int NFS_FILE_LOCK_STYLE_POSIX ; 
 scalar_t__ NFS_LOCK_MODE_DISABLED ; 
 int NFS_OPEN_FILE_LOST ; 
 int NFS_OPEN_FILE_REOPEN ; 
 scalar_t__ NFS_VER2 ; 
 scalar_t__ NFS_VER3 ; 
 int /*<<< orphan*/  NGA_UNCACHED ; 
 int NMODIFIED ; 
 int /*<<< orphan*/  NP (TYPE_2__*,char*,int,...) ; 
 int NREVOKE ; 
 scalar_t__ QUAD_MAX ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int UINT64_MAX ; 
 int VDIR ; 
 int VREG ; 
 TYPE_2__* VTONFS (int /*<<< orphan*/ ) ; 
 struct nfsmount* VTONMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_SAVE ; 
 int /*<<< orphan*/  kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int nfs4_reopen (struct nfs_open_file*,int /*<<< orphan*/ *) ; 
 int nfs_advlock_getlock (TYPE_2__*,struct nfs_lock_owner*,struct flock*,int,int,int /*<<< orphan*/ ) ; 
 int nfs_advlock_setlock (TYPE_2__*,struct nfs_open_file*,struct nfs_lock_owner*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs_advlock_unlock (TYPE_2__*,struct nfs_open_file*,struct nfs_lock_owner*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_data_lock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_data_unlock (TYPE_2__*) ; 
 int nfs_getattr (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfs_lock_owner* nfs_lock_owner_find (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_lock_owner_rele (struct nfs_lock_owner*) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_node_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 int nfs_open_file_find (TYPE_2__*,struct nfs_open_owner*,struct nfs_open_file**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfs_open_owner* nfs_open_owner_find (struct nfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_open_owner_rele (struct nfs_open_owner*) ; 
 int nfs_vinvalbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int vnode_vtype (int /*<<< orphan*/ ) ; 

int
nfs_vnop_advlock(
	struct vnop_advlock_args /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_vp;
		caddr_t a_id;
		int a_op;
		struct flock *a_fl;
		int a_flags;
		vfs_context_t a_context;
	} */ *ap)
{
	vnode_t vp = ap->a_vp;
	nfsnode_t np = VTONFS(ap->a_vp);
	struct flock *fl = ap->a_fl;
	int op = ap->a_op;
	int flags = ap->a_flags;
	vfs_context_t ctx = ap->a_context;
	struct nfsmount *nmp;
	struct nfs_open_owner *noop = NULL;
	struct nfs_open_file *nofp = NULL;
	struct nfs_lock_owner *nlop = NULL;
	off_t lstart;
	uint64_t start, end;
	int error = 0, modified, style;
	enum vtype vtype;
#define OFF_MAX QUAD_MAX

	nmp = VTONMP(ap->a_vp);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	lck_mtx_lock(&nmp->nm_lock);
	if ((nmp->nm_vers <= NFS_VER3) && (nmp->nm_lockmode == NFS_LOCK_MODE_DISABLED)) {
		lck_mtx_unlock(&nmp->nm_lock);
		return (ENOTSUP);
	}
	lck_mtx_unlock(&nmp->nm_lock);

	if (np->n_flag & NREVOKE)
		return (EIO);
	vtype = vnode_vtype(ap->a_vp);
	if (vtype == VDIR) /* ignore lock requests on directories */
		return (0);
	if (vtype != VREG) /* anything other than regular files is invalid */
		return (EINVAL);

	/* Convert the flock structure into a start and end. */
	switch (fl->l_whence) {
	case SEEK_SET:
	case SEEK_CUR:
		/*
		 * Caller is responsible for adding any necessary offset
		 * to fl->l_start when SEEK_CUR is used.
		 */
		lstart = fl->l_start;
		break;
	case SEEK_END:
		/* need to flush, and refetch attributes to make */
		/* sure we have the correct end of file offset   */
		if ((error = nfs_node_lock(np)))
			return (error);
		modified = (np->n_flag & NMODIFIED);
		nfs_node_unlock(np);
		if (modified && ((error = nfs_vinvalbuf(vp, V_SAVE, ctx, 1))))
			return (error);
		if ((error = nfs_getattr(np, NULL, ctx, NGA_UNCACHED)))
			return (error);
		nfs_data_lock(np, NFS_DATA_LOCK_SHARED);
		if ((np->n_size > OFF_MAX) ||
		    ((fl->l_start > 0) && (np->n_size > (u_quad_t)(OFF_MAX - fl->l_start))))
			error = EOVERFLOW;
		lstart = np->n_size + fl->l_start;
		nfs_data_unlock(np);
		if (error)
			return (error);
		break;
	default:
		return (EINVAL);
	}
	if (lstart < 0)
		return (EINVAL);
	start = lstart;
	if (fl->l_len == 0) {
		end = UINT64_MAX;
	} else if (fl->l_len > 0) {
		if ((fl->l_len - 1) > (OFF_MAX - lstart))
			return (EOVERFLOW);
		end = start - 1 + fl->l_len;
	} else { /* l_len is negative */
		if ((lstart + fl->l_len) < 0)
			return (EINVAL);
		end = start - 1;
		start += fl->l_len;
	}
	if ((nmp->nm_vers == NFS_VER2) && ((start > INT32_MAX) || (fl->l_len && (end > INT32_MAX))))
		return (EINVAL);

	style = (flags & F_FLOCK) ? NFS_FILE_LOCK_STYLE_FLOCK : NFS_FILE_LOCK_STYLE_POSIX;
	if ((style == NFS_FILE_LOCK_STYLE_FLOCK) && ((start != 0) || (end != UINT64_MAX)))
		return (EINVAL);

	/* find the lock owner, alloc if not unlock */
	nlop = nfs_lock_owner_find(np, vfs_context_proc(ctx), (op != F_UNLCK));
	if (!nlop) {
		error = (op == F_UNLCK) ? 0 : ENOMEM;
		if (error)
			NP(np, "nfs_vnop_advlock: no lock owner, error %d", error);
		goto out;
	}

	if (op == F_GETLK) {
		error = nfs_advlock_getlock(np, nlop, fl, start, end, ctx);
	} else {
		/* find the open owner */
		noop = nfs_open_owner_find(nmp, vfs_context_ucred(ctx), 0);
		if (!noop) {
			NP(np, "nfs_vnop_advlock: no open owner %d", kauth_cred_getuid(vfs_context_ucred(ctx)));
			error = EPERM;
			goto out;
		}
		/* find the open file */
restart:
		error = nfs_open_file_find(np, noop, &nofp, 0, 0, 0);
		if (error)
			error = EBADF;
		if (!error && (nofp->nof_flags & NFS_OPEN_FILE_LOST)) {
			NP(np, "nfs_vnop_advlock: LOST %d", kauth_cred_getuid(nofp->nof_owner->noo_cred));
			error = EIO;
		}
		if (!error && (nofp->nof_flags & NFS_OPEN_FILE_REOPEN)) {
			error = nfs4_reopen(nofp, ((op == F_UNLCK) ? NULL : vfs_context_thread(ctx)));
			nofp = NULL;
			if (!error)
				goto restart;
		}
		if (error) {
			NP(np, "nfs_vnop_advlock: no open file %d, %d", error, kauth_cred_getuid(noop->noo_cred));
			goto out;
		}
		if (op == F_UNLCK) {
			error = nfs_advlock_unlock(np, nofp, nlop, start, end, style, ctx);
		} else if ((op == F_SETLK) || (op == F_SETLKW)) {
			if ((op == F_SETLK) && (flags & F_WAIT))
				op = F_SETLKW;
			error = nfs_advlock_setlock(np, nofp, nlop, op, start, end, style, fl->l_type, ctx);
		} else {
			/* not getlk, unlock or lock? */
			error = EINVAL;
		}
	}

out:
	if (nlop)
		nfs_lock_owner_rele(nlop);
	if (noop)
		nfs_open_owner_rele(noop);
	return (error);
}