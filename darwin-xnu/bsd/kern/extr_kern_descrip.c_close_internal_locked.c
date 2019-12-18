#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  scalar_t__ u_int ;
struct fileproc {int f_flags; scalar_t__ f_type; TYPE_10__* f_fglob; scalar_t__ f_data; } ;
struct filedesc {int* fd_ofileflags; int fd_knlistsize; } ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_16__ {struct filedesc* p_fd; } ;
struct TYPE_15__ {int /*<<< orphan*/  fg_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC_END ; 
 scalar_t__ DTYPE_SOCKET ; 
 scalar_t__ DTYPE_VNODE ; 
 scalar_t__ ENTR_SHOULDTRACE ; 
 int FD_DUP2RESV ; 
 int FP_AIOISSUED ; 
 int FP_CLOSING ; 
 int FP_WAITCLOSE ; 
 int FP_WAITEVENT ; 
 int FP_WRITTEN ; 
 int /*<<< orphan*/  KAUTH_FILEOP_CLOSE ; 
 scalar_t__ KAUTH_FILEOP_CLOSE_MODIFIED ; 
 int /*<<< orphan*/  KERNEL_ENERGYTRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int UF_RESERVED ; 
 scalar_t__ VM_KERNEL_ADDRPERM (scalar_t__) ; 
 int /*<<< orphan*/  _aio_close (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _fdrelse (TYPE_1__*,int) ; 
 int closef_locked (struct fileproc*,TYPE_10__*,TYPE_1__*) ; 
 int /*<<< orphan*/  fileproc_drain (TYPE_1__*,struct fileproc*) ; 
 int /*<<< orphan*/  fileproc_free (struct fileproc*) ; 
 int /*<<< orphan*/  kEnTrActKernSocket ; 
 int /*<<< orphan*/  kauth_authorize_fileop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,uintptr_t) ; 
 scalar_t__ kauth_authorize_fileop_has_listeners () ; 
 int /*<<< orphan*/  knote_fdclose (TYPE_1__*,int) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  proc_fdlock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_fdlock_assert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdunlock (TYPE_1__*) ; 
 int /*<<< orphan*/  procfdtbl_markclosefd (TYPE_1__*,int) ; 
 int /*<<< orphan*/  procfdtbl_reservefd (TYPE_1__*,int) ; 
 scalar_t__ vnode_getwithref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitevent_close (TYPE_1__*,struct fileproc*) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

int
close_internal_locked(proc_t p, int fd, struct fileproc *fp, int flags)
{
	struct filedesc *fdp = p->p_fd;
	int error =0;
	int resvfd = flags & FD_DUP2RESV;


#if DIAGNOSTIC
	proc_fdlock_assert(p, LCK_MTX_ASSERT_OWNED);
#endif

	/* Keep people from using the filedesc while we are closing it */
	procfdtbl_markclosefd(p, fd);


	if ((fp->f_flags & FP_CLOSING) == FP_CLOSING) {
		panic("close_internal_locked: being called on already closing fd");
	}


#if DIAGNOSTIC
	if ((fdp->fd_ofileflags[fd] & UF_RESERVED) == 0)
		panic("close_internal: unreserved fileflags with fd %d", fd);
#endif

	fp->f_flags |= FP_CLOSING;

	if ( (fp->f_flags & FP_AIOISSUED) || kauth_authorize_fileop_has_listeners() ) {

	        proc_fdunlock(p);

		if ( (fp->f_type == DTYPE_VNODE) && kauth_authorize_fileop_has_listeners() ) {
		        /*
			 * call out to allow 3rd party notification of close.
			 * Ignore result of kauth_authorize_fileop call.
			 */
		        if (vnode_getwithref((vnode_t)fp->f_data) == 0) {
		        	u_int	fileop_flags = 0;
		        	if ((fp->f_flags & FP_WRITTEN) != 0)
		        		fileop_flags |= KAUTH_FILEOP_CLOSE_MODIFIED;
			        kauth_authorize_fileop(fp->f_fglob->fg_cred, KAUTH_FILEOP_CLOSE,
						       (uintptr_t)fp->f_data, (uintptr_t)fileop_flags);
				vnode_put((vnode_t)fp->f_data);
			}
		}
		if (fp->f_flags & FP_AIOISSUED)
		        /*
			 * cancel all async IO requests that can be cancelled.
			 */
		        _aio_close( p, fd );

		proc_fdlock(p);
	}

	if (fd < fdp->fd_knlistsize)
		knote_fdclose(p, fd);

	if (fp->f_flags & FP_WAITEVENT)
		(void)waitevent_close(p, fp);

	fileproc_drain(p, fp);

	if (resvfd == 0) {
		_fdrelse(p, fd);
	} else {
		procfdtbl_reservefd(p, fd);
	}

	if (ENTR_SHOULDTRACE && fp->f_type == DTYPE_SOCKET)
		KERNEL_ENERGYTRACE(kEnTrActKernSocket, DBG_FUNC_END,
		    fd, 0, (int64_t)VM_KERNEL_ADDRPERM(fp->f_data));

	error = closef_locked(fp, fp->f_fglob, p);
	if ((fp->f_flags & FP_WAITCLOSE) == FP_WAITCLOSE)
		wakeup(&fp->f_flags);
	fp->f_flags &= ~(FP_WAITCLOSE | FP_CLOSING);

	proc_fdunlock(p);

	fileproc_free(fp);

	proc_fdlock(p);

#if DIAGNOSTIC
	if (resvfd != 0) {
		if ((fdp->fd_ofileflags[fd] & UF_RESERVED) == 0)
			panic("close with reserved fd returns with freed fd:%d: proc: %p", fd, p);
	}
#endif

	return(error);
}