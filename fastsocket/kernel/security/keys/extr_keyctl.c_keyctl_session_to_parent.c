#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int pid; struct cred* replacement_session_keyring; int /*<<< orphan*/  mm; struct task_struct* real_parent; } ;
struct cred {scalar_t__ uid; scalar_t__ euid; scalar_t__ suid; scalar_t__ gid; scalar_t__ egid; scalar_t__ sgid; TYPE_1__* tgcred; } ;
typedef  int /*<<< orphan*/ * key_ref_t ;
struct TYPE_5__ {scalar_t__ uid; } ;
struct TYPE_4__ {TYPE_2__* session_keyring; } ;

/* Variables and functions */
 int ENOMEM ; 
 long EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_LINK ; 
 int /*<<< orphan*/  KEY_SPEC_SESSION_KEYRING ; 
 long PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIF_NOTIFY_RESUME ; 
 struct cred* __task_cred (struct task_struct*) ; 
 struct cred* cred_alloc_blank () ; 
 struct task_struct* current ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  key_ref_put (int /*<<< orphan*/ *) ; 
 TYPE_2__* key_ref_to_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookup_user_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cred (struct cred*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int security_key_session_to_parent (struct cred const*,struct cred const*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_ti_thread_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_thread_info (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  thread_group_empty (struct task_struct*) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

long keyctl_session_to_parent(void)
{
#ifdef TIF_NOTIFY_RESUME
	struct task_struct *me, *parent;
	const struct cred *mycred, *pcred;
	struct cred *cred, *oldcred;
	key_ref_t keyring_r;
	int ret;

	keyring_r = lookup_user_key(KEY_SPEC_SESSION_KEYRING, 0, KEY_LINK);
	if (IS_ERR(keyring_r))
		return PTR_ERR(keyring_r);

	/* our parent is going to need a new cred struct, a new tgcred struct
	 * and new security data, so we allocate them here to prevent ENOMEM in
	 * our parent */
	ret = -ENOMEM;
	cred = cred_alloc_blank();
	if (!cred)
		goto error_keyring;

	cred->tgcred->session_keyring = key_ref_to_ptr(keyring_r);
	keyring_r = NULL;

	me = current;
	rcu_read_lock();
	write_lock_irq(&tasklist_lock);

	parent = me->real_parent;
	ret = -EPERM;

	/* the parent mustn't be init and mustn't be a kernel thread */
	if (parent->pid <= 1 || !parent->mm)
		goto not_permitted;

	/* the parent must be single threaded */
	if (!thread_group_empty(parent))
		goto not_permitted;

	/* the parent and the child must have different session keyrings or
	 * there's no point */
	mycred = current_cred();
	pcred = __task_cred(parent);
	if (mycred == pcred ||
	    mycred->tgcred->session_keyring == pcred->tgcred->session_keyring)
		goto already_same;

	/* the parent must have the same effective ownership and mustn't be
	 * SUID/SGID */
	if (pcred->uid	!= mycred->euid	||
	    pcred->euid	!= mycred->euid	||
	    pcred->suid	!= mycred->euid	||
	    pcred->gid	!= mycred->egid	||
	    pcred->egid	!= mycred->egid	||
	    pcred->sgid	!= mycred->egid)
		goto not_permitted;

	/* the keyrings must have the same UID */
	if ((pcred->tgcred->session_keyring &&
	     pcred->tgcred->session_keyring->uid != mycred->euid) ||
	    mycred->tgcred->session_keyring->uid != mycred->euid)
		goto not_permitted;

	/* the LSM must permit the replacement of the parent's keyring with the
	 * keyring from this process */
	ret = security_key_session_to_parent(mycred, pcred,
					     key_ref_to_ptr(keyring_r));
	if (ret < 0)
		goto not_permitted;

	/* if there's an already pending keyring replacement, then we replace
	 * that */
	oldcred = parent->replacement_session_keyring;

	/* the replacement session keyring is applied just prior to userspace
	 * restarting */
	parent->replacement_session_keyring = cred;
	cred = NULL;
	set_ti_thread_flag(task_thread_info(parent), TIF_NOTIFY_RESUME);

	write_unlock_irq(&tasklist_lock);
	rcu_read_unlock();
	if (oldcred)
		put_cred(oldcred);
	return 0;

already_same:
	ret = 0;
not_permitted:
	write_unlock_irq(&tasklist_lock);
	rcu_read_unlock();
	put_cred(cred);
	return ret;

error_keyring:
	key_ref_put(keyring_r);
	return ret;

#else /* !TIF_NOTIFY_RESUME */
	/*
	 * To be removed when TIF_NOTIFY_RESUME has been implemented on
	 * m68k/xtensa
	 */
#warning TIF_NOTIFY_RESUME not implemented
	return -EOPNOTSUPP;
#endif /* !TIF_NOTIFY_RESUME */
}