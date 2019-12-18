#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ptid_t ;
typedef  int /*<<< orphan*/  procinfo ;

/* Variables and functions */
 scalar_t__ FLTKWATCH ; 
 scalar_t__ FLTWATCH ; 
 int PIDGET (int /*<<< orphan*/ ) ; 
 scalar_t__ PR_FAULTED ; 
 int PR_ISTOP ; 
 int PR_STOPPED ; 
 int /*<<< orphan*/ * find_procinfo_or_die (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int proc_flags (int /*<<< orphan*/ *) ; 
 scalar_t__ proc_what (int /*<<< orphan*/ *) ; 
 scalar_t__ proc_why (int /*<<< orphan*/ *) ; 

int
procfs_stopped_by_watchpoint (ptid_t ptid)
{
  procinfo *pi;

  pi = find_procinfo_or_die (PIDGET (ptid) == -1 ?
			     PIDGET (inferior_ptid) : PIDGET (ptid), 0);

  if (!pi)	/* If no process, then not stopped by watchpoint!  */
    return 0;

  if (proc_flags (pi) & (PR_STOPPED | PR_ISTOP))
    {
      if (proc_why (pi) == PR_FAULTED)
	{
#ifdef FLTWATCH
	  if (proc_what (pi) == FLTWATCH)
	    return 1;
#endif
#ifdef FLTKWATCH
	  if (proc_what (pi) == FLTKWATCH)
	    return 1;
#endif
	}
    }
  return 0;
}