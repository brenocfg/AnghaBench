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
typedef  scalar_t__ uint64_t ;
typedef  int u_int32_t ;
typedef  int u_int ;
struct waitq_set {int dummy; } ;
struct waitq {int dummy; } ;
struct vfs_context {int /*<<< orphan*/  vc_ucred; } ;
struct proc {struct filedesc* p_fd; } ;
struct fileproc {int f_flags; scalar_t__ f_type; scalar_t__ f_ops; int /*<<< orphan*/  f_cred; } ;
struct filedesc {int fd_nfiles; int* fd_ofileflags; struct fileproc** fd_ofiles; } ;
struct _select_data {int count; int /*<<< orphan*/ * wqp; } ;
struct _select {int* ibits; int* obits; } ;
typedef  int int32_t ;

/* Variables and functions */
 int EBADF ; 
 int EIO ; 
 int FP_INSELECT ; 
 int FP_SELCONFLICT ; 
#define  FREAD 129 
#define  FWRITE 128 
 int NFDBITS ; 
 int SEL_FIRSTPASS ; 
 int SEL_SECONDPASS ; 
 int UF_RESERVED ; 
 int ffs (int) ; 
 scalar_t__ fo_select (struct fileproc*,int,scalar_t__*,struct vfs_context*) ; 
 int howmany (int,int) ; 
 int /*<<< orphan*/  proc_fdlock (struct proc*) ; 
 int /*<<< orphan*/  proc_fdunlock (struct proc*) ; 
 int /*<<< orphan*/  sellinkfp (struct fileproc*,void**,struct waitq_set*) ; 
 int /*<<< orphan*/  selunlinkfp (struct fileproc*,int /*<<< orphan*/ ,struct waitq_set*) ; 
 struct vfs_context* vfs_context_current () ; 
 int /*<<< orphan*/  waitq_link_release (scalar_t__) ; 
 scalar_t__ waitq_link_reserve (struct waitq*) ; 
 int /*<<< orphan*/  waitq_set_lazy_init_link (struct waitq_set*) ; 

__attribute__((used)) static int
selscan(struct proc *p, struct _select *sel, struct _select_data * seldata,
	int nfd, int32_t *retval, int sel_pass, struct waitq_set *wqset)
{
	struct filedesc *fdp = p->p_fd;
	int msk, i, j, fd;
	u_int32_t bits;
	struct fileproc *fp;
	int n = 0;		/* count of bits */
	int nc = 0;		/* bit vector offset (nc'th bit) */
	static int flag[3] = { FREAD, FWRITE, 0 };
	u_int32_t *iptr, *optr;
	u_int nw;
	u_int32_t *ibits, *obits;
	uint64_t reserved_link, *rl_ptr = NULL;
	int count;
	struct vfs_context context = *vfs_context_current();

	/*
	 * Problems when reboot; due to MacOSX signal probs
	 * in Beaker1C ; verify that the p->p_fd is valid
	 */
	if (fdp == NULL) {
		*retval=0;
		return(EIO);
	}
	ibits = sel->ibits;
	obits = sel->obits;

	nw = howmany(nfd, NFDBITS);

	count = seldata->count;

	nc = 0;
	if (!count) {
		*retval = 0;
		return 0;
	}

	proc_fdlock(p);
	for (msk = 0; msk < 3; msk++) {
		iptr = (u_int32_t *)&ibits[msk * nw];
		optr = (u_int32_t *)&obits[msk * nw];

		for (i = 0; i < nfd; i += NFDBITS) {
			bits = iptr[i/NFDBITS];

			while ((j = ffs(bits)) && (fd = i + --j) < nfd) {
				bits &= ~(1 << j);

				if (fd < fdp->fd_nfiles)
					fp = fdp->fd_ofiles[fd];
				else
					fp = NULL;

				if (fp == NULL || (fdp->fd_ofileflags[fd] & UF_RESERVED)) {
					/*
					 * If we abort because of a bad
					 * fd, let the caller unwind...
					 */
					proc_fdunlock(p);
					return(EBADF);
				}
				if (sel_pass == SEL_SECONDPASS) {
					reserved_link = 0;
					rl_ptr = NULL;
					selunlinkfp(fp, seldata->wqp[nc], wqset);
				} else {
					reserved_link = waitq_link_reserve((struct waitq *)wqset);
					rl_ptr = &reserved_link;
					if (fp->f_flags & FP_INSELECT)
						/* someone is already in select on this fp */
						fp->f_flags |= FP_SELCONFLICT;
					else
						fp->f_flags |= FP_INSELECT;

					waitq_set_lazy_init_link(wqset);
				}

				context.vc_ucred = fp->f_cred;

				/*
				 * stash this value b/c fo_select may replace
				 * reserved_link with a pointer to a waitq object
				 */
				uint64_t rsvd = reserved_link;

				/* The select; set the bit, if true */
				if (fp->f_ops && fp->f_type
					&& fo_select(fp, flag[msk], rl_ptr, &context)) {
					optr[fd/NFDBITS] |= (1 << (fd % NFDBITS));
					n++;
				}
				if (sel_pass == SEL_FIRSTPASS) {
					waitq_link_release(rsvd);
					/*
					 * If the fp's supporting selinfo structure was linked
					 * to this thread's waitq set, then 'reserved_link'
					 * will have been updated by selrecord to be a pointer
					 * to the selinfo's waitq.
					 */
					if (reserved_link == rsvd)
						rl_ptr = NULL; /* fo_select never called selrecord() */
					/*
					 * Hook up the thread's waitq set either to
					 * the fileproc structure, or to the global
					 * conflict queue: but only on the first
					 * select pass.
					 */
					seldata->wqp[nc] = sellinkfp(fp, (void **)rl_ptr, wqset);
				}
				nc++;
			}
		}
	}
	proc_fdunlock(p);

	*retval = n;
	return (0);
}