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
struct pgrp {int dummy; } ;
struct killpg1_iterargs {scalar_t__ nfound; int signum; int /*<<< orphan*/  uc; int /*<<< orphan*/  curproc; } ;
struct killpg1_filtargs {int posix; int /*<<< orphan*/  curproc; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int EPERM ; 
 int ESRCH ; 
 int /*<<< orphan*/  PGRP_DROPREF ; 
 int PROC_ALLPROCLIST ; 
 int PROC_ZOMBPROCLIST ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  killpg1_allfilt ; 
 int /*<<< orphan*/  killpg1_callback ; 
 int /*<<< orphan*/  killpg1_pgrpfilt ; 
 struct pgrp* pgfind (int) ; 
 int /*<<< orphan*/  pgrp_iterate (struct pgrp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct killpg1_iterargs*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_iterate (int,int /*<<< orphan*/ ,struct killpg1_iterargs*,int /*<<< orphan*/ ,struct killpg1_filtargs*) ; 
 struct pgrp* proc_pgrp (int /*<<< orphan*/ ) ; 

int
killpg1(proc_t curproc, int signum, int pgid, int all, int posix)
{
	kauth_cred_t uc;
	struct pgrp *pgrp;
	int error = 0;

	uc = kauth_cred_proc_ref(curproc);
	struct killpg1_iterargs karg = {
		.curproc = curproc, .uc = uc, .nfound = 0, .signum = signum
	};

	if (all) {
		/*
		 * Broadcast to all processes that the user can signal (pid was -1).
		 */
		struct killpg1_filtargs kfarg = {
			.posix = posix, .curproc = curproc
		};
		proc_iterate(PROC_ALLPROCLIST | PROC_ZOMBPROCLIST, killpg1_callback,
				&karg, killpg1_allfilt, &kfarg);
	} else {
		if (pgid == 0) {
			/*
			 * Send to current the current process' process group.
			 */
			pgrp = proc_pgrp(curproc);
		 } else {
			pgrp = pgfind(pgid);
			if (pgrp == NULL) {
				error = ESRCH;
				goto out;
			}
		}

		/* PGRP_DROPREF drops the pgrp refernce */
		pgrp_iterate(pgrp, PGRP_DROPREF, killpg1_callback, &karg,
				killpg1_pgrpfilt, NULL);
	}
	error = (karg.nfound > 0 ? 0 : (posix ? EPERM : ESRCH));
out:
	kauth_cred_unref(&uc);
	return (error);
}