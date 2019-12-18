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
typedef  int /*<<< orphan*/  uio_t ;
struct vfs_context {int /*<<< orphan*/  vc_ucred; } ;
struct proc {int dummy; } ;
struct fileproc {scalar_t__ f_type; TYPE_1__* f_fglob; int /*<<< orphan*/  f_cred; } ;
struct TYPE_2__ {int fg_lflags; } ;

/* Variables and functions */
 scalar_t__ DTYPE_SOCKET ; 
 int EINTR ; 
 int EPIPE ; 
 int ERESTART ; 
 int EWOULDBLOCK ; 
 int FG_NOSIGPIPE ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int fo_write (struct fileproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vfs_context*) ; 
 int /*<<< orphan*/  psignal (struct proc*,int /*<<< orphan*/ ) ; 
 scalar_t__ uio_resid (int /*<<< orphan*/ ) ; 
 struct vfs_context* vfs_context_current () ; 

int
wr_uio(struct proc *p, struct fileproc *fp, uio_t uio, user_ssize_t *retval)
{
	int error;
	user_ssize_t count;
	struct vfs_context context = *vfs_context_current();

	count = uio_resid(uio);

	context.vc_ucred = fp->f_cred;
	error = fo_write(fp, uio, 0, &context);
	if (error) {
		if (uio_resid(uio) != count && (error == ERESTART ||
						error == EINTR || error == EWOULDBLOCK))
		        error = 0;
		/* The socket layer handles SIGPIPE */
		if (error == EPIPE && fp->f_type != DTYPE_SOCKET &&
		    (fp->f_fglob->fg_lflags & FG_NOSIGPIPE) == 0)
		        psignal(p, SIGPIPE);
	}
	*retval = count - uio_resid(uio);

	return(error);
}