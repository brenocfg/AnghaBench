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
struct session {int dummy; } ;
struct pgrp {scalar_t__ pg_jobc; struct session* pg_session; } ;
struct fixjob_iterargs {int entering; struct session* mysession; struct pgrp* pg; } ;
typedef  scalar_t__ proc_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 struct pgrp* PGRP_NULL ; 
 scalar_t__ PROC_NULL ; 
 struct session* SESSION_NULL ; 
 scalar_t__ current_proc () ; 
 int /*<<< orphan*/  fixjob_callback ; 
 int /*<<< orphan*/  orphanpg (struct pgrp*) ; 
 int /*<<< orphan*/  pg_rele (struct pgrp*) ; 
 int /*<<< orphan*/  pgrp_lock (struct pgrp*) ; 
 int /*<<< orphan*/  pgrp_unlock (struct pgrp*) ; 
 int /*<<< orphan*/  proc_childrenwalk (scalar_t__,int /*<<< orphan*/ ,struct fixjob_iterargs*) ; 
 scalar_t__ proc_parent (scalar_t__) ; 
 scalar_t__ proc_parent_is_currentproc (scalar_t__) ; 
 struct pgrp* proc_pgrp (scalar_t__) ; 
 int /*<<< orphan*/  proc_rele (scalar_t__) ; 
 struct session* proc_session (scalar_t__) ; 
 int /*<<< orphan*/  session_rele (struct session*) ; 

void
fixjobc(proc_t p, struct pgrp *pgrp, int entering)
{
	struct pgrp *hispgrp = PGRP_NULL;
	struct session *hissess = SESSION_NULL;
	struct session *mysession = pgrp->pg_session;
	proc_t parent;
	struct fixjob_iterargs fjarg;
	boolean_t proc_parent_self;

	/*
	 * Check if p's parent is current proc, if yes then no need to take 
	 * a ref; calling proc_parent with current proc as parent may 
	 * deadlock if current proc is exiting.
	 */
	proc_parent_self = proc_parent_is_currentproc(p);
	if (proc_parent_self)
		parent = current_proc();
	else 
		parent = proc_parent(p);

	if (parent != PROC_NULL) {
		hispgrp = proc_pgrp(parent);	
		hissess = proc_session(parent);
		if (!proc_parent_self)
			proc_rele(parent);
	}


	/*
	 * Check p's parent to see whether p qualifies its own process
	 * group; if so, adjust count for p's process group.
	 */
	if ((hispgrp != pgrp) &&
	    (hissess == mysession)) {
		pgrp_lock(pgrp);
		if (entering) {
			pgrp->pg_jobc++;
			pgrp_unlock(pgrp);
		 }else if (--pgrp->pg_jobc == 0) {
			pgrp_unlock(pgrp);
			orphanpg(pgrp);
		} else
			pgrp_unlock(pgrp);
	}

	if (hissess != SESSION_NULL)
		session_rele(hissess);
	if (hispgrp != PGRP_NULL)
		pg_rele(hispgrp);

	/*
	 * Check this process' children to see whether they qualify
	 * their process groups; if so, adjust counts for children's
	 * process groups.
	 */
	fjarg.pg = pgrp;
	fjarg.mysession = mysession;
	fjarg.entering = entering;
	proc_childrenwalk(p, fixjob_callback, &fjarg);
}