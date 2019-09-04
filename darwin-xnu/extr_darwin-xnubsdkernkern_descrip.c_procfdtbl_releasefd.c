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
struct proc {TYPE_1__* p_fd; } ;
struct fileproc {int dummy; } ;
struct TYPE_2__ {int* fd_ofileflags; struct fileproc** fd_ofiles; } ;

/* Variables and functions */
 int UF_RESERVED ; 
 int UF_RESVWAIT ; 
 int /*<<< orphan*/  wakeup (TYPE_1__**) ; 

void
procfdtbl_releasefd(struct proc * p, int fd, struct fileproc * fp)
{
	if (fp != NULL)
        	p->p_fd->fd_ofiles[fd] = fp;
        p->p_fd->fd_ofileflags[fd] &= ~UF_RESERVED;
	if ((p->p_fd->fd_ofileflags[fd] & UF_RESVWAIT) == UF_RESVWAIT) {
		p->p_fd->fd_ofileflags[fd] &= ~UF_RESVWAIT;
		wakeup(&p->p_fd);
	}
}