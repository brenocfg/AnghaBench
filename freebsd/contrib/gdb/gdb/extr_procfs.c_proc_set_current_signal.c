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
struct TYPE_6__ {scalar_t__ tid; int /*<<< orphan*/  ctl_fd; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ procinfo ;
typedef  int /*<<< orphan*/  procfs_ctl_t ;
struct TYPE_7__ {int si_signo; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; scalar_t__ si_code; } ;
typedef  TYPE_2__ gdb_siginfo_t ;
typedef  int /*<<< orphan*/  arg ;

/* Variables and functions */
 int /*<<< orphan*/  PCSSIG ; 
 int /*<<< orphan*/  PIOCSSIG ; 
 TYPE_1__* find_procinfo_or_die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  getuid () ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int proc_cursig (TYPE_1__*) ; 
 int write (int /*<<< orphan*/ ,void*,int) ; 

int
proc_set_current_signal (procinfo *pi, int signo)
{
  int win;
  struct {
    procfs_ctl_t cmd;
    /* Use char array to avoid alignment issues.  */
    char sinfo[sizeof (gdb_siginfo_t)];
  } arg;
  gdb_siginfo_t *mysinfo;

  /*
   * We should never have to apply this operation to any procinfo
   * except the one for the main process.  If that ever changes
   * for any reason, then take out the following clause and
   * replace it with one that makes sure the ctl_fd is open.
   */

  if (pi->tid != 0)
    pi = find_procinfo_or_die (pi->pid, 0);

#ifdef PROCFS_DONT_PIOCSSIG_CURSIG
  /* With Alpha OSF/1 procfs, the kernel gets really confused if it
   * receives a PIOCSSIG with a signal identical to the current signal,
   * it messes up the current signal. Work around the kernel bug.
   */
  if (signo > 0 &&
      signo == proc_cursig (pi))
    return 1;           /* I assume this is a success? */
#endif

  /* The pointer is just a type alias.  */
  mysinfo = (gdb_siginfo_t *) &arg.sinfo;
  mysinfo->si_signo = signo;
  mysinfo->si_code  = 0;
  mysinfo->si_pid   = getpid ();       /* ?why? */
  mysinfo->si_uid   = getuid ();       /* ?why? */

#ifdef NEW_PROC_API
  arg.cmd = PCSSIG;
  win = (write (pi->ctl_fd, (void *) &arg, sizeof (arg))  == sizeof (arg));
#else
  win = (ioctl (pi->ctl_fd, PIOCSSIG, (void *) &arg.sinfo) >= 0);
#endif

  return win;
}