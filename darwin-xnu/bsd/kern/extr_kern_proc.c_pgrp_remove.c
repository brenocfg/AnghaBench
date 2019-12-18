#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct proc {int p_listflag; int /*<<< orphan*/ * p_pgrp; int /*<<< orphan*/  p_pgrpid; } ;
struct TYPE_2__ {scalar_t__ lh_first; } ;
struct pgrp {scalar_t__ pg_membercnt; TYPE_1__ pg_members; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRPID_DEAD ; 
 struct pgrp* PGRP_NULL ; 
 int P_LIST_INPGRP ; 
 int /*<<< orphan*/  p_pglist ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  pg_rele (struct pgrp*) ; 
 int /*<<< orphan*/  pgdelete_dropref (struct pgrp*) ; 
 int /*<<< orphan*/  pgrp_lock (struct pgrp*) ; 
 int /*<<< orphan*/  pgrp_unlock (struct pgrp*) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 struct pgrp* proc_pgrp (struct proc*) ; 

__attribute__((used)) static void
pgrp_remove(struct proc * p)
{
	struct pgrp * pg;

	pg = proc_pgrp(p);

	proc_list_lock();
#if __PROC_INTERNAL_DEBUG
	if ((p->p_listflag & P_LIST_INPGRP) == 0)
		panic("removing from pglist but no named ref\n");
#endif
	p->p_pgrpid = PGRPID_DEAD;
	p->p_listflag &= ~P_LIST_INPGRP;
	p->p_pgrp = NULL;
	proc_list_unlock();

	if (pg == PGRP_NULL)
		panic("pgrp_remove: pg is NULL");
	pgrp_lock(pg);
	pg->pg_membercnt--;

	if (pg->pg_membercnt < 0)
		panic("pgprp: -ve membercnt pgprp:%p p:%p\n",pg, p);

	LIST_REMOVE(p, p_pglist);
	if (pg->pg_members.lh_first == 0) {
		pgrp_unlock(pg);
		pgdelete_dropref(pg);
	} else {
		pgrp_unlock(pg);
		pg_rele(pg);
	}
}