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
struct session {scalar_t__ s_count; int s_listflags; int /*<<< orphan*/  s_mlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_ZONE (struct session*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SESSION ; 
 int S_LIST_DEAD ; 
 int S_LIST_TERM ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  proc_lck_grp ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 int /*<<< orphan*/  proc_mlock_grp ; 
 int /*<<< orphan*/  s_hash ; 

void
session_rele(struct session *sess)
{
	proc_list_lock();
	if (--sess->s_count == 0) {
		if ((sess->s_listflags & (S_LIST_TERM | S_LIST_DEAD)) != 0)
			panic("session_rele: terminating already terminated session");
		sess->s_listflags |= S_LIST_TERM;
		LIST_REMOVE(sess, s_hash);
		sess->s_listflags |= S_LIST_DEAD;
		if (sess->s_count != 0)
			panic("session_rele: freeing session in use");	
		proc_list_unlock();
#if CONFIG_FINE_LOCK_GROUPS
		lck_mtx_destroy(&sess->s_mlock, proc_mlock_grp);
#else
		lck_mtx_destroy(&sess->s_mlock, proc_lck_grp);
#endif
		FREE_ZONE(sess, sizeof(struct session), M_SESSION);
	} else
		proc_list_unlock();
}