#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode {scalar_t__ v_type; scalar_t__ v_tag; TYPE_1__* v_mount; } ;
struct uio {scalar_t__ uio_offset; } ;
struct fileproc {TYPE_4__* f_fglob; } ;
typedef  scalar_t__ rlim_t ;
typedef  TYPE_3__* proc_t ;
typedef  int off_t ;
struct TYPE_13__ {int fg_flag; scalar_t__ fg_offset; scalar_t__ fg_data; } ;
struct TYPE_12__ {TYPE_2__* p_rlimit; } ;
struct TYPE_11__ {scalar_t__ rlim_cur; } ;
struct TYPE_10__ {int mnt_flag; } ;

/* Variables and functions */
 int EFBIG ; 
 int EPERM ; 
 int FNOCACHE ; 
 int FNODIRECT ; 
 int FNONBLOCK ; 
 int FOF_OFFSET ; 
 int FOF_PCRED ; 
 int FSINGLE_WRITER ; 
 int IO_APPEND ; 
 int IO_EVTONLY ; 
 int IO_NDELAY ; 
 int IO_NOCACHE ; 
 int IO_NODIRECT ; 
 int IO_SINGLE_WRITER ; 
 int IO_SYNC ; 
 int IO_SYSCALL_DISPATCH ; 
 int IO_UNIT ; 
 int MNT_SYNCHRONOUS ; 
 int O_APPEND ; 
 int O_DSYNC ; 
 int O_EVTONLY ; 
 int O_FSYNC ; 
 size_t RLIMIT_FSIZE ; 
 int /*<<< orphan*/  SIGXFSZ ; 
 scalar_t__ UBCINFOEXISTS (struct vnode*) ; 
 int VNOP_WRITE (struct vnode*,struct uio*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 scalar_t__ VT_NFS ; 
 int /*<<< orphan*/  current_thread () ; 
 int mac_vnode_check_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode*) ; 
 int /*<<< orphan*/  psignal (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubc_setcred (struct vnode*,TYPE_3__*) ; 
 int /*<<< orphan*/  ubc_setthreadcred (struct vnode*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int uio_resid (struct uio*) ; 
 int /*<<< orphan*/  uio_setresid (struct uio*,int) ; 
 TYPE_3__* vfs_context_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_offset_lock (TYPE_4__*) ; 
 int /*<<< orphan*/  vn_offset_unlock (TYPE_4__*) ; 
 int vnode_getwithref (struct vnode*) ; 
 scalar_t__ vnode_isnocache (struct vnode*) ; 
 scalar_t__ vnode_isswap (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 
 scalar_t__ vnode_vtype (struct vnode*) ; 

__attribute__((used)) static int
vn_write(struct fileproc *fp, struct uio *uio, int flags, vfs_context_t ctx)
{
	struct vnode *vp;
	int error, ioflag;
	off_t count;
	int clippedsize = 0;
	int partialwrite=0;
	int residcount, oldcount;
	int offset_locked = 0;
	proc_t p = vfs_context_proc(ctx);

	count = 0;
	vp = (struct vnode *)fp->f_fglob->fg_data;
	if ( (error = vnode_getwithref(vp)) ) {
		return(error);
	}

#if DEVELOPMENT || DEBUG
	/*
	 * XXX VSWAP: Check for entitlements or special flag here
	 * so we can restrict access appropriately.
	 */
#else /* DEVELOPMENT || DEBUG */

	if (vnode_isswap(vp)) {
		(void)vnode_put(vp);
		error = EPERM;
		return (error);
	}
#endif /* DEVELOPMENT || DEBUG */


#if CONFIG_MACF
	error = mac_vnode_check_write(ctx, vfs_context_ucred(ctx), vp);
	if (error) {
		(void)vnode_put(vp);
		return (error);
	}
#endif

	/*
	 * IO_SYSCALL_DISPATCH signals to VNOP handlers that this write came from
	 * a file table write
	 */
	ioflag = (IO_UNIT | IO_SYSCALL_DISPATCH);

	if (vp->v_type == VREG && (fp->f_fglob->fg_flag & O_APPEND))
		ioflag |= IO_APPEND;
	if (fp->f_fglob->fg_flag & FNONBLOCK)
		ioflag |= IO_NDELAY;
	if ((fp->f_fglob->fg_flag & FNOCACHE) || vnode_isnocache(vp))
	        ioflag |= IO_NOCACHE;
	if (fp->f_fglob->fg_flag & FNODIRECT)
		ioflag |= IO_NODIRECT;
	if (fp->f_fglob->fg_flag & FSINGLE_WRITER)
		ioflag |= IO_SINGLE_WRITER;
	if (fp->f_fglob->fg_flag & O_EVTONLY)
		ioflag |= IO_EVTONLY;

	/*
	 * Treat synchronous mounts and O_FSYNC on the fd as equivalent.
	 *
	 * XXX We treat O_DSYNC as O_FSYNC for now, since we can not delay
	 * XXX the non-essential metadata without some additional VFS work;
	 * XXX the intent at this point is to plumb the interface for it.
	 */
	if ((fp->f_fglob->fg_flag & (O_FSYNC|O_DSYNC)) ||
		(vp->v_mount && (vp->v_mount->mnt_flag & MNT_SYNCHRONOUS))) {
		ioflag |= IO_SYNC;
	}

	if ((flags & FOF_OFFSET) == 0) {
		if ((vnode_vtype(vp) == VREG) && !vnode_isswap(vp)) {
			vn_offset_lock(fp->f_fglob);
			offset_locked = 1;
		}
		uio->uio_offset = fp->f_fglob->fg_offset;
		count = uio_resid(uio);
	}
	if (((flags & FOF_OFFSET) == 0) &&
	 	vfs_context_proc(ctx) && (vp->v_type == VREG) &&
            (((rlim_t)(uio->uio_offset + uio_resid(uio)) > p->p_rlimit[RLIMIT_FSIZE].rlim_cur) ||
             ((rlim_t)uio_resid(uio) > (p->p_rlimit[RLIMIT_FSIZE].rlim_cur - uio->uio_offset)))) {
	     	/*
		 * If the requested residual would cause us to go past the
		 * administrative limit, then we need to adjust the residual
		 * down to cause fewer bytes than requested to be written.  If
		 * we can't do that (e.g. the residual is already 1 byte),
		 * then we fail the write with EFBIG.
		 */
		residcount = uio_resid(uio);
            	if ((rlim_t)(uio->uio_offset + uio_resid(uio)) > p->p_rlimit[RLIMIT_FSIZE].rlim_cur) {
			clippedsize =  (uio->uio_offset + uio_resid(uio)) - p->p_rlimit[RLIMIT_FSIZE].rlim_cur;
		} else if ((rlim_t)uio_resid(uio) > (p->p_rlimit[RLIMIT_FSIZE].rlim_cur - uio->uio_offset)) {
			clippedsize = (p->p_rlimit[RLIMIT_FSIZE].rlim_cur - uio->uio_offset);
		}
		if (clippedsize >= residcount) {
			psignal(p, SIGXFSZ);
			error = EFBIG;
			goto error_out;
		}
		partialwrite = 1;
		uio_setresid(uio, residcount-clippedsize);
	}
	if ((flags & FOF_OFFSET) != 0) {
		/* for pwrite, append should  be ignored */
		ioflag &= ~IO_APPEND;
		if (p && (vp->v_type == VREG) &&
            	((rlim_t)uio->uio_offset  >= p->p_rlimit[RLIMIT_FSIZE].rlim_cur)) {
		psignal(p, SIGXFSZ);
		error = EFBIG;
		goto error_out;
	}
		if (p && (vp->v_type == VREG) &&
			((rlim_t)(uio->uio_offset + uio_resid(uio)) > p->p_rlimit[RLIMIT_FSIZE].rlim_cur)) {
			//Debugger("vn_bwrite:overstepping the bounds");
			residcount = uio_resid(uio);
			clippedsize =  (uio->uio_offset + uio_resid(uio)) - p->p_rlimit[RLIMIT_FSIZE].rlim_cur;
			partialwrite = 1;
			uio_setresid(uio, residcount-clippedsize);
		}
	}

	error = VNOP_WRITE(vp, uio, ioflag, ctx);

	if (partialwrite) {
		oldcount = uio_resid(uio);
		uio_setresid(uio, oldcount + clippedsize);
	}

	if ((flags & FOF_OFFSET) == 0) {
		if (ioflag & IO_APPEND)
			fp->f_fglob->fg_offset = uio->uio_offset;
		else
			fp->f_fglob->fg_offset += count - uio_resid(uio);
		if (offset_locked) {
			vn_offset_unlock(fp->f_fglob);
			offset_locked = 0;
		}
	}

	/*
	 * Set the credentials on successful writes
	 */
	if ((error == 0) && (vp->v_tag == VT_NFS) && (UBCINFOEXISTS(vp))) {
		/* 
		 * When called from aio subsystem, we only have the proc from
		 * which to get the credential, at this point, so use that
		 * instead.  This means aio functions are incompatible with
		 * per-thread credentials (aio operations are proxied).  We
		 * can't easily correct the aio vs. settid race in this case
		 * anyway, so we disallow it.
		 */
		if ((flags & FOF_PCRED) == 0) {
			ubc_setthreadcred(vp, p, current_thread());
		} else {
			ubc_setcred(vp, p);
		}
	}
	(void)vnode_put(vp);
	return (error);

error_out:
	if (offset_locked) {
		vn_offset_unlock(fp->f_fglob);
	}
	(void)vnode_put(vp);
	return (error);
}