#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* uthread_t ;
typedef  scalar_t__ task_t ;
struct TYPE_24__ {scalar_t__* val; } ;
typedef  TYPE_4__ security_token_t ;
typedef  TYPE_5__* proc_t ;
typedef  TYPE_6__* posix_cred_t ;
typedef  TYPE_7__* kauth_cred_t ;
typedef  scalar_t__ host_priv_t ;
struct TYPE_28__ {int /*<<< orphan*/ * val; } ;
typedef  TYPE_8__ audit_token_t ;
struct TYPE_22__ {TYPE_1__* as_aia_p; } ;
struct TYPE_27__ {TYPE_2__ cr_audit; } ;
struct TYPE_26__ {int /*<<< orphan*/  cr_rgid; int /*<<< orphan*/  cr_ruid; int /*<<< orphan*/  cr_gid; int /*<<< orphan*/  cr_uid; } ;
struct TYPE_25__ {int /*<<< orphan*/  p_idversion; int /*<<< orphan*/  p_pid; } ;
struct TYPE_23__ {int uu_flag; } ;
struct TYPE_21__ {int /*<<< orphan*/  ai_asid; int /*<<< orphan*/  ai_auid; } ;

/* Variables and functions */
 scalar_t__ HOST_PRIV_NULL ; 
 scalar_t__ IS_VALID_CRED (TYPE_7__*) ; 
 scalar_t__ KERN_SUCCESS ; 
 int UT_VFORK ; 
 scalar_t__ current_task () ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ get_bsdthread_info (int /*<<< orphan*/ ) ; 
 scalar_t__ host_priv_self () ; 
 int /*<<< orphan*/  host_security_self () ; 
 scalar_t__ host_security_set_task_token (int /*<<< orphan*/ ,scalar_t__,TYPE_4__,TYPE_8__,scalar_t__) ; 
 scalar_t__ kauth_cred_getgid (TYPE_7__*) ; 
 scalar_t__ kauth_cred_getuid (TYPE_7__*) ; 
 TYPE_7__* kauth_cred_proc_ref (TYPE_5__*) ; 
 int /*<<< orphan*/  kauth_cred_unref (TYPE_7__**) ; 
 scalar_t__ mac_system_check_host_priv (TYPE_7__*) ; 
 TYPE_6__* posix_cred_get (TYPE_7__*) ; 
 int /*<<< orphan*/  task_importance_update_owner_info (scalar_t__) ; 

int
set_security_token_task_internal(proc_t p, void *t)
{
	security_token_t sec_token;
	audit_token_t    audit_token;
	kauth_cred_t my_cred;
	posix_cred_t my_pcred;
	host_priv_t host_priv;
	task_t task = t;

	/*
	 * Don't allow a vfork child to override the parent's token settings
	 * (since they share a task).  Instead, the child will just have to
	 * suffer along using the parent's token until the exec().  It's all
	 * undefined behavior anyway, right?
	 */
	if (task == current_task()) {
		uthread_t	 uthread;
		uthread = (uthread_t)get_bsdthread_info(current_thread());
		if (uthread->uu_flag & UT_VFORK)
			return (1);
	}
		
	my_cred = kauth_cred_proc_ref(p);
	my_pcred = posix_cred_get(my_cred);

	/* XXX mach_init doesn't have a p_ucred when it calls this function */
	if (IS_VALID_CRED(my_cred)) {
		sec_token.val[0] = kauth_cred_getuid(my_cred);
		sec_token.val[1] = kauth_cred_getgid(my_cred);
	} else {
		sec_token.val[0] = 0;
		sec_token.val[1] = 0;
	}

	/*
	 * The current layout of the Mach audit token explicitly
	 * adds these fields.  But nobody should rely on such
	 * a literal representation.  Instead, the BSM library
	 * provides a function to convert an audit token into
	 * a BSM subject.  Use of that mechanism will isolate
	 * the user of the trailer from future representation
	 * changes.
	 */
	audit_token.val[0] = my_cred->cr_audit.as_aia_p->ai_auid;
	audit_token.val[1] = my_pcred->cr_uid;
	audit_token.val[2] = my_pcred->cr_gid;
	audit_token.val[3] = my_pcred->cr_ruid;
	audit_token.val[4] = my_pcred->cr_rgid;
	audit_token.val[5] = p->p_pid;
	audit_token.val[6] = my_cred->cr_audit.as_aia_p->ai_asid;
	audit_token.val[7] = p->p_idversion;

	host_priv = (sec_token.val[0]) ? HOST_PRIV_NULL : host_priv_self();
#if CONFIG_MACF
	if (host_priv != HOST_PRIV_NULL && mac_system_check_host_priv(my_cred))
		host_priv = HOST_PRIV_NULL;
#endif
	kauth_cred_unref(&my_cred);

#if DEVELOPMENT || DEBUG
	/* 
	 * Update the pid an proc name for importance base if any
	 */
	task_importance_update_owner_info(task);
#endif

	return (host_security_set_task_token(host_security_self(),
					   task,
					   sec_token,
					   audit_token,
					   host_priv) != KERN_SUCCESS);
}