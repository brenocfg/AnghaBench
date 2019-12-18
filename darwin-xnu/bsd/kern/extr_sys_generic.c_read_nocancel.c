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
typedef  int /*<<< orphan*/  user_ssize_t ;
struct vfs_context {int /*<<< orphan*/  vc_ucred; } ;
struct read_nocancel_args {int fd; int /*<<< orphan*/  nbyte; int /*<<< orphan*/  cbuf; } ;
struct proc {int dummy; } ;
struct fileproc {TYPE_1__* f_fglob; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int /*<<< orphan*/  fg_cred; } ;

/* Variables and functions */
 int dofileread (struct vfs_context*,struct fileproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  donefileread (struct proc*,struct fileproc*,int) ; 
 int preparefileread (struct proc*,struct fileproc**,int,int /*<<< orphan*/ ) ; 
 struct vfs_context* vfs_context_current () ; 

int
read_nocancel(struct proc *p, struct read_nocancel_args *uap, user_ssize_t *retval)
{
	struct fileproc *fp;
	int error;
	int fd = uap->fd;
	struct vfs_context context;

	if ( (error = preparefileread(p, &fp, fd, 0)) )
	        return (error);

	context = *(vfs_context_current());
	context.vc_ucred = fp->f_fglob->fg_cred;

	error = dofileread(&context, fp, uap->cbuf, uap->nbyte,
			   (off_t)-1, 0, retval);

	donefileread(p, fp, fd);

	return (error);
}