#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct vfs_context {int dummy; } ;
struct lseek_args {scalar_t__ offset; int whence; int /*<<< orphan*/  fd; } ;
struct fileproc {TYPE_7__* f_fglob; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_12__ {scalar_t__ fg_offset; } ;
struct TYPE_11__ {scalar_t__ v_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 int EOVERFLOW ; 
 int ESPIPE ; 
 int /*<<< orphan*/  FSIOC_FIOSEEKDATA ; 
 int /*<<< orphan*/  FSIOC_FIOSEEKHOLE ; 
#define  L_INCR 132 
#define  L_SET 131 
#define  L_XTND 130 
 int /*<<< orphan*/  NOTE_NONE ; 
#define  SEEK_DATA 129 
#define  SEEK_HOLE 128 
 scalar_t__ VCHR ; 
 int VNOP_IOCTL (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vfs_context*) ; 
 int /*<<< orphan*/  file_drop (int /*<<< orphan*/ ) ; 
 int fp_getfvp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fileproc**,TYPE_1__**) ; 
 int mac_file_check_change_offset (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int mac_file_check_get_offset (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  post_event_if_success (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct vfs_context* vfs_context_current () ; 
 int /*<<< orphan*/  vfs_context_ucred (struct vfs_context*) ; 
 int vnode_getwithref (TYPE_1__*) ; 
 scalar_t__ vnode_isfifo (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_put (TYPE_1__*) ; 
 int vnode_size (TYPE_1__*,scalar_t__*,struct vfs_context*) ; 

int
lseek(proc_t p, struct lseek_args *uap, off_t *retval)
{
	struct fileproc *fp;
	vnode_t vp;
	struct vfs_context *ctx;
	off_t offset = uap->offset, file_size;
	int error;

	if ( (error = fp_getfvp(p,uap->fd, &fp, &vp)) ) {
	        if (error == ENOTSUP)
		        return (ESPIPE);
		return (error);
	}
	if (vnode_isfifo(vp)) {
		file_drop(uap->fd);
		return(ESPIPE);
	}


	ctx = vfs_context_current();
#if CONFIG_MACF
	if (uap->whence == L_INCR && uap->offset == 0)
		error = mac_file_check_get_offset(vfs_context_ucred(ctx),
		    fp->f_fglob);
	else
		error = mac_file_check_change_offset(vfs_context_ucred(ctx),
		    fp->f_fglob);
	if (error) {
		file_drop(uap->fd);
		return (error);
	}
#endif
	if ( (error = vnode_getwithref(vp)) ) {
		file_drop(uap->fd);
		return(error);
	}

	switch (uap->whence) {
	case L_INCR:
		offset += fp->f_fglob->fg_offset;
		break;
	case L_XTND:
		if ((error = vnode_size(vp, &file_size, ctx)) != 0)
			break;
		offset += file_size;
		break;
	case L_SET:
		break;
	case SEEK_HOLE:
        error = VNOP_IOCTL(vp, FSIOC_FIOSEEKHOLE, (caddr_t)&offset, 0, ctx);
		break;
	case SEEK_DATA:
        error = VNOP_IOCTL(vp, FSIOC_FIOSEEKDATA, (caddr_t)&offset, 0, ctx);
		break;
	default:
		error = EINVAL;
	}
	if (error == 0) {
		if (uap->offset > 0 && offset < 0) {
			/* Incremented/relative move past max size */
			error = EOVERFLOW;
		} else {
			/*
			 * Allow negative offsets on character devices, per
			 * POSIX 1003.1-2001.  Most likely for writing disk
			 * labels.
			 */
			if (offset < 0 && vp->v_type != VCHR) {
				/* Decremented/relative move before start */
				error = EINVAL;
			} else {
				/* Success */
				fp->f_fglob->fg_offset = offset;
				*retval = fp->f_fglob->fg_offset;
			}
		}
	}

	/*
	 * An lseek can affect whether data is "available to read."  Use
	 * hint of NOTE_NONE so no EVFILT_VNODE events fire
	 */
	post_event_if_success(vp, error, NOTE_NONE);
	(void)vnode_put(vp);
	file_drop(uap->fd);
	return (error);
}