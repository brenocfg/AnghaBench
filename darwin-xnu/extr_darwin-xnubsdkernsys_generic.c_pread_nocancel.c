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
struct proc {int dummy; } ;
struct pread_nocancel_args {int fd; int offset; int /*<<< orphan*/  nbyte; int /*<<< orphan*/  buf; } ;
struct fileproc {TYPE_1__* f_fglob; } ;
struct TYPE_2__ {int /*<<< orphan*/  fg_cred; } ;

/* Variables and functions */
 int BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_BSD_SC_EXTENDED_INFO ; 
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  FOF_OFFSET ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_pread ; 
 int dofileread (struct vfs_context*,struct fileproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  donefileread (struct proc*,struct fileproc*,int) ; 
 int preparefileread (struct proc*,struct fileproc**,int,int) ; 
 struct vfs_context* vfs_context_current () ; 

int
pread_nocancel(struct proc *p, struct pread_nocancel_args *uap, user_ssize_t *retval)
{
	struct fileproc *fp = NULL;	/* fp set by preparefileread() */
	int fd = uap->fd;
	int error;
	struct vfs_context context;

	if ( (error = preparefileread(p, &fp, fd, 1)) )
		goto out;

	context = *(vfs_context_current());
	context.vc_ucred = fp->f_fglob->fg_cred;

	error = dofileread(&context, fp, uap->buf, uap->nbyte,
			uap->offset, FOF_OFFSET, retval);
	
	donefileread(p, fp, fd);

	KERNEL_DEBUG_CONSTANT((BSDDBG_CODE(DBG_BSD_SC_EXTENDED_INFO, SYS_pread) | DBG_FUNC_NONE),
	      uap->fd, uap->nbyte, (unsigned int)((uap->offset >> 32)), (unsigned int)(uap->offset), 0);

out:
	return (error);
}