#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
struct TYPE_7__ {scalar_t__ p_stat; int p_listflag; int /*<<< orphan*/  p_childrencnt; struct TYPE_7__* p_pptr; } ;

/* Variables and functions */
 TYPE_1__* PROC_NULL ; 
 int P_LIST_CHILDDRAINED ; 
 int P_LIST_CHILDLKWAIT ; 
 int P_LIST_EXITED ; 
 scalar_t__ SZOMB ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_mlock ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 TYPE_1__* proc_ref_locked (TYPE_1__*) ; 

proc_t 
proc_parent(proc_t p)
{
	proc_t parent;
	proc_t pp;

	proc_list_lock();
loop:
	pp = p->p_pptr;
	parent =  proc_ref_locked(pp);
	if ((parent == PROC_NULL) && (pp != PROC_NULL) && (pp->p_stat != SZOMB) && ((pp->p_listflag & P_LIST_EXITED) != 0) && ((pp->p_listflag & P_LIST_CHILDDRAINED)== 0)){
		pp->p_listflag |= P_LIST_CHILDLKWAIT;
		msleep(&pp->p_childrencnt, proc_list_mlock, 0, "proc_parent", 0);
		goto loop;
	}
	proc_list_unlock();
	return(parent);
}