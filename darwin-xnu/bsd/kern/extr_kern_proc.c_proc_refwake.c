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
struct TYPE_3__ {int /*<<< orphan*/  p_listflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_LIST_REFWAIT ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
proc_refwake(proc_t p)
{
	proc_list_lock();
	p->p_listflag &= ~P_LIST_REFWAIT;
	wakeup(&p->p_listflag);
	proc_list_unlock();
}