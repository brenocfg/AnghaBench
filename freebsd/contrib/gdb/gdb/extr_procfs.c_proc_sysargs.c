#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pr_sysarg; } ;
struct TYPE_7__ {int /*<<< orphan*/  pr_sysarg; TYPE_1__ pr_lwp; } ;
struct TYPE_8__ {TYPE_2__ prstatus; int /*<<< orphan*/  status_valid; } ;
typedef  TYPE_3__ procinfo ;

/* Variables and functions */
 int /*<<< orphan*/  proc_get_status (TYPE_3__*) ; 

long *
proc_sysargs (procinfo *pi)
{
  if (!pi->status_valid)
    if (!proc_get_status (pi))
      return NULL;

#ifdef NEW_PROC_API
  return (long *) &pi->prstatus.pr_lwp.pr_sysarg;
#else
  return (long *) &pi->prstatus.pr_sysarg;
#endif
}