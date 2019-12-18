#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  uc_sigmask; } ;
struct TYPE_9__ {int /*<<< orphan*/  pr_lwphold; TYPE_1__ pr_context; } ;
struct TYPE_10__ {TYPE_2__ pr_lwp; } ;
struct TYPE_11__ {scalar_t__ tid; int /*<<< orphan*/  ctl_fd; TYPE_3__ prstatus; int /*<<< orphan*/  status_valid; int /*<<< orphan*/  pid; } ;
typedef  TYPE_4__ procinfo ;
typedef  int /*<<< orphan*/  gdb_sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIOCGHOLD ; 
 TYPE_4__* find_procinfo_or_die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  proc_get_status (TYPE_4__*) ; 

gdb_sigset_t *
proc_get_held_signals (procinfo *pi, gdb_sigset_t *save)
{
  gdb_sigset_t *ret = NULL;

  /*
   * We should never have to apply this operation to any procinfo
   * except the one for the main process.  If that ever changes
   * for any reason, then take out the following clause and
   * replace it with one that makes sure the ctl_fd is open.
   */

  if (pi->tid != 0)
    pi = find_procinfo_or_die (pi->pid, 0);

#ifdef NEW_PROC_API
  if (!pi->status_valid)
    if (!proc_get_status (pi))
      return NULL;

#ifdef UNIXWARE
  ret = &pi->prstatus.pr_lwp.pr_context.uc_sigmask;
#else
  ret = &pi->prstatus.pr_lwp.pr_lwphold;
#endif /* UNIXWARE */
#else  /* not NEW_PROC_API */
  {
    static gdb_sigset_t sigheld;

    if (ioctl (pi->ctl_fd, PIOCGHOLD, &sigheld) >= 0)
      ret = &sigheld;
  }
#endif /* NEW_PROC_API */
  if (save && ret)
    memcpy (save, ret, sizeof (gdb_sigset_t));

  return ret;
}