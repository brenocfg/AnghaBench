#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vnode {int dummy; } ;
struct fpathconf_args {int fd; int /*<<< orphan*/  name; } ;
struct fileproc {int f_type; scalar_t__ f_data; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int file_type_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_VNODE1 ; 
 int /*<<< orphan*/  AUDIT_ARG (int,int,...) ; 
#define  DTYPE_PIPE 130 
#define  DTYPE_SOCKET 129 
#define  DTYPE_VNODE 128 
 int EINVAL ; 
 int /*<<< orphan*/  PIPE_BUF ; 
 int /*<<< orphan*/  _PC_PIPE_BUF ; 
 int /*<<< orphan*/  fp_drop (int /*<<< orphan*/ ,int,struct fileproc*,int /*<<< orphan*/ ) ; 
 int fp_lookup (int /*<<< orphan*/ ,int,struct fileproc**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int vn_pathconf (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vnode_getwithref (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 
 int /*<<< orphan*/  vnpath ; 

int
fpathconf(proc_t p, struct fpathconf_args *uap, int32_t *retval)
{
	int fd = uap->fd;
	struct fileproc *fp;
	struct vnode *vp;
	int error = 0;
	file_type_t type;
	caddr_t data;


	AUDIT_ARG(fd, uap->fd);
	if ( (error = fp_lookup(p, fd, &fp, 0)) )
		return(error);
	type = fp->f_type;
	data = fp->f_data;

	switch (type) {

	case DTYPE_SOCKET:
		if (uap->name != _PC_PIPE_BUF) {
			error = EINVAL;
			goto out;
		}
		*retval = PIPE_BUF;
		error = 0;
		goto out;

	case DTYPE_PIPE:
		if (uap->name != _PC_PIPE_BUF) {
			error = EINVAL;
			goto out;
		}
		*retval = PIPE_BUF;
		error = 0;
		goto out;

	case DTYPE_VNODE:
		vp = (struct vnode *)data;

		if ( (error = vnode_getwithref(vp)) == 0) {
		        AUDIT_ARG(vnpath, vp, ARG_VNODE1);

			error = vn_pathconf(vp, uap->name, retval, vfs_context_current());

			(void)vnode_put(vp);
		}
		goto out;

	default:
		error = EINVAL;
		goto out;

	}
	/*NOTREACHED*/
out:
	fp_drop(p, fd, fp, 0);
	return(error);
}