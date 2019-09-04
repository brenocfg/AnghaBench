#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct session {int s_listflags; int /*<<< orphan*/  s_count; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_6__ {struct session* pg_session; } ;
struct TYPE_5__ {int p_listflag; TYPE_4__* p_pgrp; int /*<<< orphan*/  p_pgrpid; } ;

/* Variables and functions */
 TYPE_4__* PGRP_NULL ; 
 TYPE_1__* PROC_NULL ; 
 int P_LIST_PGRPTRANS ; 
 int P_LIST_PGRPTRWAIT ; 
 struct session* SESSION_NULL ; 
 int S_LIST_DEAD ; 
 int S_LIST_TERM ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_mlock ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

struct session *
proc_session(proc_t p)
{
	struct session * sess = SESSION_NULL;
	
	if (p == PROC_NULL)
		return(SESSION_NULL);

	proc_list_lock();

	/* wait during transitions */
	while ((p->p_listflag & P_LIST_PGRPTRANS) == P_LIST_PGRPTRANS) {
		p->p_listflag |= P_LIST_PGRPTRWAIT;
		(void)msleep(&p->p_pgrpid, proc_list_mlock, 0, "proc_pgrp", 0);
	}

	if ((p->p_pgrp != PGRP_NULL) && ((sess = p->p_pgrp->pg_session) != SESSION_NULL)) {
		if ((sess->s_listflags & (S_LIST_TERM | S_LIST_DEAD)) != 0)
			panic("proc_session:returning sesssion ref on terminating session");
		sess->s_count++;
	}
	proc_list_unlock();
	return(sess);
}