#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct fileproc {scalar_t__ f_type; int /*<<< orphan*/  f_data; } ;
struct filedesc {int dummy; } ;
struct dup_args {int fd; } ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_10__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC_START ; 
 scalar_t__ DTYPE_SOCKET ; 
 scalar_t__ ENTR_SHOULDTRACE ; 
 scalar_t__ FP_ISGUARDED (struct fileproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUARD_DUP ; 
 int /*<<< orphan*/  KERNEL_ENERGYTRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (int /*<<< orphan*/ ) ; 
 int fdalloc (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int finishdup (TYPE_1__*,struct filedesc*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fp_drop (TYPE_1__*,int,struct fileproc*,int) ; 
 int fp_guard_exception (TYPE_1__*,int,struct fileproc*,int /*<<< orphan*/ ) ; 
 int fp_lookup (TYPE_1__*,int,struct fileproc**,int) ; 
 int /*<<< orphan*/  kEnTrActKernSocket ; 
 int /*<<< orphan*/  kGUARD_EXC_DUP ; 
 int /*<<< orphan*/  proc_fdlock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_fdunlock (TYPE_1__*) ; 

int
dup(proc_t p, struct dup_args *uap, int32_t *retval)
{
	struct filedesc *fdp = p->p_fd;
	int old = uap->fd;
	int new, error;
	struct fileproc *fp;

	proc_fdlock(p);
	if ( (error = fp_lookup(p, old, &fp, 1)) ) {
		proc_fdunlock(p);
		return(error);
	}
	if (FP_ISGUARDED(fp, GUARD_DUP)) {
		error = fp_guard_exception(p, old, fp, kGUARD_EXC_DUP);
		(void) fp_drop(p, old, fp, 1);
		proc_fdunlock(p);
		return (error);
	}
	if ( (error = fdalloc(p, 0, &new)) ) {
		fp_drop(p, old, fp, 1);
		proc_fdunlock(p);
		return (error);
	}
	error = finishdup(p, fdp, old, new, 0, retval);
	fp_drop(p, old, fp, 1);
	proc_fdunlock(p);

	if (ENTR_SHOULDTRACE && fp->f_type == DTYPE_SOCKET) {
		KERNEL_ENERGYTRACE(kEnTrActKernSocket, DBG_FUNC_START,
		    new, 0, (int64_t)VM_KERNEL_ADDRPERM(fp->f_data));
	}

	return (error);
}