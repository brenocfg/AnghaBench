#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
struct TYPE_5__ {int p_listflag; int /*<<< orphan*/  p_stat; } ;

/* Variables and functions */
 TYPE_1__* PROC_NULL ; 
 int /*<<< orphan*/  PWAIT ; 
 int P_LIST_EXITED ; 
 int P_LIST_INCREATE ; 
 int P_LIST_WAITING ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* pfind_locked (int) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_mlock ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

proc_t
proc_find_zombref(int pid)
{
	proc_t p;

	proc_list_lock();

 again:
	p = pfind_locked(pid);

	/* should we bail? */
	if ((p == PROC_NULL)					/* not found */
	    || ((p->p_listflag & P_LIST_INCREATE) != 0)		/* not created yet */
	    || ((p->p_listflag & P_LIST_EXITED) == 0)) {	/* not started exit */

		proc_list_unlock();
		return (PROC_NULL);
	}

	/* If someone else is controlling the (unreaped) zombie - wait */
	if ((p->p_listflag & P_LIST_WAITING) != 0) {
		(void)msleep(&p->p_stat, proc_list_mlock, PWAIT, "waitcoll", 0);
		goto again;
	}
	p->p_listflag |=  P_LIST_WAITING;

	proc_list_unlock();

	return(p);
}