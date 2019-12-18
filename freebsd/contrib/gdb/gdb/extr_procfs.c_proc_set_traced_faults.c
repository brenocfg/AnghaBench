#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tid; scalar_t__ status_valid; int /*<<< orphan*/  ctl_fd; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ procinfo ;
typedef  int /*<<< orphan*/  procfs_ctl_t ;
typedef  int /*<<< orphan*/  fltset_t ;
typedef  int /*<<< orphan*/  arg ;

/* Variables and functions */
 int /*<<< orphan*/  PCSFAULT ; 
 int /*<<< orphan*/  PIOCSFAULT ; 
 TYPE_1__* find_procinfo_or_die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char**,char*,int) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

int
proc_set_traced_faults (procinfo *pi, fltset_t *fltset)
{
  int win;

  /*
   * We should never have to apply this operation to any procinfo
   * except the one for the main process.  If that ever changes
   * for any reason, then take out the following clause and
   * replace it with one that makes sure the ctl_fd is open.
   */

  if (pi->tid != 0)
    pi = find_procinfo_or_die (pi->pid, 0);

#ifdef NEW_PROC_API
  {
    struct {
      procfs_ctl_t cmd;
      /* Use char array to avoid alignment issues.  */
      char fltset[sizeof (fltset_t)];
    } arg;

    arg.cmd = PCSFAULT;
    memcpy (&arg.fltset, fltset, sizeof (fltset_t));

    win = (write (pi->ctl_fd, (char *) &arg, sizeof (arg)) == sizeof (arg));
  }
#else	/* ioctl method */
  win = (ioctl (pi->ctl_fd, PIOCSFAULT, fltset) >= 0);
#endif
  /* The above operation renders the procinfo's cached pstatus obsolete. */
  pi->status_valid = 0;

  return win;
}