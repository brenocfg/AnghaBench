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
struct TYPE_6__ {int pr_ppid; } ;
struct TYPE_7__ {scalar_t__ tid; TYPE_1__ prstatus; int /*<<< orphan*/  status_valid; int /*<<< orphan*/  pid; } ;
typedef  TYPE_2__ procinfo ;

/* Variables and functions */
 TYPE_2__* find_procinfo_or_die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_get_status (TYPE_2__*) ; 

int
proc_parent_pid (procinfo *pi)
{
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
      return 0;

  return pi->prstatus.pr_ppid;
}