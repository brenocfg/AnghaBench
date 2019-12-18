#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* uthread_t ;
typedef  int u_int32_t ;
typedef  int u_int ;
struct proc {scalar_t__ p_fpdrainwait; struct filedesc* p_fd; } ;
struct fileproc {scalar_t__ f_iocount; int f_flags; } ;
struct filedesc {struct fileproc** fd_ofiles; } ;
struct _select_data {int /*<<< orphan*/ * wqp; } ;
struct TYPE_4__ {struct _select_data uus_select_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  uu_wqset; TYPE_1__ uu_save; } ;

/* Variables and functions */
 int EBADF ; 
 int EIO ; 
 int FP_SELCONFLICT ; 
 int NFDBITS ; 
 int /*<<< orphan*/  current_thread () ; 
 int ffs (int) ; 
 TYPE_2__* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int howmany (int,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  selunlinkfp (struct fileproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
seldrop_locked(struct proc *p, u_int32_t *ibits, int nfd, int lim, int *need_wakeup, int fromselcount)
{
	struct filedesc *fdp = p->p_fd;
	int msk, i, j, nc, fd;
	u_int32_t bits;
	struct fileproc *fp;
	u_int32_t *iptr;
	u_int nw;
	int error = 0;
	int dropcount = 0;
	uthread_t uth = get_bsdthread_info(current_thread());
	struct _select_data *seldata;

	*need_wakeup = 0;

	/*
	 * Problems when reboot; due to MacOSX signal probs
	 * in Beaker1C ; verify that the p->p_fd is valid
	 */
	if (fdp == NULL) {
		return(EIO);
	}

	nw = howmany(nfd, NFDBITS);
	seldata = &uth->uu_save.uus_select_data;

	nc = 0;
	for (msk = 0; msk < 3; msk++) {
		iptr = (u_int32_t *)&ibits[msk * nw];
		for (i = 0; i < nfd; i += NFDBITS) {
			bits = iptr[i/NFDBITS];
			while ((j = ffs(bits)) && (fd = i + --j) < nfd) {
				bits &= ~(1 << j);
				fp = fdp->fd_ofiles[fd];
				/*
				 * If we've already dropped as many as were
				 * counted/scanned, then we are done.  
				 */
				if ((fromselcount != 0) && (++dropcount > lim))
					goto done;

				/*
				 * unlink even potentially NULL fileprocs.
				 * If the FD was closed from under us, we
				 * still need to cleanup the waitq links!
				 */
				selunlinkfp(fp,
					    seldata->wqp ? seldata->wqp[nc] : 0,
					    uth->uu_wqset);

				nc++;

				if (fp == NULL) {
					/* skip (now) bad fds */
					error = EBADF;
					continue;
				}

				fp->f_iocount--;
				if (fp->f_iocount < 0)
					panic("f_iocount overdecrement!");

				if (fp->f_iocount == 0) {
					/*
					 * The last iocount is responsible for clearing
					 * selconfict flag - even if we didn't set it -
					 * and is also responsible for waking up anyone
					 * waiting on iocounts to drain.
					 */
					if (fp->f_flags & FP_SELCONFLICT)
						fp->f_flags &= ~FP_SELCONFLICT;
					if (p->p_fpdrainwait) {
						p->p_fpdrainwait = 0;
						*need_wakeup = 1;
					}
				}
			}
		}
	}
done:
	return (error);
}