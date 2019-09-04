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
struct setpriority_args {int which; int who; int prio; } ;
struct puser_nice_args {int prio; int who; int* foundp; int* errorp; struct proc* curp; } ;
struct proc {int dummy; } ;
struct ppgrp_nice_args {int prio; int* foundp; int* errorp; struct proc* curp; } ;
struct pgrp {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,int,...) ; 
 int EIDRM ; 
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  PGRP_DROPREF ; 
 struct pgrp* PGRP_NULL ; 
#define  PRIO_DARWIN_GPU 134 
#define  PRIO_DARWIN_PROCESS 133 
#define  PRIO_DARWIN_ROLE 132 
#define  PRIO_DARWIN_THREAD 131 
#define  PRIO_PGRP 130 
#define  PRIO_PROCESS 129 
#define  PRIO_USER 128 
 int /*<<< orphan*/  PROC_ALLPROCLIST ; 
 struct proc* PROC_NULL ; 
 int /*<<< orphan*/  cmd ; 
 int /*<<< orphan*/  current_thread () ; 
 int do_background_proc (struct proc*,struct proc*,int) ; 
 int do_background_thread (int /*<<< orphan*/ ,int) ; 
 int donice (struct proc*,struct proc*,int) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  owner ; 
 struct pgrp* pgfind (int) ; 
 int /*<<< orphan*/  pgrp_iterate (struct pgrp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppgrp_donice_callback ; 
 struct proc* proc_find (int) ; 
 int /*<<< orphan*/  proc_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pgrp* proc_pgrp (struct proc*) ; 
 int /*<<< orphan*/  proc_rele (struct proc*) ; 
 int proc_set_darwin_role (struct proc*,struct proc*,int) ; 
 int /*<<< orphan*/  puser_donice_callback ; 
 int set_gpudeny_proc (struct proc*,struct proc*,int) ; 
 int /*<<< orphan*/  value32 ; 

int
setpriority(struct proc *curp, struct setpriority_args *uap, int32_t *retval)
{
	struct proc *p;
	int found = 0, error = 0;
	int refheld = 0;

	AUDIT_ARG(cmd, uap->which);
	AUDIT_ARG(owner, uap->who, 0);
	AUDIT_ARG(value32, uap->prio);

	/* would also test (uap->who < 0), but id_t is unsigned */
	if (uap->who > 0x7fffffff)
		return (EINVAL);

	switch (uap->which) {

	case PRIO_PROCESS:
		if (uap->who == 0)
			p = curp;
		else {
			p = proc_find(uap->who);
			if (p == 0)
				break;
			refheld = 1;
		}
		error = donice(curp, p, uap->prio);
		found++;
		if (refheld != 0)
			proc_rele(p);
		break;

	case PRIO_PGRP: {
		struct pgrp *pg = PGRP_NULL;
		struct ppgrp_nice_args ppgrp;
		 
		if (uap->who == 0) {
			pg = proc_pgrp(curp);
		 } else if ((pg = pgfind(uap->who)) == PGRP_NULL)
			break;

		ppgrp.curp = curp;
		ppgrp.prio = uap->prio;
		ppgrp.foundp = &found;
		ppgrp.errorp = &error;
		
		/* PGRP_DROPREF drops the reference on process group */
		pgrp_iterate(pg, PGRP_DROPREF, ppgrp_donice_callback, (void *)&ppgrp, NULL, NULL);

		break;
	}

	case PRIO_USER: {
		struct puser_nice_args punice;

		if (uap->who == 0)
			uap->who = kauth_cred_getuid(kauth_cred_get());

		punice.curp = curp;
		punice.prio = uap->prio;
		punice.who = uap->who;
		punice.foundp = &found;
		error = 0;
		punice.errorp = &error;
		proc_iterate(PROC_ALLPROCLIST, puser_donice_callback, (void *)&punice, NULL, NULL);

		break;
	}

	case PRIO_DARWIN_THREAD: {
		/* we currently only support the current thread */
		if (uap->who != 0)
			return (EINVAL);

		error = do_background_thread(current_thread(), uap->prio);
		found++;
		break;
	}

	case PRIO_DARWIN_PROCESS: {
		if (uap->who == 0)
			p = curp;
		else {
			p = proc_find(uap->who);
			if (p == 0)
				break;
			refheld = 1;
		}

		error = do_background_proc(curp, p, uap->prio);

		found++;
		if (refheld != 0)
			proc_rele(p);
		break;
	}

	case PRIO_DARWIN_GPU: {
		if (uap->who == 0)
			return (EINVAL);

		p = proc_find(uap->who);
		if (p == PROC_NULL)
			break;

		error = set_gpudeny_proc(curp, p, uap->prio);

		found++;
		proc_rele(p);
		break;
	}

	case PRIO_DARWIN_ROLE: {
		if (uap->who == 0) {
			p = curp;
		} else {
			p = proc_find(uap->who);
			if (p == PROC_NULL)
				break;
			refheld = 1;
		}

		error = proc_set_darwin_role(curp, p, uap->prio);

		found++;
		if (refheld != 0)
			proc_rele(p);
		break;
	}

	default:
		return (EINVAL);
	}
	if (found == 0)
		return (ESRCH);
	if (error == EIDRM) {
		*retval = -2;
		error = 0;
	}
	return (error);
}