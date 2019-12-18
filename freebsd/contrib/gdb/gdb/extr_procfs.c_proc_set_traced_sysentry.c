#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct gdb_proc_ctl_pcsentry   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sysset_t ;
struct TYPE_7__ {scalar_t__ tid; scalar_t__ status_valid; int /*<<< orphan*/  ctl_fd; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ procinfo ;
typedef  int /*<<< orphan*/  procfs_ctl_t ;
struct gdb_proc_ctl_pcsentry {int /*<<< orphan*/  cmd; char* sysset; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCSENTRY ; 
 int /*<<< orphan*/  PIOCSENTRY ; 
 TYPE_1__* find_procinfo_or_die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char**,char*,int) ; 
 int sysset_t_size (TYPE_1__*) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xfree (TYPE_2__*) ; 
 TYPE_2__* xmalloc (int) ; 

int
proc_set_traced_sysentry (procinfo *pi, sysset_t *sysset)
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
    struct gdb_proc_ctl_pcsentry {
      procfs_ctl_t cmd;
      /* Use char array to avoid alignment issues.  */
      char sysset[sizeof (sysset_t)];
    } *argp;
    int argp_size = sizeof (struct gdb_proc_ctl_pcsentry)
                  - sizeof (sysset_t)
		  + sysset_t_size (pi);

    argp = xmalloc (argp_size);

    argp->cmd = PCSENTRY;
    memcpy (&argp->sysset, sysset, sysset_t_size (pi));

    win = (write (pi->ctl_fd, (char *) argp, argp_size) == argp_size);
    xfree (argp);
  }
#else	/* ioctl method */
  win = (ioctl (pi->ctl_fd, PIOCSENTRY, sysset) >= 0);
#endif
  /* The above operation renders the procinfo's cached pstatus obsolete. */
  pi->status_valid = 0;

  return win;
}