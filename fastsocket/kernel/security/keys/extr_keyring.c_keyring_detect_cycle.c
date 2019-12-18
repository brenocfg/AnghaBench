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
struct keyring_list {int nkeys; struct key** keys; } ;
struct TYPE_2__ {int /*<<< orphan*/  subscriptions; } ;
struct key {int /*<<< orphan*/ * type; TYPE_1__ payload; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EDEADLK ; 
 int ELOOP ; 
 int KEYRING_SEARCH_MAX_DEPTH ; 
 int /*<<< orphan*/  KEY_FLAG_REVOKED ; 
 int /*<<< orphan*/  key_type_keyring ; 
 struct keyring_list* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int keyring_detect_cycle(struct key *A, struct key *B)
{
	struct {
		struct keyring_list *keylist;
		int kix;
	} stack[KEYRING_SEARCH_MAX_DEPTH];

	struct keyring_list *keylist;
	struct key *subtree, *key;
	int sp, nkeys, kix, ret;

	rcu_read_lock();

	ret = -EDEADLK;
	if (A == B)
		goto cycle_detected;

	subtree = B;
	sp = 0;

	/* start processing a new keyring */
descend:
	if (test_bit(KEY_FLAG_REVOKED, &subtree->flags))
		goto not_this_keyring;

	keylist = rcu_dereference(subtree->payload.subscriptions);
	if (!keylist)
		goto not_this_keyring;
	kix = 0;

ascend:
	/* iterate through the remaining keys in this keyring */
	nkeys = keylist->nkeys;
	smp_rmb();
	for (; kix < nkeys; kix++) {
		key = keylist->keys[kix];

		if (key == A)
			goto cycle_detected;

		/* recursively check nested keyrings */
		if (key->type == &key_type_keyring) {
			if (sp >= KEYRING_SEARCH_MAX_DEPTH)
				goto too_deep;

			/* stack the current position */
			stack[sp].keylist = keylist;
			stack[sp].kix = kix;
			sp++;

			/* begin again with the new keyring */
			subtree = key;
			goto descend;
		}
	}

	/* the keyring we're looking at was disqualified or didn't contain a
	 * matching key */
not_this_keyring:
	if (sp > 0) {
		/* resume the checking of a keyring higher up in the tree */
		sp--;
		keylist = stack[sp].keylist;
		kix = stack[sp].kix + 1;
		goto ascend;
	}

	ret = 0; /* no cycles detected */

error:
	rcu_read_unlock();
	return ret;

too_deep:
	ret = -ELOOP;
	goto error;

cycle_detected:
	ret = -EDEADLK;
	goto error;
}