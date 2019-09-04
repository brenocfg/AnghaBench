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
typedef  scalar_t__ user_ssize_t ;
struct write_nocancel_args {int fd; int /*<<< orphan*/  nbyte; int /*<<< orphan*/  cbuf; } ;
struct vfs_context {int /*<<< orphan*/  vc_ucred; } ;
struct proc {int dummy; } ;
struct fileproc {int f_flag; TYPE_1__* f_fglob; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int /*<<< orphan*/  fg_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int,int) ; 
 int EBADF ; 
 scalar_t__ FP_ISGUARDED (struct fileproc*,int /*<<< orphan*/ ) ; 
 int FWRITE ; 
 int /*<<< orphan*/  GUARD_WRITE ; 
 int dofilewrite (struct vfs_context*,struct fileproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  fp_drop (struct proc*,int,struct fileproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fp_drop_written (struct proc*,int,struct fileproc*) ; 
 int fp_guard_exception (struct proc*,int,struct fileproc*,int /*<<< orphan*/ ) ; 
 int fp_lookup (struct proc*,int,struct fileproc**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kGUARD_EXC_WRITE ; 
 int /*<<< orphan*/  proc_fdlock (struct proc*) ; 
 int /*<<< orphan*/  proc_fdunlock (struct proc*) ; 
 struct vfs_context* vfs_context_current () ; 

int
write_nocancel(struct proc *p, struct write_nocancel_args *uap, user_ssize_t *retval)
{
	struct fileproc *fp;
	int error;      
	int fd = uap->fd;
	bool wrote_some = false;

	AUDIT_ARG(fd, fd);

	error = fp_lookup(p,fd,&fp,0);
	if (error)
		return(error);
	if ((fp->f_flag & FWRITE) == 0) {
		error = EBADF;
	} else if (FP_ISGUARDED(fp, GUARD_WRITE)) {
		proc_fdlock(p);
		error = fp_guard_exception(p, fd, fp, kGUARD_EXC_WRITE);
		proc_fdunlock(p);
	} else {
		struct vfs_context context = *(vfs_context_current());
		context.vc_ucred = fp->f_fglob->fg_cred;

		error = dofilewrite(&context, fp, uap->cbuf, uap->nbyte,
			(off_t)-1, 0, retval);

		wrote_some = *retval > 0;
	}
	if (wrote_some)
	        fp_drop_written(p, fd, fp);
	else
	        fp_drop(p, fd, fp, 0);
	return(error);  
}