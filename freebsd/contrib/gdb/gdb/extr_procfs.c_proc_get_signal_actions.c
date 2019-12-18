#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pr_action; } ;
struct TYPE_8__ {int /*<<< orphan*/  pr_action; TYPE_1__ pr_lwp; } ;
struct TYPE_9__ {scalar_t__ tid; TYPE_2__ prstatus; int /*<<< orphan*/  status_valid; int /*<<< orphan*/  pid; } ;
typedef  TYPE_3__ procinfo ;
typedef  int /*<<< orphan*/  gdb_sigaction_t ;

/* Variables and functions */
 TYPE_3__* find_procinfo_or_die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  proc_get_status (TYPE_3__*) ; 

gdb_sigaction_t *
proc_get_signal_actions (procinfo *pi, gdb_sigaction_t *save)
{
  gdb_sigaction_t *ret = NULL;

  /*
   * We should never have to apply this operation to any procinfo
   * except the one for the main process.  If that ever changes
   * for any reason, then take out the following clause and
   * replace it with one that makes sure the ctl_fd is open.
   */

  if (pi->tid != 0)
    pi = find_procinfo_or_die (pi->pid, 0);

  if (!pi->status_valid)
    if (!proc_get_status (pi))
      return NULL;

#ifdef NEW_PROC_API
  ret = &pi->prstatus.pr_lwp.pr_action;
#else
  ret = &pi->prstatus.pr_action;
#endif
  if (save && ret)
    memcpy (save, ret, sizeof (gdb_sigaction_t));

  return ret;
}