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
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  u_long ;
struct vnode {int v_type; int /*<<< orphan*/  v_rdev; } ;
struct session {int /*<<< orphan*/  s_ttyvid; struct vnode* s_ttyvp; } ;
struct fileproc {TYPE_1__* f_fglob; } ;
typedef  int off_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_6__ {int d_type; } ;
struct TYPE_5__ {int d_type; } ;
struct TYPE_4__ {int fg_offset; int /*<<< orphan*/  fg_flag; scalar_t__ fg_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DKIOCSETBLOCKSIZE ; 
 int ENOTTY ; 
 int ENXIO ; 
 int EPERM ; 
 int /*<<< orphan*/  FIOASYNC ; 
 int /*<<< orphan*/  FIODTYPE ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  FIONREAD ; 
 int /*<<< orphan*/  TIOCSCTTY ; 
#define  VBLK 132 
#define  VCHR 131 
#define  VDIR 130 
#define  VFIFO 129 
 int VNOP_IOCTL (struct vnode*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  VREG 128 
 TYPE_3__* bdevsw ; 
 TYPE_2__* cdevsw ; 
 int mac_vnode_check_ioctl (int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ) ; 
 size_t major (int /*<<< orphan*/ ) ; 
 size_t nblkdev ; 
 size_t nchrdev ; 
 struct session* proc_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_lock (struct session*) ; 
 int /*<<< orphan*/  session_rele (struct session*) ; 
 int /*<<< orphan*/  session_unlock (struct session*) ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 
 int vnode_getwithref (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 
 int vnode_size (struct vnode*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_vid (struct vnode*) ; 

__attribute__((used)) static int
vn_ioctl(struct fileproc *fp, u_long com, caddr_t data, vfs_context_t ctx)
{
	struct vnode *vp = ((struct vnode *)fp->f_fglob->fg_data);
	off_t file_size;
	int error;
	struct vnode *ttyvp;
	struct session * sessp;
	
	if ( (error = vnode_getwithref(vp)) ) {
		return(error);
	}

#if CONFIG_MACF
	error = mac_vnode_check_ioctl(ctx, vp, com);
	if (error)
		goto out;
#endif

	switch (vp->v_type) {
	case VREG:
	case VDIR:
		if (com == FIONREAD) {
			if ((error = vnode_size(vp, &file_size, ctx)) != 0)
				goto out;
			*(int *)data = file_size - fp->f_fglob->fg_offset;
			goto out;
		}
		if (com == FIONBIO || com == FIOASYNC) {	/* XXX */
			goto out;
		}
		/* fall into ... */

	default:
		error = ENOTTY;
		goto out;

	case VFIFO:
	case VCHR:
	case VBLK:

		/* Should not be able to set block size from user space */
		if (com == DKIOCSETBLOCKSIZE) {
			error = EPERM;
			goto out;
		}

		if (com == FIODTYPE) {
			if (vp->v_type == VBLK) {
				if (major(vp->v_rdev) >= nblkdev) {
					error = ENXIO;
					goto out;
				}
				*(int *)data = bdevsw[major(vp->v_rdev)].d_type;

			} else if (vp->v_type == VCHR) {
				if (major(vp->v_rdev) >= nchrdev) {
					error = ENXIO;
					goto out;
				}
				*(int *)data = cdevsw[major(vp->v_rdev)].d_type;
			} else {
				error = ENOTTY;
				goto out;
			}
			goto out;
		}
		error = VNOP_IOCTL(vp, com, data, fp->f_fglob->fg_flag, ctx);

		if (error == 0 && com == TIOCSCTTY) {
			sessp = proc_session(vfs_context_proc(ctx));

			session_lock(sessp);
			ttyvp = sessp->s_ttyvp;
			sessp->s_ttyvp = vp;
			sessp->s_ttyvid = vnode_vid(vp);
			session_unlock(sessp);
			session_rele(sessp);
		}
	}
out:
	(void)vnode_put(vp);
	return(error);
}