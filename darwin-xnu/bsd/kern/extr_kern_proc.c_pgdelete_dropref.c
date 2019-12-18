#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tty {struct session* t_session; struct session* t_pgrp; } ;
struct session {scalar_t__ pg_membercnt; scalar_t__ pg_refcount; int s_listflags; scalar_t__ s_count; int /*<<< orphan*/  pg_mlock; int /*<<< orphan*/  s_mlock; struct session* pg_session; int /*<<< orphan*/  s_ttypgrpid; int /*<<< orphan*/  pg_listflags; } ;
struct pgrp {scalar_t__ pg_membercnt; scalar_t__ pg_refcount; int s_listflags; scalar_t__ s_count; int /*<<< orphan*/  pg_mlock; int /*<<< orphan*/  s_mlock; struct pgrp* pg_session; int /*<<< orphan*/  s_ttypgrpid; int /*<<< orphan*/  pg_listflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_ZONE (struct session*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PGRP ; 
 int /*<<< orphan*/  M_SESSION ; 
 int /*<<< orphan*/  NO_PID ; 
 int /*<<< orphan*/  PGRP_FLAG_DEAD ; 
 int /*<<< orphan*/  PGRP_FLAG_TERMINATE ; 
 struct tty* SESSION_TP (struct session*) ; 
 int S_LIST_DEAD ; 
 int S_LIST_TERM ; 
 struct tty* TTY_NULL ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pg_hash ; 
 int /*<<< orphan*/  pgrp_lock (struct session*) ; 
 int /*<<< orphan*/  pgrp_unlock (struct session*) ; 
 int /*<<< orphan*/  proc_lck_grp ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 int /*<<< orphan*/  proc_mlock_grp ; 
 int /*<<< orphan*/  s_hash ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 

__attribute__((used)) static void
pgdelete_dropref(struct pgrp *pgrp)
{
	struct tty *ttyp;
	int emptypgrp  = 1;
	struct session *sessp;


	pgrp_lock(pgrp);
	if (pgrp->pg_membercnt != 0) {
		emptypgrp = 0;
	}
	pgrp_unlock(pgrp);

	proc_list_lock();
	pgrp->pg_refcount--;
	if ((emptypgrp == 0) || (pgrp->pg_membercnt != 0)) {
		proc_list_unlock();
		return;
	}

	pgrp->pg_listflags |= PGRP_FLAG_TERMINATE;
	
	if (pgrp->pg_refcount > 0) {
		proc_list_unlock();
		return;
	}

	pgrp->pg_listflags |= PGRP_FLAG_DEAD;
	LIST_REMOVE(pgrp, pg_hash);

	proc_list_unlock();
	
	ttyp = SESSION_TP(pgrp->pg_session);
	if (ttyp != TTY_NULL) {
		if (ttyp->t_pgrp == pgrp) {
			tty_lock(ttyp);
			/* Re-check after acquiring the lock */
			if (ttyp->t_pgrp == pgrp) {
				ttyp->t_pgrp = NULL;
				pgrp->pg_session->s_ttypgrpid = NO_PID;
			}
			tty_unlock(ttyp);
		}
	}

	proc_list_lock();

	sessp = pgrp->pg_session;
	if ((sessp->s_listflags & (S_LIST_TERM | S_LIST_DEAD)) != 0)
			panic("pg_deleteref: manipulating refs of already terminating session");
	if (--sessp->s_count == 0) {
		if ((sessp->s_listflags & (S_LIST_TERM | S_LIST_DEAD)) != 0)
			panic("pg_deleteref: terminating already terminated session");
		sessp->s_listflags |= S_LIST_TERM;
		ttyp = SESSION_TP(sessp);
		LIST_REMOVE(sessp, s_hash);
		proc_list_unlock();
		if (ttyp != TTY_NULL) {
			tty_lock(ttyp);
			if (ttyp->t_session == sessp)
				ttyp->t_session = NULL;
			tty_unlock(ttyp);
		}
		proc_list_lock();
		sessp->s_listflags |= S_LIST_DEAD;
		if (sessp->s_count != 0)
			panic("pg_deleteref: freeing session in use");	
		proc_list_unlock();
#if CONFIG_FINE_LOCK_GROUPS
		lck_mtx_destroy(&sessp->s_mlock, proc_mlock_grp);
#else
		lck_mtx_destroy(&sessp->s_mlock, proc_lck_grp);
#endif
		FREE_ZONE(sessp, sizeof(struct session), M_SESSION);
	} else
		proc_list_unlock();
#if CONFIG_FINE_LOCK_GROUPS
	lck_mtx_destroy(&pgrp->pg_mlock, proc_mlock_grp);
#else
	lck_mtx_destroy(&pgrp->pg_mlock, proc_lck_grp);
#endif
	FREE_ZONE(pgrp, sizeof(*pgrp), M_PGRP);
}