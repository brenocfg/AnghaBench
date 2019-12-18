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
struct keyring_list {int /*<<< orphan*/  rcu; } ;
struct TYPE_2__ {int /*<<< orphan*/  subscriptions; } ;
struct key {int /*<<< orphan*/  sem; TYPE_1__ payload; int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 int ENOTDIR ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_payload_reserve (struct key*,int) ; 
 int /*<<< orphan*/  key_type_keyring ; 
 int /*<<< orphan*/  keyring_clear_rcu_disposal ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct keyring_list* rcu_dereference_locked_keyring (struct key*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int keyring_clear(struct key *keyring)
{
	struct keyring_list *klist;
	int ret;

	ret = -ENOTDIR;
	if (keyring->type == &key_type_keyring) {
		/* detach the pointer block with the locks held */
		down_write(&keyring->sem);

		klist = rcu_dereference_locked_keyring(keyring);
		if (klist) {
			/* adjust the quota */
			key_payload_reserve(keyring,
					    sizeof(struct keyring_list));

			rcu_assign_pointer(keyring->payload.subscriptions,
					   NULL);
		}

		up_write(&keyring->sem);

		/* free the keys after the locks have been dropped */
		if (klist)
			call_rcu(&klist->rcu, keyring_clear_rcu_disposal);

		ret = 0;
	}

	return ret;
}