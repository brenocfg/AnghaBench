#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  gregs; } ;
struct TYPE_9__ {TYPE_1__ uc_mcontext; } ;
struct TYPE_10__ {int /*<<< orphan*/  pr_reg; TYPE_2__ pr_context; } ;
struct TYPE_11__ {int /*<<< orphan*/  pr_reg; TYPE_3__ pr_lwp; } ;
struct TYPE_12__ {TYPE_4__ prstatus; int /*<<< orphan*/  gregs_valid; int /*<<< orphan*/  status_valid; } ;
typedef  TYPE_5__ procinfo ;
typedef  int /*<<< orphan*/  gdb_gregset_t ;

/* Variables and functions */
 int /*<<< orphan*/  proc_get_status (TYPE_5__*) ; 

gdb_gregset_t *
proc_get_gregs (procinfo *pi)
{
  if (!pi->status_valid || !pi->gregs_valid)
    if (!proc_get_status (pi))
      return NULL;

  /*
   * OK, sorry about the ifdef's.
   * There's three cases instead of two, because
   * in this instance Unixware and Solaris/RW differ.
   */

#ifdef NEW_PROC_API
#ifdef UNIXWARE		/* ugh, a true architecture dependency */
  return &pi->prstatus.pr_lwp.pr_context.uc_mcontext.gregs;
#else	/* not Unixware */
  return &pi->prstatus.pr_lwp.pr_reg;
#endif	/* Unixware */
#else	/* not NEW_PROC_API */
  return &pi->prstatus.pr_reg;
#endif	/* NEW_PROC_API */
}