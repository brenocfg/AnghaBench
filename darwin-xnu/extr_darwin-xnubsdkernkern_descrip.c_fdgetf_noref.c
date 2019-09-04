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
struct fileproc {int dummy; } ;
struct filedesc {int fd_nfiles; int* fd_ofileflags; struct fileproc** fd_ofiles; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int EBADF ; 
 int UF_RESERVED ; 

int
fdgetf_noref(proc_t p, int fd, struct fileproc **resultfp)
{
	struct filedesc *fdp = p->p_fd;
	struct fileproc *fp;

	if (fd < 0 || fd >= fdp->fd_nfiles ||
			(fp = fdp->fd_ofiles[fd]) == NULL ||
			(fdp->fd_ofileflags[fd] & UF_RESERVED)) {
		return (EBADF);
	}
	if (resultfp)
		*resultfp = fp;
	return (0);
}