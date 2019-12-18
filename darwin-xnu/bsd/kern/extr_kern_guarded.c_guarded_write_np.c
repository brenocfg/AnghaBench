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
typedef  int /*<<< orphan*/  uguard ;
struct vfs_context {int /*<<< orphan*/  vc_ucred; } ;
struct proc {int dummy; } ;
struct guarded_write_np_args {int fd; int /*<<< orphan*/  nbyte; int /*<<< orphan*/  cbuf; int /*<<< orphan*/  guard; } ;
struct guarded_fileproc {int dummy; } ;
struct fileproc {int f_flag; TYPE_1__* f_fglob; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  guardid_t ;
struct TYPE_2__ {int /*<<< orphan*/  fg_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int,int) ; 
 int EBADF ; 
 int FWRITE ; 
 struct fileproc* GFP_TO_FP (struct guarded_fileproc*) ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int dofilewrite (struct vfs_context*,struct fileproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  fp_drop (struct proc*,int,struct fileproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fp_drop_written (struct proc*,int,struct fileproc*) ; 
 int fp_lookup_guarded (struct proc*,int,int /*<<< orphan*/ ,struct guarded_fileproc**,int /*<<< orphan*/ ) ; 
 struct vfs_context* vfs_context_current () ; 

int
guarded_write_np(struct proc *p, struct guarded_write_np_args *uap, user_ssize_t *retval)
{
	int error;      
	int fd = uap->fd;
	guardid_t uguard;
	struct fileproc *fp;
	struct guarded_fileproc *gfp;
	bool wrote_some = false;

	AUDIT_ARG(fd, fd);

	if ((error = copyin(uap->guard, &uguard, sizeof (uguard))) != 0)
		return (error);

	error = fp_lookup_guarded(p, fd, uguard, &gfp, 0);
	if (error)
		return(error);

	fp = GFP_TO_FP(gfp);
	if ((fp->f_flag & FWRITE) == 0) {
		error = EBADF;
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