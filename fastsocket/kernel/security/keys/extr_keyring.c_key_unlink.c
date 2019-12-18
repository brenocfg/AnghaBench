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
struct keyring_list {int nkeys; int maxkeys; int delkey; int /*<<< orphan*/  rcu; struct key** keys; } ;
struct TYPE_2__ {int /*<<< orphan*/  subscriptions; } ;
struct key {int /*<<< orphan*/  sem; TYPE_1__ payload; scalar_t__ datalen; int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ KEYQUOTA_LINK_BYTES ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_check (struct key*) ; 
 int /*<<< orphan*/  key_payload_reserve (struct key*,scalar_t__) ; 
 int /*<<< orphan*/  key_type_keyring ; 
 int /*<<< orphan*/  keyring_unlink_rcu_disposal ; 
 struct keyring_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct key**,struct key**,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct keyring_list*) ; 
 struct keyring_list* rcu_dereference_locked_keyring (struct key*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int key_unlink(struct key *keyring, struct key *key)
{
	struct keyring_list *klist, *nklist;
	int loop, ret;

	key_check(keyring);
	key_check(key);

	ret = -ENOTDIR;
	if (keyring->type != &key_type_keyring)
		goto error;

	down_write(&keyring->sem);

	klist = rcu_dereference_locked_keyring(keyring);
	if (klist) {
		/* search the keyring for the key */
		for (loop = 0; loop < klist->nkeys; loop++)
			if (klist->keys[loop] == key)
				goto key_is_present;
	}

	up_write(&keyring->sem);
	ret = -ENOENT;
	goto error;

key_is_present:
	/* we need to copy the key list for RCU purposes */
	nklist = kmalloc(sizeof(*klist) +
			 sizeof(struct key *) * klist->maxkeys,
			 GFP_KERNEL);
	if (!nklist)
		goto nomem;
	nklist->maxkeys = klist->maxkeys;
	nklist->nkeys = klist->nkeys - 1;

	if (loop > 0)
		memcpy(&nklist->keys[0],
		       &klist->keys[0],
		       loop * sizeof(struct key *));

	if (loop < nklist->nkeys)
		memcpy(&nklist->keys[loop],
		       &klist->keys[loop + 1],
		       (nklist->nkeys - loop) * sizeof(struct key *));

	/* adjust the user's quota */
	key_payload_reserve(keyring,
			    keyring->datalen - KEYQUOTA_LINK_BYTES);

	rcu_assign_pointer(keyring->payload.subscriptions, nklist);

	up_write(&keyring->sem);

	/* schedule for later cleanup */
	klist->delkey = loop;
	call_rcu(&klist->rcu, keyring_unlink_rcu_disposal);

	ret = 0;

error:
	return ret;
nomem:
	ret = -ENOMEM;
	up_write(&keyring->sem);
	goto error;
}