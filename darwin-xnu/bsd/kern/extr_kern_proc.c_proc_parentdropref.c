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
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {scalar_t__ p_parentref; int p_listflag; } ;

/* Variables and functions */
 int P_LIST_PARENTREFWAIT ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

int 
proc_parentdropref(proc_t p, int listlocked)
{
	if (listlocked == 0)
		proc_list_lock();

	if (p->p_parentref > 0) {
		p->p_parentref--;
		if ((p->p_parentref == 0) && ((p->p_listflag & P_LIST_PARENTREFWAIT) == P_LIST_PARENTREFWAIT)) {
			p->p_listflag &= ~P_LIST_PARENTREFWAIT;
			wakeup(&p->p_parentref);
		}
	} else
		panic("proc_parentdropref  -ve ref\n");
	if (listlocked == 0)
		proc_list_unlock();

	return(0);
}