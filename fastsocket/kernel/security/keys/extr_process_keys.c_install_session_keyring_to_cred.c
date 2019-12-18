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
struct key {int /*<<< orphan*/  usage; } ;
struct cred {TYPE_1__* tgcred; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct key* session_keyring; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct key*) ; 
 unsigned long KEY_ALLOC_IN_QUOTA ; 
 unsigned long KEY_ALLOC_QUOTA_OVERRUN ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 struct key* keyring_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct key*,struct key*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int install_session_keyring_to_cred(struct cred *cred,
					   struct key *keyring)
{
	unsigned long flags;
	struct key *old;

	might_sleep();

	/* create an empty session keyring */
	if (!keyring) {
		flags = KEY_ALLOC_QUOTA_OVERRUN;
		if (cred->tgcred->session_keyring)
			flags = KEY_ALLOC_IN_QUOTA;

		keyring = keyring_alloc("_ses", cred->uid, cred->gid,
					cred, flags, NULL);
		if (IS_ERR(keyring))
			return PTR_ERR(keyring);
	} else {
		atomic_inc(&keyring->usage);
	}

	/* install the keyring */
	spin_lock_irq(&cred->tgcred->lock);
	old = cred->tgcred->session_keyring;
	rcu_assign_pointer(cred->tgcred->session_keyring, keyring);
	spin_unlock_irq(&cred->tgcred->lock);

	/* we're using RCU on the pointer, but there's no point synchronising
	 * on it if it didn't previously point to anything */
	if (old) {
		synchronize_rcu();
		key_put(old);
	}

	return 0;
}