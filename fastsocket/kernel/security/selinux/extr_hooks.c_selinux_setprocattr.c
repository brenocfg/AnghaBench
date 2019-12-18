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
typedef  scalar_t__ u32 ;
struct task_struct {int dummy; } ;
struct task_security_struct {scalar_t__ sid; scalar_t__ sockcreate_sid; scalar_t__ keycreate_sid; scalar_t__ create_sid; scalar_t__ exec_sid; } ;
struct cred {struct task_security_struct* security; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_MAC_ADMIN ; 
 int EACCES ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  PROCESS__DYNTRANSITION ; 
 int /*<<< orphan*/  PROCESS__PTRACE ; 
 int /*<<< orphan*/  PROCESS__SETCURRENT ; 
 int /*<<< orphan*/  PROCESS__SETEXEC ; 
 int /*<<< orphan*/  PROCESS__SETFSCREATE ; 
 int /*<<< orphan*/  PROCESS__SETKEYCREATE ; 
 int /*<<< orphan*/  PROCESS__SETSOCKCREATE ; 
 int /*<<< orphan*/  SECCLASS_PROCESS ; 
 int /*<<< orphan*/  abort_creds (struct cred*) ; 
 int avc_has_perm (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_creds (struct cred*) ; 
 struct task_struct* current ; 
 int current_has_perm (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_is_single_threaded () ; 
 int may_create_key (scalar_t__,struct task_struct*) ; 
 struct cred* prepare_creds () ; 
 int security_bounded_transition (scalar_t__,scalar_t__) ; 
 int security_context_to_sid (void*,size_t,scalar_t__*) ; 
 int security_context_to_sid_force (void*,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 scalar_t__ task_sid (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 struct task_struct* tracehook_tracer_task (struct task_struct*) ; 

__attribute__((used)) static int selinux_setprocattr(struct task_struct *p,
			       char *name, void *value, size_t size)
{
	struct task_security_struct *tsec;
	struct task_struct *tracer;
	struct cred *new;
	u32 sid = 0, ptsid;
	int error;
	char *str = value;

	if (current != p) {
		/* SELinux only allows a process to change its own
		   security attributes. */
		return -EACCES;
	}

	/*
	 * Basic control over ability to set these attributes at all.
	 * current == p, but we'll pass them separately in case the
	 * above restriction is ever removed.
	 */
	if (!strcmp(name, "exec"))
		error = current_has_perm(p, PROCESS__SETEXEC);
	else if (!strcmp(name, "fscreate"))
		error = current_has_perm(p, PROCESS__SETFSCREATE);
	else if (!strcmp(name, "keycreate"))
		error = current_has_perm(p, PROCESS__SETKEYCREATE);
	else if (!strcmp(name, "sockcreate"))
		error = current_has_perm(p, PROCESS__SETSOCKCREATE);
	else if (!strcmp(name, "current"))
		error = current_has_perm(p, PROCESS__SETCURRENT);
	else
		error = -EINVAL;
	if (error)
		return error;

	/* Obtain a SID for the context, if one was specified. */
	if (size && str[1] && str[1] != '\n') {
		if (str[size-1] == '\n') {
			str[size-1] = 0;
			size--;
		}
		error = security_context_to_sid(value, size, &sid);
		if (error == -EINVAL && !strcmp(name, "fscreate")) {
			if (!capable(CAP_MAC_ADMIN))
				return error;
			error = security_context_to_sid_force(value, size,
							      &sid);
		}
		if (error)
			return error;
	}

	new = prepare_creds();
	if (!new)
		return -ENOMEM;

	/* Permission checking based on the specified context is
	   performed during the actual operation (execve,
	   open/mkdir/...), when we know the full context of the
	   operation.  See selinux_bprm_set_creds for the execve
	   checks and may_create for the file creation checks. The
	   operation will then fail if the context is not permitted. */
	tsec = new->security;
	if (!strcmp(name, "exec")) {
		tsec->exec_sid = sid;
	} else if (!strcmp(name, "fscreate")) {
		tsec->create_sid = sid;
	} else if (!strcmp(name, "keycreate")) {
		error = may_create_key(sid, p);
		if (error)
			goto abort_change;
		tsec->keycreate_sid = sid;
	} else if (!strcmp(name, "sockcreate")) {
		tsec->sockcreate_sid = sid;
	} else if (!strcmp(name, "current")) {
		error = -EINVAL;
		if (sid == 0)
			goto abort_change;

		/* Only allow single threaded processes to change context */
		error = -EPERM;
		if (!current_is_single_threaded()) {
			error = security_bounded_transition(tsec->sid, sid);
			if (error)
				goto abort_change;
		}

		/* Check permissions for the transition. */
		error = avc_has_perm(tsec->sid, sid, SECCLASS_PROCESS,
				     PROCESS__DYNTRANSITION, NULL);
		if (error)
			goto abort_change;

		/* Check for ptracing, and update the task SID if ok.
		   Otherwise, leave SID unchanged and fail. */
		ptsid = 0;
		task_lock(p);
		tracer = tracehook_tracer_task(p);
		if (tracer)
			ptsid = task_sid(tracer);
		task_unlock(p);

		if (tracer) {
			error = avc_has_perm(ptsid, sid, SECCLASS_PROCESS,
					     PROCESS__PTRACE, NULL);
			if (error)
				goto abort_change;
		}

		tsec->sid = sid;
	} else {
		error = -EINVAL;
		goto abort_change;
	}

	commit_creds(new);
	return size;

abort_change:
	abort_creds(new);
	return error;
}