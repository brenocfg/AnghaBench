#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vnode {int dummy; } ;
struct vfs_context {int /*<<< orphan*/  vc_ucred; int /*<<< orphan*/ * vc_thread; } ;
struct flock {int /*<<< orphan*/  l_type; scalar_t__ l_len; scalar_t__ l_start; int /*<<< orphan*/  l_whence; } ;
struct fileproc {int f_flags; } ;
struct fileglob {scalar_t__ fg_count; int /*<<< orphan*/  fg_lock; int /*<<< orphan*/  fg_lflags; int /*<<< orphan*/  fg_flag; scalar_t__ fg_data; int /*<<< orphan*/  fg_cred; } ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {int p_ladvflag; } ;

/* Variables and functions */
 scalar_t__ DTYPE_VNODE ; 
 int /*<<< orphan*/  FG_TERM ; 
 scalar_t__ FILEGLOB_DTYPE (struct fileglob*) ; 
 int FP_WRITTEN ; 
 int /*<<< orphan*/  FWASWRITTEN ; 
 int /*<<< orphan*/  F_POSIX ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int P_LADVLOCK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  VNOP_ADVLOCK (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flock*,int /*<<< orphan*/ ,struct vfs_context*,int /*<<< orphan*/ *) ; 
 TYPE_1__* current_proc () ; 
 int /*<<< orphan*/ * current_thread () ; 
 int /*<<< orphan*/  fg_free (struct fileglob*) ; 
 int fo_close (struct fileglob*,struct vfs_context*) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,struct fileglob*,scalar_t__) ; 
 int /*<<< orphan*/  proc_fdlock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_fdunlock (TYPE_1__*) ; 
 int vnode_getwithref (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 

int
closef_locked(struct fileproc *fp, struct fileglob *fg, proc_t p)
{
	struct vnode *vp;
	struct flock lf;
	struct vfs_context context;
	int error;

	if (fg == NULL) {
		return (0);
	}

	/* Set up context with cred stashed in fg */
	if (p == current_proc())
		context.vc_thread = current_thread();
	else
		context.vc_thread = NULL;
	context.vc_ucred = fg->fg_cred;

	/*
	 * POSIX record locking dictates that any close releases ALL
	 * locks owned by this process.  This is handled by setting
	 * a flag in the unlock to free ONLY locks obeying POSIX
	 * semantics, and not to free BSD-style file locks.
	 * If the descriptor was in a message, POSIX-style locks
	 * aren't passed with the descriptor.
	 */
	if (p && (p->p_ladvflag & P_LADVLOCK) &&
	    DTYPE_VNODE == FILEGLOB_DTYPE(fg)) {
		proc_fdunlock(p);

		lf.l_whence = SEEK_SET;
		lf.l_start = 0;
		lf.l_len = 0;
		lf.l_type = F_UNLCK;
		vp = (struct vnode *)fg->fg_data;

		if ( (error = vnode_getwithref(vp)) == 0 ) {
			(void) VNOP_ADVLOCK(vp, (caddr_t)p, F_UNLCK, &lf, F_POSIX, &context, NULL);
			(void)vnode_put(vp);
		}
		proc_fdlock(p);
	}
	lck_mtx_lock_spin(&fg->fg_lock);
	fg->fg_count--;

	if (fg->fg_count > 0) {
		lck_mtx_unlock(&fg->fg_lock);
		return (0);
	}
#if DIAGNOSTIC
	if (fg->fg_count != 0)
		panic("fg %p: being freed with bad fg_count (%d)", fg, fg->fg_count);
#endif

	if (fp && (fp->f_flags & FP_WRITTEN))
	        fg->fg_flag |= FWASWRITTEN;

	fg->fg_lflags |= FG_TERM;
	lck_mtx_unlock(&fg->fg_lock);

	if (p)
		proc_fdunlock(p);

	/* Since we ensure that fg->fg_ops is always initialized,
	 * it is safe to invoke fo_close on the fg */
	error = fo_close(fg, &context);

	fg_free(fg);

	if (p)
		proc_fdlock(p);

	return(error);
}