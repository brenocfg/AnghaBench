#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct task_security_struct {scalar_t__ sid; scalar_t__ osid; } ;
struct rlimit {int /*<<< orphan*/  rlim_cur; int /*<<< orphan*/  rlim_max; } ;
struct linux_binprm {TYPE_5__* cred; } ;
struct TYPE_11__ {struct task_security_struct* security; } ;
struct TYPE_10__ {TYPE_1__* signal; } ;
struct TYPE_9__ {TYPE_2__* signal; scalar_t__ pdeath_signal; int /*<<< orphan*/  files; } ;
struct TYPE_8__ {struct rlimit* rlim; } ;
struct TYPE_7__ {struct rlimit* rlim; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROCESS__RLIMITINH ; 
 size_t RLIMIT_CPU ; 
 int RLIM_NLIMITS ; 
 int /*<<< orphan*/  SECCLASS_PROCESS ; 
 int avc_has_perm (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  flush_unauthorized_files (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_4__ init_task ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_rlimit_cpu (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void selinux_bprm_committing_creds(struct linux_binprm *bprm)
{
	struct task_security_struct *new_tsec;
	struct rlimit *rlim, *initrlim;
	int rc, i;

	new_tsec = bprm->cred->security;
	if (new_tsec->sid == new_tsec->osid)
		return;

	/* Close files for which the new task SID is not authorized. */
	flush_unauthorized_files(bprm->cred, current->files);

	/* Always clear parent death signal on SID transitions. */
	current->pdeath_signal = 0;

	/* Check whether the new SID can inherit resource limits from the old
	 * SID.  If not, reset all soft limits to the lower of the current
	 * task's hard limit and the init task's soft limit.
	 *
	 * Note that the setting of hard limits (even to lower them) can be
	 * controlled by the setrlimit check.  The inclusion of the init task's
	 * soft limit into the computation is to avoid resetting soft limits
	 * higher than the default soft limit for cases where the default is
	 * lower than the hard limit, e.g. RLIMIT_CORE or RLIMIT_STACK.
	 */
	rc = avc_has_perm(new_tsec->osid, new_tsec->sid, SECCLASS_PROCESS,
			  PROCESS__RLIMITINH, NULL);
	if (rc) {
		for (i = 0; i < RLIM_NLIMITS; i++) {
			rlim = current->signal->rlim + i;
			initrlim = init_task.signal->rlim + i;
			rlim->rlim_cur = min(rlim->rlim_max, initrlim->rlim_cur);
		}
		update_rlimit_cpu(current,
				current->signal->rlim[RLIMIT_CPU].rlim_cur);
	}
}