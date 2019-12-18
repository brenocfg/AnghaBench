#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  TYPE_2__* uthread_t ;
typedef  scalar_t__ thread_t ;
struct mount {int dummy; } ;
struct filedesc {TYPE_1__* fd_cdir; } ;
struct fchdir_args {int fd; } ;
typedef  TYPE_3__* proc_t ;
struct TYPE_19__ {int /*<<< orphan*/  p_flag; struct filedesc* p_fd; } ;
struct TYPE_18__ {TYPE_1__* uu_cdir; } ;
struct TYPE_17__ {scalar_t__ v_type; struct mount* v_mountedhere; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_VNODE1 ; 
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,...) ; 
 int EACCES ; 
 int EBADF ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  KAUTH_VNODE_SEARCH ; 
 int /*<<< orphan*/  LK_NOWAIT ; 
 TYPE_1__* NULLVP ; 
 int /*<<< orphan*/  OSBitOrAtomic (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  P_THCWD ; 
 scalar_t__ VDIR ; 
 int VFS_ROOT (struct mount*,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  file_drop (int) ; 
 int file_vnode (int,TYPE_1__**) ; 
 TYPE_2__* get_bsdthread_info (scalar_t__) ; 
 int mac_vnode_check_chdir (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  proc_fdlock (TYPE_3__*) ; 
 int /*<<< orphan*/  proc_fdunlock (TYPE_3__*) ; 
 scalar_t__ vfs_busy (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 scalar_t__ vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_unbusy (struct mount*) ; 
 int vnode_authorize (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vnode_getwithref (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_put (TYPE_1__*) ; 
 int vnode_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  vnpath ; 

__attribute__((used)) static int
common_fchdir(proc_t p, struct fchdir_args *uap, int per_thread)
{
	struct filedesc *fdp = p->p_fd;
	vnode_t vp;
	vnode_t tdp;
	vnode_t tvp;
	struct mount *mp;
	int error;
	vfs_context_t ctx = vfs_context_current();

	AUDIT_ARG(fd, uap->fd);
	if (per_thread && uap->fd == -1) {
		/*
		 * Switching back from per-thread to per process CWD; verify we
		 * in fact have one before proceeding.  The only success case
		 * for this code path is to return 0 preemptively after zapping
		 * the thread structure contents.
		 */
		thread_t th = vfs_context_thread(ctx);
		if (th) {
			uthread_t uth = get_bsdthread_info(th);
			tvp = uth->uu_cdir;
			uth->uu_cdir = NULLVP;
			if (tvp != NULLVP) {
				vnode_rele(tvp);
				return (0);
			}
		}
		return (EBADF);
	}

	if ( (error = file_vnode(uap->fd, &vp)) )
		return(error);
	if ( (error = vnode_getwithref(vp)) ) {
	        file_drop(uap->fd);
		return(error);
	}

	AUDIT_ARG(vnpath, vp, ARG_VNODE1);

	if (vp->v_type != VDIR) {
		error = ENOTDIR;
		goto out;
	}

#if CONFIG_MACF
	error = mac_vnode_check_chdir(ctx, vp);
	if (error)
		goto out;
#endif
	error = vnode_authorize(vp, NULL, KAUTH_VNODE_SEARCH, ctx);
	if (error)
		goto out;

	while (!error && (mp = vp->v_mountedhere) != NULL) {
		if (vfs_busy(mp, LK_NOWAIT)) {
			error = EACCES;
			goto out;
		}
		error = VFS_ROOT(mp, &tdp, ctx);
		vfs_unbusy(mp);
		if (error)
			break;
		vnode_put(vp);
		vp = tdp;
	}
	if (error)
		goto out;
	if ( (error = vnode_ref(vp)) )
	        goto out;
	vnode_put(vp);

	if (per_thread) {
		thread_t th = vfs_context_thread(ctx);
		if (th) {
			uthread_t uth = get_bsdthread_info(th);
			tvp = uth->uu_cdir;
			uth->uu_cdir = vp;
			OSBitOrAtomic(P_THCWD, &p->p_flag);
		} else {
			vnode_rele(vp);
			return (ENOENT);
		}
	} else {
		proc_fdlock(p);
		tvp = fdp->fd_cdir;
		fdp->fd_cdir = vp;
		proc_fdunlock(p);
	}

	if (tvp)
	        vnode_rele(tvp);
	file_drop(uap->fd);

	return (0);
out:
	vnode_put(vp);
	file_drop(uap->fd);

	return(error);
}