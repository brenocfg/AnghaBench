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
typedef  struct vnode* vnode_t ;
struct vnode {int v_flag; } ;
struct proc {int dummy; } ;
struct fileproc {int f_flag; scalar_t__ f_type; TYPE_1__* f_fglob; } ;
struct TYPE_2__ {scalar_t__ fg_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int,int) ; 
 scalar_t__ DTYPE_VNODE ; 
 int EBADF ; 
 int ENXIO ; 
 int ESPIPE ; 
 int FREAD ; 
 int VISTTY ; 
 int /*<<< orphan*/  fp_drop (struct proc*,int,struct fileproc*,int) ; 
 int fp_lookup (struct proc*,int,struct fileproc**,int) ; 
 int /*<<< orphan*/  proc_fdlock_spin (struct proc*) ; 
 int /*<<< orphan*/  proc_fdunlock (struct proc*) ; 
 scalar_t__ vnode_isfifo (struct vnode*) ; 

int
preparefileread(struct proc *p, struct fileproc **fp_ret, int fd, int check_for_pread)
{
	vnode_t vp;
	int 	error;
	struct fileproc *fp;

	AUDIT_ARG(fd, fd);

	proc_fdlock_spin(p);

	error = fp_lookup(p, fd, &fp, 1);

	if (error) {
	        proc_fdunlock(p);
		return (error);
	}
	if ((fp->f_flag & FREAD) == 0) {
	        error = EBADF;
		goto out;
	}
	if (check_for_pread && (fp->f_type != DTYPE_VNODE)) {
	        error = ESPIPE;
		goto out;
	}
	if (fp->f_type == DTYPE_VNODE) {
		vp = (struct vnode *)fp->f_fglob->fg_data;

		if (check_for_pread && (vnode_isfifo(vp))) {
			error = ESPIPE;
			goto out;
		} 
		if (check_for_pread && (vp->v_flag & VISTTY)) {
			error = ENXIO;
			goto out;
		}
	}

	*fp_ret = fp;

        proc_fdunlock(p);
	return (0);

out:
	fp_drop(p, fd, fp, 1);
	proc_fdunlock(p);
	return (error);
}