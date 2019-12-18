#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode {int dummy; } ;
struct uio {int /*<<< orphan*/  uio_offset; } ;
struct fileproc {TYPE_1__* f_fglob; } ;
typedef  scalar_t__ off_t ;
struct TYPE_3__ {int fg_flag; int /*<<< orphan*/  fg_offset; scalar_t__ fg_data; } ;

/* Variables and functions */
 int FENCRYPTED ; 
 int FNOCACHE ; 
 int FNONBLOCK ; 
 int FNORDAHEAD ; 
 int FOF_OFFSET ; 
 int FUNENCRYPTED ; 
 int IO_ENCRYPTED ; 
 int IO_EVTONLY ; 
 int IO_NDELAY ; 
 int IO_NOCACHE ; 
 int IO_RAOFF ; 
 int IO_SKIP_ENCRYPTION ; 
 int IO_SYSCALL_DISPATCH ; 
 int O_EVTONLY ; 
 int VNOP_READ (struct vnode*,struct uio*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 int mac_vnode_check_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode*) ; 
 scalar_t__ uio_resid (struct uio*) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_offset_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vn_offset_unlock (TYPE_1__*) ; 
 int vn_read_swapfile (struct vnode*,struct uio*) ; 
 int vnode_getwithref (struct vnode*) ; 
 scalar_t__ vnode_isnocache (struct vnode*) ; 
 scalar_t__ vnode_isswap (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 
 scalar_t__ vnode_vtype (struct vnode*) ; 

__attribute__((used)) static int
vn_read(struct fileproc *fp, struct uio *uio, int flags, vfs_context_t ctx)
{
	struct vnode *vp;
	int error;
	int ioflag;
	off_t count;
	int offset_locked = 0;

	vp = (struct vnode *)fp->f_fglob->fg_data;
	if ( (error = vnode_getwithref(vp)) ) {
		return(error);
	}

#if CONFIG_MACF
	error = mac_vnode_check_read(ctx, vfs_context_ucred(ctx), vp);
	if (error) {
		(void)vnode_put(vp);
		return (error);
	}
#endif

	/* This signals to VNOP handlers that this read came from a file table read */
	ioflag = IO_SYSCALL_DISPATCH;

	if (fp->f_fglob->fg_flag & FNONBLOCK)
		ioflag |= IO_NDELAY;
	if ((fp->f_fglob->fg_flag & FNOCACHE) || vnode_isnocache(vp))
	    ioflag |= IO_NOCACHE;
	if (fp->f_fglob->fg_flag & FENCRYPTED) {
		ioflag |= IO_ENCRYPTED;
	}
	if (fp->f_fglob->fg_flag & FUNENCRYPTED) {
		ioflag |= IO_SKIP_ENCRYPTION;
	}
	if (fp->f_fglob->fg_flag & O_EVTONLY) {
		ioflag |= IO_EVTONLY;
	}
	if (fp->f_fglob->fg_flag & FNORDAHEAD)
	    ioflag |= IO_RAOFF;

	if ((flags & FOF_OFFSET) == 0) {
		if ((vnode_vtype(vp) == VREG) && !vnode_isswap(vp)) {
			vn_offset_lock(fp->f_fglob);
			offset_locked = 1;
		}
		uio->uio_offset = fp->f_fglob->fg_offset;
	}
	count = uio_resid(uio);

	if (vnode_isswap(vp) && !(IO_SKIP_ENCRYPTION & ioflag)) {

		/* special case for swap files */
		error = vn_read_swapfile(vp, uio);
	} else {
		error = VNOP_READ(vp, uio, ioflag, ctx);
	}

	if ((flags & FOF_OFFSET) == 0) {
		fp->f_fglob->fg_offset += count - uio_resid(uio);
		if (offset_locked) {
			vn_offset_unlock(fp->f_fglob);
			offset_locked = 0;
		}
	}

	(void)vnode_put(vp);
	return (error);
}