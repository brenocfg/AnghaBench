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
struct TYPE_5__ {scalar_t__ p_stat; int p_listflag; int /*<<< orphan*/  p_parentref; int /*<<< orphan*/  p_childrencnt; struct TYPE_5__* p_pptr; } ;

/* Variables and functions */
 TYPE_1__* PROC_NULL ; 
 int P_LIST_CHILDDRAINED ; 
 int P_LIST_CHILDDRSTART ; 
 int P_LIST_CHILDDRWAIT ; 
 scalar_t__ SZOMB ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_mlock ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

proc_t 
proc_parentholdref(proc_t p)
{
	proc_t parent = PROC_NULL;
	proc_t pp;
	int loopcnt = 0;


	proc_list_lock();
loop:
	pp = p->p_pptr;
	if ((pp == PROC_NULL) || (pp->p_stat == SZOMB) || ((pp->p_listflag & (P_LIST_CHILDDRSTART | P_LIST_CHILDDRAINED)) == (P_LIST_CHILDDRSTART | P_LIST_CHILDDRAINED))) {
		parent = PROC_NULL;
		goto out;
	}
		
	if ((pp->p_listflag & (P_LIST_CHILDDRSTART | P_LIST_CHILDDRAINED)) == P_LIST_CHILDDRSTART) {
		pp->p_listflag |= P_LIST_CHILDDRWAIT;
		msleep(&pp->p_childrencnt, proc_list_mlock, 0, "proc_parent", 0);
		loopcnt++;
		if (loopcnt == 5) {
			parent = PROC_NULL;
			goto out;
		}
		goto loop;
	}

	if ((pp->p_listflag & (P_LIST_CHILDDRSTART | P_LIST_CHILDDRAINED)) == 0) {
		pp->p_parentref++;
		parent = pp;
		goto out;
	}
	
out:
	proc_list_unlock();
	return(parent);
}