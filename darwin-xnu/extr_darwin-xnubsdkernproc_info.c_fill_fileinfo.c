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
struct proc_fileinfo {int /*<<< orphan*/  fi_guardflags; int /*<<< orphan*/  fi_status; int /*<<< orphan*/  fi_type; int /*<<< orphan*/  fi_offset; int /*<<< orphan*/  fi_openflags; } ;
struct fileproc {TYPE_1__* f_fglob; } ;
typedef  scalar_t__ proc_t ;
struct TYPE_2__ {int fg_count; int /*<<< orphan*/  fg_offset; int /*<<< orphan*/  fg_flag; } ;

/* Variables and functions */
 int FDFLAGS_GET (scalar_t__,int) ; 
 int /*<<< orphan*/  FILEGLOB_DTYPE (TYPE_1__*) ; 
 scalar_t__ FILEPROC_TYPE (struct fileproc*) ; 
 scalar_t__ FTYPE_GUARDED ; 
 int /*<<< orphan*/  GUARD_CLOSE ; 
 int /*<<< orphan*/  GUARD_DUP ; 
 int /*<<< orphan*/  GUARD_FILEPORT ; 
 int /*<<< orphan*/  GUARD_SOCKET_IPC ; 
 int /*<<< orphan*/  PROC_FI_GUARD_CLOSE ; 
 int /*<<< orphan*/  PROC_FI_GUARD_DUP ; 
 int /*<<< orphan*/  PROC_FI_GUARD_FILEPORT ; 
 int /*<<< orphan*/  PROC_FI_GUARD_SOCKET_IPC ; 
 int /*<<< orphan*/  PROC_FP_CLEXEC ; 
 int /*<<< orphan*/  PROC_FP_CLFORK ; 
 int /*<<< orphan*/  PROC_FP_GUARDED ; 
 int /*<<< orphan*/  PROC_FP_SHARED ; 
 scalar_t__ PROC_NULL ; 
 int UF_EXCLOSE ; 
 int UF_FORKCLOSE ; 
 scalar_t__ fp_isguarded (struct fileproc*,int /*<<< orphan*/ ) ; 

void
fill_fileinfo(struct fileproc * fp, proc_t proc, int fd, struct proc_fileinfo * fproc)
{
	fproc->fi_openflags = fp->f_fglob->fg_flag;
	fproc->fi_status = 0;
	fproc->fi_offset = fp->f_fglob->fg_offset;
	fproc->fi_type = FILEGLOB_DTYPE(fp->f_fglob);
	if (fp->f_fglob->fg_count > 1)
		fproc->fi_status |= PROC_FP_SHARED;
	if (proc != PROC_NULL) {
		if ((FDFLAGS_GET(proc, fd) & UF_EXCLOSE) != 0)
			fproc->fi_status |= PROC_FP_CLEXEC;
		if ((FDFLAGS_GET(proc, fd) & UF_FORKCLOSE) != 0)
			fproc->fi_status |= PROC_FP_CLFORK;
	}
	if (FILEPROC_TYPE(fp) == FTYPE_GUARDED) {
		fproc->fi_status |= PROC_FP_GUARDED;
		fproc->fi_guardflags = 0;
		if (fp_isguarded(fp, GUARD_CLOSE))
			fproc->fi_guardflags |= PROC_FI_GUARD_CLOSE;
		if (fp_isguarded(fp, GUARD_DUP))
			fproc->fi_guardflags |= PROC_FI_GUARD_DUP;
		if (fp_isguarded(fp, GUARD_SOCKET_IPC))
			fproc->fi_guardflags |= PROC_FI_GUARD_SOCKET_IPC;
		if (fp_isguarded(fp, GUARD_FILEPORT))
			fproc->fi_guardflags |= PROC_FI_GUARD_FILEPORT;
	}
}