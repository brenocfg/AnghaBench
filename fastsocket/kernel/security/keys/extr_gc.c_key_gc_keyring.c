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
typedef  scalar_t__ time_t ;
struct keyring_list {int nkeys; struct key** keys; } ;
struct TYPE_2__ {int /*<<< orphan*/  subscriptions; } ;
struct key {scalar_t__ expiry; int /*<<< orphan*/  flags; TYPE_1__ payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_FLAG_DEAD ; 
 int /*<<< orphan*/  KEY_FLAG_REVOKED ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  keyring_gc (struct key*,scalar_t__) ; 
 int /*<<< orphan*/  kleave (char*) ; 
 struct keyring_list* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void key_gc_keyring(struct key *keyring, time_t limit)
{
	struct keyring_list *klist;
	struct key *key;
	int loop;

	kenter("%x", key_serial(keyring));

	if (test_bit(KEY_FLAG_REVOKED, &keyring->flags))
		goto dont_gc;

	/* scan the keyring looking for dead keys */
	rcu_read_lock();
	klist = rcu_dereference(keyring->payload.subscriptions);
	if (!klist)
		goto unlock_dont_gc;

	loop = klist->nkeys;
	smp_rmb();
	for (loop--; loop >= 0; loop--) {
		key = klist->keys[loop];
		if (test_bit(KEY_FLAG_DEAD, &key->flags) ||
		    (key->expiry > 0 && key->expiry <= limit))
			goto do_gc;
	}

unlock_dont_gc:
	rcu_read_unlock();
dont_gc:
	kleave(" [no gc]");
	return;

do_gc:
	rcu_read_unlock();

	keyring_gc(keyring, limit);
	kleave(" [gc]");
}