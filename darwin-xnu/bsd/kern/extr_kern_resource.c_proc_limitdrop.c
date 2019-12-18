#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct plimit {scalar_t__ pl_refcnt; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {struct plimit* p_olimit; struct plimit* p_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_ZONE (struct plimit*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PLIMIT ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

void
proc_limitdrop(proc_t p, int exiting)
{
	struct  plimit * freelim = NULL;
	struct  plimit * freeoldlim = NULL;

	proc_list_lock();

	if (--p->p_limit->pl_refcnt == 0) { 
		freelim = p->p_limit;
		p->p_limit = NULL;
	}
	if ((exiting != 0) && (p->p_olimit != NULL) && (--p->p_olimit->pl_refcnt == 0)) {
		freeoldlim =  p->p_olimit;
		p->p_olimit = NULL;
	}

	proc_list_unlock();
	if (freelim != NULL)
		FREE_ZONE(freelim, sizeof *p->p_limit, M_PLIMIT);
	if (freeoldlim != NULL)
		FREE_ZONE(freeoldlim, sizeof *p->p_olimit, M_PLIMIT);
}