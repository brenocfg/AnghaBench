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
struct pgrp {scalar_t__ pg_jobc; } ;
struct fixjob_iterargs {int entering; struct session* mysession; struct pgrp* pg; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 struct pgrp* PGRP_NULL ; 
 int PROC_RETURNED ; 
 struct session* SESSION_NULL ; 
 int /*<<< orphan*/  orphanpg (struct pgrp*) ; 
 int /*<<< orphan*/  pg_rele (struct pgrp*) ; 
 int /*<<< orphan*/  pgrp_lock (struct pgrp*) ; 
 int /*<<< orphan*/  pgrp_unlock (struct pgrp*) ; 
 struct pgrp* proc_pgrp (int /*<<< orphan*/ ) ; 
 struct session* proc_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_rele (struct session*) ; 

int
fixjob_callback(proc_t p, void * arg)
{
	struct fixjob_iterargs *fp;
	struct pgrp * pg, *hispg;
	struct session * mysession, *hissess;
	int entering;

	fp = (struct fixjob_iterargs *)arg;
	pg = fp->pg;
	mysession = fp->mysession;
	entering = fp->entering;

	hispg = proc_pgrp(p);
	hissess = proc_session(p);

	if ((hispg  != pg) &&
	    (hissess == mysession)) {
		pgrp_lock(hispg);
		if (entering) {
			hispg->pg_jobc++;
			pgrp_unlock(hispg);
		} else if (--hispg->pg_jobc == 0) {
			pgrp_unlock(hispg);
			orphanpg(hispg);
		} else
			pgrp_unlock(hispg);
	}
	if (hissess != SESSION_NULL)
		session_rele(hissess);
	if (hispg != PGRP_NULL)
		pg_rele(hispg);

	return(PROC_RETURNED);
}