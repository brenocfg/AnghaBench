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
struct thread_group_cred {int /*<<< orphan*/ * process_keyring; int /*<<< orphan*/  session_keyring; int /*<<< orphan*/  lock; int /*<<< orphan*/  usage; } ;
struct cred {struct thread_group_cred* tgcred; int /*<<< orphan*/ * thread_keyring; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  key_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct thread_group_cred*) ; 
 struct thread_group_cred* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct thread_group_cred*,struct thread_group_cred*,int) ; 
 struct cred* prepare_creds () ; 
 int /*<<< orphan*/  release_tgcred (struct cred*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct cred *prepare_exec_creds(void)
{
	struct thread_group_cred *tgcred = NULL;
	struct cred *new;

#ifdef CONFIG_KEYS
	tgcred = kmalloc(sizeof(*tgcred), GFP_KERNEL);
	if (!tgcred)
		return NULL;
#endif

	new = prepare_creds();
	if (!new) {
		kfree(tgcred);
		return new;
	}

#ifdef CONFIG_KEYS
	/* newly exec'd tasks don't get a thread keyring */
	key_put(new->thread_keyring);
	new->thread_keyring = NULL;

	/* create a new per-thread-group creds for all this set of threads to
	 * share */
	memcpy(tgcred, new->tgcred, sizeof(struct thread_group_cred));

	atomic_set(&tgcred->usage, 1);
	spin_lock_init(&tgcred->lock);

	/* inherit the session keyring; new process keyring */
	key_get(tgcred->session_keyring);
	tgcred->process_keyring = NULL;

	release_tgcred(new);
	new->tgcred = tgcred;
#endif

	return new;
}