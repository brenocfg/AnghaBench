#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode_attr {int dummy; } ;
struct ftruncate_args {int fd; scalar_t__ length; } ;
struct fileproc {TYPE_1__* f_fglob; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int fg_flag; int /*<<< orphan*/  fg_cred; scalar_t__ fg_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_VNODE1 ; 
 int /*<<< orphan*/  AUDIT_ARG (int,int,...) ; 
#define  DTYPE_PSXSHM 129 
#define  DTYPE_VNODE 128 
 int EINVAL ; 
 int FILEGLOB_DTYPE (TYPE_1__*) ; 
 int FWRITE ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_SET (struct vnode_attr*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  file_drop (int) ; 
 int fp_lookup (int /*<<< orphan*/ ,int,struct fileproc**,int /*<<< orphan*/ ) ; 
 int mac_vnode_check_truncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mac_vnode_notify_truncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int pshm_truncate (int /*<<< orphan*/ ,struct fileproc*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  va_data_size ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int vnode_getwithref (scalar_t__) ; 
 int /*<<< orphan*/  vnode_put (scalar_t__) ; 
 int vnode_setattr (scalar_t__,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnpath ; 
 int /*<<< orphan*/  vnpath_withref ; 

int
ftruncate(proc_t p, struct ftruncate_args *uap, int32_t *retval)
{
	vfs_context_t ctx = vfs_context_current();
	struct vnode_attr va;
	vnode_t vp;
	struct fileproc *fp;
	int error ;
	int fd = uap->fd;

	AUDIT_ARG(fd, uap->fd);
	if (uap->length < 0)
		return(EINVAL);

	if ( (error = fp_lookup(p,fd,&fp,0)) ) {
		return(error);
	}

	switch (FILEGLOB_DTYPE(fp->f_fglob)) {
	case DTYPE_PSXSHM:
		error = pshm_truncate(p, fp, uap->fd, uap->length, retval);
		goto out;
	case DTYPE_VNODE:
		break;
	default:
		error = EINVAL;
		goto out;
	}

	vp = (vnode_t)fp->f_fglob->fg_data;

	if ((fp->f_fglob->fg_flag & FWRITE) == 0) {
		AUDIT_ARG(vnpath_withref, vp, ARG_VNODE1);
		error = EINVAL;
		goto out;
	}

	if ((error = vnode_getwithref(vp)) != 0) {
		goto out;
	}

	AUDIT_ARG(vnpath, vp, ARG_VNODE1);

#if CONFIG_MACF
	error = mac_vnode_check_truncate(ctx,
	    fp->f_fglob->fg_cred, vp);
	if (error) {
		(void)vnode_put(vp);
		goto out;
	}
#endif
	VATTR_INIT(&va);
	VATTR_SET(&va, va_data_size, uap->length);
	error = vnode_setattr(vp, &va, ctx);

#if CONFIG_MACF
	if (error == 0)
		mac_vnode_notify_truncate(ctx, fp->f_fglob->fg_cred, vp);
#endif

	(void)vnode_put(vp);
out:
	file_drop(fd);
	return (error);
}