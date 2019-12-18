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
struct TYPE_6__ {long pr_flags; } ;
struct TYPE_7__ {long pr_flags; TYPE_1__ pr_lwp; } ;
struct TYPE_8__ {TYPE_2__ prstatus; int /*<<< orphan*/  status_valid; } ;
typedef  TYPE_3__ procinfo ;

/* Variables and functions */
 int /*<<< orphan*/  proc_get_status (TYPE_3__*) ; 

long
proc_flags (procinfo *pi)
{
  if (!pi->status_valid)
    if (!proc_get_status (pi))
      return 0;	/* FIXME: not a good failure value (but what is?) */

#ifdef NEW_PROC_API
# ifdef UNIXWARE
  /* UnixWare 7.1 puts process status flags, e.g. PR_ASYNC, in
     pstatus_t and LWP status flags, e.g. PR_STOPPED, in lwpstatus_t.
     The two sets of flags don't overlap. */
  return pi->prstatus.pr_flags | pi->prstatus.pr_lwp.pr_flags;
# else
  return pi->prstatus.pr_lwp.pr_flags;
# endif
#else
  return pi->prstatus.pr_flags;
#endif
}