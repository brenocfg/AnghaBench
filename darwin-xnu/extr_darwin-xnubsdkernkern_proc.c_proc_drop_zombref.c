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
struct TYPE_3__ {int p_listflag; int /*<<< orphan*/  p_stat; } ;

/* Variables and functions */
 int P_LIST_WAITING ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
proc_drop_zombref(proc_t p)
{
	proc_list_lock();
	if ((p->p_listflag & P_LIST_WAITING) ==  P_LIST_WAITING) {
		p->p_listflag &= ~P_LIST_WAITING;
		wakeup(&p->p_stat);
	}
	proc_list_unlock();
}