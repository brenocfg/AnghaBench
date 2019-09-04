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
typedef  int u_int32_t ;
typedef  int u_int ;
struct proc {int /*<<< orphan*/  p_fpdrainwait; struct filedesc* p_fd; } ;
struct fileproc {int /*<<< orphan*/  f_iocount; } ;
struct filedesc {int fd_nfiles; int* fd_ofileflags; struct fileproc** fd_ofiles; } ;

/* Variables and functions */
 int EBADF ; 
 int EIO ; 
 int NFDBITS ; 
 int UF_RESERVED ; 
 int ffs (int) ; 
 int howmany (int,int) ; 
 int /*<<< orphan*/  proc_fdlock (struct proc*) ; 
 int /*<<< orphan*/  proc_fdunlock (struct proc*) ; 
 int /*<<< orphan*/  seldrop_locked (struct proc*,int*,int,int,int*,int) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
selcount(struct proc *p, u_int32_t *ibits, int nfd, int *countp)
{
	struct filedesc *fdp = p->p_fd;
	int msk, i, j, fd;
	u_int32_t bits;
	struct fileproc *fp;
	int n = 0;
	u_int32_t *iptr;
	u_int nw;
	int error=0; 
	int dropcount;
	int need_wakeup = 0;

	/*
	 * Problems when reboot; due to MacOSX signal probs
	 * in Beaker1C ; verify that the p->p_fd is valid
	 */
	if (fdp == NULL) {
		*countp = 0;
		return(EIO);
	}
	nw = howmany(nfd, NFDBITS);

	proc_fdlock(p);
	for (msk = 0; msk < 3; msk++) {
		iptr = (u_int32_t *)&ibits[msk * nw];
		for (i = 0; i < nfd; i += NFDBITS) {
			bits = iptr[i/NFDBITS];
			while ((j = ffs(bits)) && (fd = i + --j) < nfd) {
				bits &= ~(1 << j);

				if (fd < fdp->fd_nfiles)
					fp = fdp->fd_ofiles[fd];
				else
					fp = NULL;

				if (fp == NULL ||
					(fdp->fd_ofileflags[fd] & UF_RESERVED)) {
						*countp = 0;
						error = EBADF;
						goto bad;
				}
				fp->f_iocount++;
				n++;
			}
		}
	}
	proc_fdunlock(p);

	*countp = n;
	return (0);

bad:
	dropcount = 0;
	
	if (n == 0)
		goto out;
	/* Ignore error return; it's already EBADF */
	(void)seldrop_locked(p, ibits, nfd, n, &need_wakeup, 1);

out:
	proc_fdunlock(p);
	if (need_wakeup) {
		wakeup(&p->p_fpdrainwait);
	}
	return(error);
}