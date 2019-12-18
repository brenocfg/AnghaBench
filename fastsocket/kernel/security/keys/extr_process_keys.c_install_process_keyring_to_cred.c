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
struct key {int dummy; } ;
struct cred {TYPE_1__* tgcred; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct key* process_keyring; } ;

/* Variables and functions */
 int EEXIST ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_ALLOC_QUOTA_OVERRUN ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 struct key* keyring_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int install_process_keyring_to_cred(struct cred *new)
{
	struct key *keyring;
	int ret;

	if (new->tgcred->process_keyring)
		return -EEXIST;

	keyring = keyring_alloc("_pid", new->uid, new->gid,
				new, KEY_ALLOC_QUOTA_OVERRUN, NULL);
	if (IS_ERR(keyring))
		return PTR_ERR(keyring);

	spin_lock_irq(&new->tgcred->lock);
	if (!new->tgcred->process_keyring) {
		new->tgcred->process_keyring = keyring;
		keyring = NULL;
		ret = 0;
	} else {
		ret = -EEXIST;
	}
	spin_unlock_irq(&new->tgcred->lock);
	key_put(keyring);
	return ret;
}