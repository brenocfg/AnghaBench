#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ tid; int status_valid; int /*<<< orphan*/  prstatus; int /*<<< orphan*/  ctl_fd; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ procinfo ;
typedef  int /*<<< orphan*/  procfs_ctl_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  PCWSTOP ; 
 int /*<<< orphan*/  PIOCWSTOP ; 
 int /*<<< orphan*/  PROC_PRETTYFPRINT_STATUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* find_procinfo_or_die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_flags (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_get_current_thread (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_what (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_why (TYPE_1__*) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

int
proc_wait_for_stop (procinfo *pi)
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
    procfs_ctl_t cmd = PCWSTOP;
    win = (write (pi->ctl_fd, (char *) &cmd, sizeof (cmd)) == sizeof (cmd));
    /* We been runnin' and we stopped -- need to update status.  */
    pi->status_valid = 0;
  }
#else	/* ioctl method */
  win = (ioctl (pi->ctl_fd, PIOCWSTOP, &pi->prstatus) >= 0);
  /* Above call also refreshes the prstatus.  */
  if (win)
    {
      pi->status_valid = 1;
      PROC_PRETTYFPRINT_STATUS (proc_flags (pi),
				proc_why (pi),
				proc_what (pi),
				proc_get_current_thread (pi));
    }
#endif

  return win;
}