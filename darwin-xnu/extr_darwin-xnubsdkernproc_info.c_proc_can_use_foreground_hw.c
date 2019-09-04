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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int uint32_t ;
typedef  scalar_t__ task_t ;
typedef  int /*<<< orphan*/  reason ;
typedef  scalar_t__ proc_t ;
typedef  int int32_t ;

/* Variables and functions */
#define  EINVAL 130 
#define  ENOATTR 129 
#define  ESRCH 128 
 int PROC_FGHW_DAEMON_NO_VOUCHER ; 
 int PROC_FGHW_DAEMON_OK ; 
 int PROC_FGHW_ERROR ; 
 int PROC_FGHW_NO_ORIGINATOR ; 
 int PROC_FGHW_NO_VOUCHER_ATTR ; 
 int PROC_FGHW_ORIGINATOR_BACKGROUND ; 
 int PROC_FGHW_VOUCHER_ERROR ; 
 scalar_t__ PROC_NULL ; 
 scalar_t__ TASK_NULL ; 
 int /*<<< orphan*/  copyout (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ current_proc () ; 
 scalar_t__ proc_find (int) ; 
 int proc_get_originatorbgstate (int*) ; 
 int /*<<< orphan*/  proc_rele (scalar_t__) ; 
 int /*<<< orphan*/  task_deallocate (scalar_t__) ; 

int proc_can_use_foreground_hw(int pid, user_addr_t u_reason, uint32_t reasonsize, int32_t *retval)
{
	proc_t p = PROC_NULL;
	int error = 0;
	uint32_t reason = PROC_FGHW_ERROR;
	uint32_t isBG = 0;
	task_t task = TASK_NULL;
#if CONFIG_COALITIONS
	coalition_t coal = COALITION_NULL;
#endif

	*retval = 0;

	if (pid <= 0) {
		error = EINVAL;
		reason = PROC_FGHW_ERROR;
		goto out;
	}

	p = proc_find(pid);
	if (p == PROC_NULL) {
		error = ESRCH;
		reason = PROC_FGHW_ERROR;
		goto out;
	}

#if CONFIG_COALITIONS
	if (p != current_proc() &&
	    !kauth_cred_issuser(kauth_cred_get())) {
		error = EPERM;
		reason = PROC_FGHW_ERROR;
		goto out;
	}

	task = p->task;
	task_reference(task);
	if (coalition_is_leader(task, COALITION_TYPE_JETSAM, &coal) == FALSE) {
		/* current task is not a coalition leader: find the leader */
		task_deallocate(task);
		task = coalition_get_leader(coal);
	}

	if (task != TASK_NULL) {
		/*
		 * If task is non-null, then it is the coalition leader of the
		 * current process' coalition. This could be the same task as
		 * the current_task, and that's OK.
		 */
		uint32_t flags = 0;
		int role;

		proc_get_darwinbgstate(task, &flags);
		if ((flags & PROC_FLAG_APPLICATION) != PROC_FLAG_APPLICATION) {
			/*
			 * Coalition leader is not an application, continue
			 * searching for other ways this task could gain
			 * access to HW
			 */
			reason = PROC_FGHW_DAEMON_LEADER;
			goto no_leader;
		}

		if (proc_get_effective_task_policy(task, TASK_POLICY_DARWIN_BG)) {
			/*
			 * If the leader of the current process' coalition has
			 * been marked as DARWIN_BG, then it definitely should
			 * not be using foreground hardware resources.
			 */
			reason = PROC_FGHW_LEADER_BACKGROUND;
			goto out;
		}

		role = proc_get_effective_task_policy(task, TASK_POLICY_ROLE);
		switch (role) {
		case TASK_FOREGROUND_APPLICATION: /* DARWIN_ROLE_UI_FOCAL */
		case TASK_BACKGROUND_APPLICATION: /* DARWIN_ROLE_UI */
			/*
			 * The leader of this coalition is a focal, UI app:
			 * access granted
			 * TODO: should extensions/plugins be allowed to use
			 *       this hardware?
			 */
			*retval = 1;
			reason = PROC_FGHW_OK;
			goto out;
		case TASK_DEFAULT_APPLICATION: /* DARWIN_ROLE_UI_NON_FOCAL */
		case TASK_NONUI_APPLICATION: /* DARWIN_ROLE_NON_UI */
		case TASK_THROTTLE_APPLICATION:
		case TASK_UNSPECIFIED:
		default:
			/* non-focal, non-ui apps don't get access */
			reason = PROC_FGHW_LEADER_NONUI;
			goto out;
		}
	}

no_leader:
	if (task != TASK_NULL) {
		task_deallocate(task);
		task = TASK_NULL;
	}
#endif /* CONFIG_COALITIONS */

	/*
	 * There is no reasonable semantic to investigate the currently
	 * adopted voucher of an arbitrary thread in a non-current process.
	 * We return '0'
	 */
	if (p != current_proc()) {
		error = EINVAL;
		goto out;
	}

	/*
	 * In the absence of coalitions, fall back to a voucher-based lookup
	 * where a daemon can used foreground HW if it's operating on behalf
	 * of a foreground application.
	 * NOTE: this is equivalent to a call to
	 *       proc_pidoriginatorinfo(PROC_PIDORIGINATOR_BGSTATE, &isBG, sizeof(isBG))
	 */
	isBG = 1;
	error = proc_get_originatorbgstate(&isBG);
	switch (error) {
	case 0:
		break;
	case ESRCH:
		reason = PROC_FGHW_NO_ORIGINATOR;
		error = 0;
		goto out;
	case ENOATTR:
		reason = PROC_FGHW_NO_VOUCHER_ATTR;
		error = 0;
		goto out;
	case EINVAL:
		reason = PROC_FGHW_DAEMON_NO_VOUCHER;
		error = 0;
		goto out;
	default:
		/* some other error occurred: report that to the caller */
		reason = PROC_FGHW_VOUCHER_ERROR;
		goto out;
	}

	if (isBG) {
		reason = PROC_FGHW_ORIGINATOR_BACKGROUND;
		error = 0;
	} else {
		/*
		 * The process itself is either a foreground app, or has
		 * adopted a voucher originating from an app that's still in
		 * the foreground
		 */
		reason = PROC_FGHW_DAEMON_OK;
		*retval = 1;
	}

out:
	if (task != TASK_NULL)
		task_deallocate(task);
	if (p != PROC_NULL)
		proc_rele(p);
	if (reasonsize >= sizeof(reason) && u_reason != (user_addr_t)0)
		(void)copyout(&reason, u_reason, sizeof(reason));
	return error;
}