#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_6__ {scalar_t__ tid; char* pr_fpregs; } ;
typedef  TYPE_1__ tfpregset_t ;
struct TYPE_7__ {scalar_t__ ctl_fd; scalar_t__ tid; scalar_t__ fpregs_valid; } ;
typedef  TYPE_2__ procinfo ;
typedef  int /*<<< orphan*/  procfs_ctl_t ;
typedef  int /*<<< orphan*/  gdb_fpregset_t ;
typedef  int /*<<< orphan*/  arg ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CTL ; 
 int /*<<< orphan*/  PCSFPREG ; 
 int /*<<< orphan*/  PIOCSFPREG ; 
 int /*<<< orphan*/  PIOCTSFPREG ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memcpy (char**,char*,int) ; 
 scalar_t__ open_procinfo_files (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * proc_get_fpregs (TYPE_2__*) ; 
 int write (scalar_t__,void*,int) ; 

int
proc_set_fpregs (procinfo *pi)
{
  gdb_fpregset_t *fpregs;
  int win;

  if ((fpregs = proc_get_fpregs (pi)) == NULL)
    return 0;		/* get_fpregs has already warned */

  if (pi->ctl_fd == 0 &&
      open_procinfo_files (pi, FD_CTL) == 0)
    {
      return 0;
    }
  else
    {
#ifdef NEW_PROC_API
      struct {
	procfs_ctl_t cmd;
	/* Use char array to avoid alignment issues.  */
	char fpregs[sizeof (gdb_fpregset_t)];
      } arg;

      arg.cmd   = PCSFPREG;
      memcpy (&arg.fpregs, fpregs, sizeof (arg.fpregs));
      win = (write (pi->ctl_fd, (void *) &arg, sizeof (arg)) == sizeof (arg));
#else
#ifdef PIOCTSFPREG
      if (pi->tid == 0)
	win = (ioctl (pi->ctl_fd, PIOCSFPREG, fpregs) >= 0);
      else
	{
	  struct {
	    long pr_count;
	    tid_t pr_error_thread;
	    tfpregset_t thread_1;
	  } thread_fpregs;

	  thread_fpregs.pr_count = 1;
	  thread_fpregs.thread_1.tid = pi->tid;
	  memcpy (&thread_fpregs.thread_1.pr_fpregs, fpregs,
		  sizeof (*fpregs));
	  win = (ioctl (pi->ctl_fd, PIOCTSFPREG, &thread_fpregs) >= 0);
	}
#else
      win = (ioctl (pi->ctl_fd, PIOCSFPREG, fpregs) >= 0);
#endif	/* osf PIOCTSFPREG */
#endif	/* NEW_PROC_API */
    }

  /* Policy: writing the regs invalidates our cache. */
  pi->fpregs_valid = 0;
  return win;
}