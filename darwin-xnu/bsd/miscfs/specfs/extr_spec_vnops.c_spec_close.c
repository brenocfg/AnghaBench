#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vnop_close_args {int a_fflag; int /*<<< orphan*/  a_context; struct vnode* a_vp; } ;
struct vnode {int v_type; TYPE_1__* v_specinfo; int /*<<< orphan*/  v_rdev; } ;
struct tty {int dummy; } ;
struct session {int /*<<< orphan*/  s_ttypgrpid; struct tty* s_ttyp; int /*<<< orphan*/  s_ttyvid; struct vnode* s_ttyvp; } ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_6__ {int (* d_close ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct proc*) ;} ;
struct TYPE_5__ {int (* d_close ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct proc*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  si_opencount; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_WRITE_DATA ; 
 int EBADF ; 
 int IO_REVOKE ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int /*<<< orphan*/  NO_PID ; 
 struct session* SESSION_NULL ; 
 struct tty* SESSION_TP (struct session*) ; 
 int /*<<< orphan*/  S_IFBLK ; 
 int /*<<< orphan*/  S_IFCHR ; 
 struct tty* TTY_NULL ; 
#define  VBLK 129 
#define  VCHR 128 
 TYPE_3__* bdevsw ; 
 int buf_invalidateblks (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* cdevsw ; 
 int /*<<< orphan*/  devsw_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devsw_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 struct session* proc_session (struct proc*) ; 
 int /*<<< orphan*/  session_lock (struct session*) ; 
 int /*<<< orphan*/  session_rele (struct session*) ; 
 int /*<<< orphan*/  session_unlock (struct session*) ; 
 int spec_fsync_internal (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct proc*) ; 
 int stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct proc*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttyclrpgrphup (struct tty*) ; 
 int /*<<< orphan*/  ttyfree (struct tty*) ; 
 int vcount (struct vnode*) ; 
 struct proc* vfs_context_proc (int /*<<< orphan*/ ) ; 

int
spec_close(struct vnop_close_args *ap)
{
	struct vnode *vp = ap->a_vp;
	dev_t dev = vp->v_rdev;
	int error = 0;
	int flags = ap->a_fflag;
	struct proc *p = vfs_context_proc(ap->a_context);
	struct session *sessp;

	switch (vp->v_type) {

	case VCHR:
		/*
		 * Hack: a tty device that is a controlling terminal
		 * has a reference from the session structure.
		 * We cannot easily tell that a character device is
		 * a controlling terminal, unless it is the closing
		 * process' controlling terminal.  In that case,
		 * if the reference count is 1 (this is the very
		 * last close)
		 */
		sessp = proc_session(p);
		devsw_lock(dev, S_IFCHR);
		if (sessp != SESSION_NULL) {
			if (vp == sessp->s_ttyvp && vcount(vp) == 1) {
				struct tty *tp = TTY_NULL;

				devsw_unlock(dev, S_IFCHR);
				session_lock(sessp);
				if (vp == sessp->s_ttyvp) {
					tp = SESSION_TP(sessp);
					sessp->s_ttyvp = NULL;
					sessp->s_ttyvid = 0;
					sessp->s_ttyp = TTY_NULL;
					sessp->s_ttypgrpid = NO_PID;
				} 
				session_unlock(sessp);

				if (tp != TTY_NULL) {
					/*
					 * We may have won a race with a proc_exit
					 * of the session leader, the winner
					 * clears the flag (even if not set)
					 */
					tty_lock(tp);
					ttyclrpgrphup(tp);
					tty_unlock(tp);

					ttyfree(tp);
				}
				devsw_lock(dev, S_IFCHR);
			}
			session_rele(sessp);
		}

		if (--vp->v_specinfo->si_opencount < 0)
			panic("negative open count (c, %u, %u)", major(dev), minor(dev));

		/*
		 * close on last reference or on vnode revoke call
		 */
		if (vcount(vp) == 0 || (flags & IO_REVOKE) != 0)
			error = cdevsw[major(dev)].d_close(dev, flags, S_IFCHR, p);

		devsw_unlock(dev, S_IFCHR);
		break;

	case VBLK:
		/*
		 * If there is more than one outstanding open, don't
		 * send the close to the device.
		 */
		devsw_lock(dev, S_IFBLK);
		if (vcount(vp) > 1) {
			vp->v_specinfo->si_opencount--;
			devsw_unlock(dev, S_IFBLK);
			return (0);
		}
		devsw_unlock(dev, S_IFBLK);

		/*
		 * On last close of a block device (that isn't mounted)
		 * we must invalidate any in core blocks, so that
		 * we can, for instance, change floppy disks.
		 */
	        if ((error = spec_fsync_internal(vp, MNT_WAIT, ap->a_context)))
		        return (error);

		error = buf_invalidateblks(vp, BUF_WRITE_DATA, 0, 0);
		if (error)
			return (error);

		devsw_lock(dev, S_IFBLK);

		if (--vp->v_specinfo->si_opencount < 0)
			panic("negative open count (b, %u, %u)", major(dev), minor(dev));

		if (vcount(vp) == 0)
			error = bdevsw[major(dev)].d_close(dev, flags, S_IFBLK, p);

		devsw_unlock(dev, S_IFBLK);
		break;

	default:
		panic("spec_close: not special");
		return(EBADF);
	}

	return error;
}