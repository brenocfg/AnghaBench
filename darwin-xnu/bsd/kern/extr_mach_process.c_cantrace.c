#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_9__ {scalar_t__ p_pid; int p_lflag; int p_flag; int /*<<< orphan*/  p_acflag; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ ISSET (int,int) ; 
 int P_LNOATTACH ; 
 int P_LTRACED ; 
 int P_SUGID ; 
 scalar_t__ isinferior (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ kauth_cred_getruid (int /*<<< orphan*/ ) ; 
 int mac_proc_check_debug (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  proc_ucred (TYPE_1__*) ; 
 int suser (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
cantrace(proc_t cur_procp, kauth_cred_t creds, proc_t traced_procp, int *errp)
{
	int		my_err;
	/*
	 * You can't trace a process if:
	 *	(1) it's the process that's doing the tracing,
	 */
	if (traced_procp->p_pid == cur_procp->p_pid) {
		*errp = EINVAL;
		return (0);
	}

	/*
	 *	(2) it's already being traced, or
	 */
	if (ISSET(traced_procp->p_lflag, P_LTRACED)) {
		*errp = EBUSY;
		return (0);
	}

	/*
	 *	(3) it's not owned by you, or is set-id on exec
	 *	    (unless you're root).
	 */
	if ((kauth_cred_getruid(creds) != kauth_cred_getruid(proc_ucred(traced_procp)) ||
		ISSET(traced_procp->p_flag, P_SUGID)) &&
		(my_err = suser(creds, &cur_procp->p_acflag)) != 0) {
		*errp = my_err;
		return (0);
	}

	if ((cur_procp->p_lflag & P_LTRACED) && isinferior(cur_procp, traced_procp)) {
		*errp = EPERM;
		return (0);
	}

	if (ISSET(traced_procp->p_lflag, P_LNOATTACH)) {
		*errp = EBUSY;
		return (0);
	}

#if CONFIG_MACF
	if ((my_err = mac_proc_check_debug(cur_procp, traced_procp)) != 0) {
		*errp = my_err;
		return (0);
	}
#endif

	return(1);
}