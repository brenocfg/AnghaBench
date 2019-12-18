#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timespec {unsigned int tv_sec; } ;
struct TYPE_4__ {long* x; } ;
struct key {unsigned int expiry; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; TYPE_2__ type_data; TYPE_1__* user; int /*<<< orphan*/  description; } ;
struct TYPE_3__ {int /*<<< orphan*/  nikeys; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  KEY_FLAG_INSTANTIATED ; 
 int /*<<< orphan*/  KEY_FLAG_NEGATIVE ; 
 int /*<<< orphan*/  KEY_FLAG_USER_CONSTRUCT ; 
 int /*<<< orphan*/  __key_link (struct key*,struct key*,unsigned long*) ; 
 int __key_link_begin (struct key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  __key_link_end (struct key*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct timespec current_kernel_time () ; 
 int /*<<< orphan*/  key_check (struct key*) ; 
 int /*<<< orphan*/  key_construction_mutex ; 
 unsigned int key_gc_delay ; 
 int /*<<< orphan*/  key_revoke (struct key*) ; 
 int /*<<< orphan*/  key_schedule_gc (unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int key_reject_and_link(struct key *key,
			unsigned timeout,
			unsigned error,
			struct key *keyring,
			struct key *authkey)
{
	unsigned long prealloc;
	struct timespec now;
	int ret, awaken, link_ret = 0;

	key_check(key);
	key_check(keyring);

	awaken = 0;
	ret = -EBUSY;

	if (keyring)
		link_ret = __key_link_begin(keyring, key->type,
					    key->description, &prealloc);

	mutex_lock(&key_construction_mutex);

	/* can't instantiate twice */
	if (!test_bit(KEY_FLAG_INSTANTIATED, &key->flags)) {
		/* mark the key as being negatively instantiated */
		atomic_inc(&key->user->nikeys);
		key->type_data.x[0] = -(long)error;
		smp_wmb();
		set_bit(KEY_FLAG_NEGATIVE, &key->flags);
		set_bit(KEY_FLAG_INSTANTIATED, &key->flags);
		now = current_kernel_time();
		key->expiry = now.tv_sec + timeout;
		key_schedule_gc(key->expiry + key_gc_delay);

		if (test_and_clear_bit(KEY_FLAG_USER_CONSTRUCT, &key->flags))
			awaken = 1;

		ret = 0;

		/* and link it into the destination keyring */
		if (keyring && link_ret == 0)
			__key_link(keyring, key, &prealloc);

		/* disable the authorisation key */
		if (authkey)
			key_revoke(authkey);
	}

	mutex_unlock(&key_construction_mutex);

	if (keyring)
		__key_link_end(keyring, key->type, prealloc);

	/* wake up anyone waiting for a key to be constructed */
	if (awaken)
		wake_up_bit(&key->flags, KEY_FLAG_USER_CONSTRUCT);

	return ret == 0 ? link_ret : ret;
}