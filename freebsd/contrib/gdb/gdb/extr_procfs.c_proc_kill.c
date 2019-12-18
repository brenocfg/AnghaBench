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
struct TYPE_4__ {scalar_t__ ctl_fd; } ;
typedef  TYPE_1__ procinfo ;
typedef  int procfs_ctl_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CTL ; 
 int PCKILL ; 
 int /*<<< orphan*/  PIOCKILL ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ open_procinfo_files (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int write (scalar_t__,char*,int) ; 

int
proc_kill (procinfo *pi, int signo)
{
  int win;

  /*
   * We might conceivably apply this operation to an LWP, and
   * the LWP's ctl file descriptor might not be open.
   */

  if (pi->ctl_fd == 0 &&
      open_procinfo_files (pi, FD_CTL) == 0)
    {
      return 0;
    }
  else
    {
#ifdef NEW_PROC_API
      procfs_ctl_t cmd[2];

      cmd[0] = PCKILL;
      cmd[1] = signo;
      win = (write (pi->ctl_fd, (char *) &cmd, sizeof (cmd)) == sizeof (cmd));
#else   /* ioctl method */
      /* FIXME: do I need the Alpha OSF fixups present in
	 procfs.c/unconditionally_kill_inferior?  Perhaps only for SIGKILL? */
      win = (ioctl (pi->ctl_fd, PIOCKILL, &signo) >= 0);
#endif
  }

  return win;
}