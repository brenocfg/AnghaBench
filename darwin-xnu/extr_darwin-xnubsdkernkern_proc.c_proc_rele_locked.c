#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
struct TYPE_4__ {scalar_t__ p_refcount; int p_listflag; } ;

/* Variables and functions */
 int P_LIST_DRAINWAIT ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  record_procref (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

void
proc_rele_locked(proc_t p)
{

	if (p->p_refcount > 0) {
		p->p_refcount--;
		record_procref(p, -1);
		if ((p->p_refcount == 0) && ((p->p_listflag & P_LIST_DRAINWAIT) == P_LIST_DRAINWAIT)) {
			p->p_listflag &= ~P_LIST_DRAINWAIT;
			wakeup(&p->p_refcount);
		}
	} else
		panic("proc_rele_locked  -ve ref\n");

}