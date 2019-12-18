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
struct TYPE_6__ {int /*<<< orphan*/  pr_flttrace; } ;
struct TYPE_7__ {scalar_t__ tid; int /*<<< orphan*/  ctl_fd; TYPE_1__ prstatus; int /*<<< orphan*/  status_valid; int /*<<< orphan*/  pid; } ;
typedef  TYPE_2__ procinfo ;
typedef  int /*<<< orphan*/  fltset_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIOCGFAULT ; 
 TYPE_2__* find_procinfo_or_die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  proc_get_status (TYPE_2__*) ; 

fltset_t *
proc_get_traced_faults (procinfo *pi, fltset_t *save)
{
  fltset_t *ret = NULL;

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

  ret = &pi->prstatus.pr_flttrace;
#else
  {
    static fltset_t flttrace;

    if (ioctl (pi->ctl_fd, PIOCGFAULT, &flttrace) >= 0)
      ret = &flttrace;
  }
#endif
  if (save && ret)
    memcpy (save, ret, sizeof (fltset_t));

  return ret;
}