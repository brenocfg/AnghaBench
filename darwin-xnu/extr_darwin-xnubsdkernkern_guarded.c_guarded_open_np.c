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
struct vnode_attr {int dummy; } ;
struct nameidata {int dummy; } ;
struct guarded_open_np_args {int flags; int guardflags; int mode; int /*<<< orphan*/  path; int /*<<< orphan*/  guard; } ;
struct gfp_crarg {int gca_attrs; scalar_t__ gca_guard; } ;
struct filedesc {int fd_cmask; } ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int ACCESSPERMS ; 
 int ALLPERMS ; 
 int AUDITVNPATH1 ; 
 int EINVAL ; 
 int FOLLOW ; 
 int GUARD_CLOSE ; 
 int GUARD_DUP ; 
 int GUARD_FILEPORT ; 
 int GUARD_SOCKET_IPC ; 
 int GUARD_WRITE ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_OPEN ; 
 int O_CLOEXEC ; 
 int O_CLOFORK ; 
 int S_ISTXT ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_SET (struct vnode_attr*,int /*<<< orphan*/ ,int) ; 
 int copyin (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  guarded_fileproc_alloc_init ; 
 int open1 (int /*<<< orphan*/ ,struct nameidata*,int,struct vnode_attr*,int /*<<< orphan*/ ,struct gfp_crarg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  va_mode ; 
 int /*<<< orphan*/  vfs_context_current () ; 

int
guarded_open_np(proc_t p, struct guarded_open_np_args *uap, int32_t *retval)
{
	if ((uap->flags & O_CLOEXEC) == 0)
		return (EINVAL);

#define GUARD_REQUIRED (GUARD_DUP)
#define GUARD_ALL      (GUARD_REQUIRED |	\
			(GUARD_CLOSE | GUARD_SOCKET_IPC | GUARD_FILEPORT | GUARD_WRITE))

	if (((uap->guardflags & GUARD_REQUIRED) != GUARD_REQUIRED) ||
	    ((uap->guardflags & ~GUARD_ALL) != 0))
		return (EINVAL);

	int error;
	struct gfp_crarg crarg = {
		.gca_attrs = uap->guardflags
	};

	if ((error = copyin(uap->guard,
	    &(crarg.gca_guard), sizeof (crarg.gca_guard))) != 0)
		return (error);

	/*
	 * Disallow certain guard values -- is zero enough?
	 */
	if (crarg.gca_guard == 0)
		return (EINVAL);

	struct filedesc *fdp = p->p_fd;
	struct vnode_attr va;
	struct nameidata nd;
	vfs_context_t ctx = vfs_context_current();
	int cmode;

	VATTR_INIT(&va);
	cmode = ((uap->mode & ~fdp->fd_cmask) & ALLPERMS) & ~S_ISTXT;
	VATTR_SET(&va, va_mode, cmode & ACCESSPERMS);

	NDINIT(&nd, LOOKUP, OP_OPEN, FOLLOW | AUDITVNPATH1, UIO_USERSPACE,
	       uap->path, ctx);

	return (open1(ctx, &nd, uap->flags | O_CLOFORK, &va,
	    guarded_fileproc_alloc_init, &crarg, retval));
}