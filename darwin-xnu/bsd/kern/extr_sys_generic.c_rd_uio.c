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
typedef  scalar_t__ user_ssize_t ;
typedef  int /*<<< orphan*/  uio_t ;
struct vfs_context {int /*<<< orphan*/  vc_ucred; } ;
struct proc {int dummy; } ;
struct fileproc {int /*<<< orphan*/  f_cred; } ;

/* Variables and functions */
 int EINTR ; 
 int ERESTART ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  donefileread (struct proc*,struct fileproc*,int) ; 
 int fo_read (struct fileproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vfs_context*) ; 
 int preparefileread (struct proc*,struct fileproc**,int,int /*<<< orphan*/ ) ; 
 scalar_t__ uio_resid (int /*<<< orphan*/ ) ; 
 struct vfs_context* vfs_context_current () ; 

int
rd_uio(struct proc *p, int fdes, uio_t uio, user_ssize_t *retval)
{
	struct fileproc *fp;
	int error;
	user_ssize_t count;
	struct vfs_context context = *vfs_context_current();

	if ( (error = preparefileread(p, &fp, fdes, 0)) )
	        return (error);

	count = uio_resid(uio);

	context.vc_ucred = fp->f_cred;

	error = fo_read(fp, uio, 0, &context);

	if (error) {
	        if (uio_resid(uio) != count && (error == ERESTART ||
						error == EINTR || error == EWOULDBLOCK))
		        error = 0;
	}
	*retval = count - uio_resid(uio);

	donefileread(p, fp, fdes);

	return (error);
}