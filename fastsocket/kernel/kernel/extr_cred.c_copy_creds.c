#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread_group_cred {int /*<<< orphan*/  session_keyring; int /*<<< orphan*/ * process_keyring; int /*<<< orphan*/  lock; int /*<<< orphan*/  usage; } ;
struct task_struct {struct cred* real_cred; struct cred* cred; int /*<<< orphan*/ * replacement_session_keyring; int /*<<< orphan*/  cred_guard_mutex; } ;
struct cred {TYPE_1__* user; struct thread_group_cred* tgcred; int /*<<< orphan*/ * thread_keyring; int /*<<< orphan*/  usage; } ;
struct TYPE_2__ {int /*<<< orphan*/  processes; } ;

/* Variables and functions */
 unsigned long CLONE_NEWUSER ; 
 unsigned long CLONE_THREAD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alter_cred_subscribers (struct cred*,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int create_user_ns (struct cred*) ; 
 void* get_cred (struct cred*) ; 
 int /*<<< orphan*/  install_thread_keyring_to_cred (struct cred*) ; 
 int /*<<< orphan*/  kdebug (char*,struct cred*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ *) ; 
 struct thread_group_cred* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct cred* prepare_creds () ; 
 int /*<<< orphan*/  put_cred (struct cred*) ; 
 int /*<<< orphan*/  read_cred_subscribers (struct cred*) ; 
 int /*<<< orphan*/  release_tgcred (struct cred*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validate_creds (struct cred*) ; 

int copy_creds(struct task_struct *p, unsigned long clone_flags)
{
#ifdef CONFIG_KEYS
	struct thread_group_cred *tgcred;
#endif
	struct cred *new;
	int ret;

	mutex_init(&p->cred_guard_mutex);
	p->replacement_session_keyring = NULL;

	if (
#ifdef CONFIG_KEYS
		!p->cred->thread_keyring &&
#endif
		clone_flags & CLONE_THREAD
	    ) {
		p->real_cred = get_cred(p->cred);
		get_cred(p->cred);
		alter_cred_subscribers(p->cred, 2);
		kdebug("share_creds(%p{%d,%d})",
		       p->cred, atomic_read(&p->cred->usage),
		       read_cred_subscribers(p->cred));
		atomic_inc(&p->cred->user->processes);
		return 0;
	}

	new = prepare_creds();
	if (!new)
		return -ENOMEM;

	if (clone_flags & CLONE_NEWUSER) {
		ret = create_user_ns(new);
		if (ret < 0)
			goto error_put;
	}

#ifdef CONFIG_KEYS
	/* new threads get their own thread keyrings if their parent already
	 * had one */
	if (new->thread_keyring) {
		key_put(new->thread_keyring);
		new->thread_keyring = NULL;
		if (clone_flags & CLONE_THREAD)
			install_thread_keyring_to_cred(new);
	}

	/* we share the process and session keyrings between all the threads in
	 * a process - this is slightly icky as we violate COW credentials a
	 * bit */
	if (!(clone_flags & CLONE_THREAD)) {
		tgcred = kmalloc(sizeof(*tgcred), GFP_KERNEL);
		if (!tgcred) {
			ret = -ENOMEM;
			goto error_put;
		}
		atomic_set(&tgcred->usage, 1);
		spin_lock_init(&tgcred->lock);
		tgcred->process_keyring = NULL;
		tgcred->session_keyring = key_get(new->tgcred->session_keyring);

		release_tgcred(new);
		new->tgcred = tgcred;
	}
#endif

	atomic_inc(&new->user->processes);
	p->cred = p->real_cred = get_cred(new);
	alter_cred_subscribers(new, 2);
	validate_creds(new);
	return 0;

error_put:
	put_cred(new);
	return ret;
}