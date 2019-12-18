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
struct proc {struct filedesc* p_fd; } ;
struct filedesc {int fd_freefile; int fd_lastfile; int* fd_ofileflags; int /*<<< orphan*/ ** fd_ofiles; } ;

/* Variables and functions */
 int UF_RESERVED ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  procfdtbl_clearfd (struct proc*,int) ; 

__attribute__((used)) static void
_fdrelse(struct proc * p, int fd)
{
	struct filedesc *fdp = p->p_fd;
	int nfd = 0;

	if (fd < fdp->fd_freefile)
		fdp->fd_freefile = fd;
#if DIAGNOSTIC
	if (fd > fdp->fd_lastfile)
 		panic("fdrelse: fd_lastfile inconsistent");
#endif
	procfdtbl_clearfd(p, fd);

	while ((nfd = fdp->fd_lastfile) > 0 &&
			fdp->fd_ofiles[nfd] == NULL &&
			!(fdp->fd_ofileflags[nfd] & UF_RESERVED))
		/* JMM - What about files with lingering EV_VANISHED knotes? */
		fdp->fd_lastfile--;
}