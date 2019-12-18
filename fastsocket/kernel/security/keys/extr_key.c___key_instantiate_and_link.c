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
struct key {int /*<<< orphan*/  flags; TYPE_2__* user; TYPE_1__* type; } ;
struct TYPE_4__ {int /*<<< orphan*/  nikeys; } ;
struct TYPE_3__ {int (* instantiate ) (struct key*,void const*,size_t) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  KEY_FLAG_INSTANTIATED ; 
 int /*<<< orphan*/  KEY_FLAG_USER_CONSTRUCT ; 
 int /*<<< orphan*/  __key_link (struct key*,struct key*,unsigned long*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_check (struct key*) ; 
 int /*<<< orphan*/  key_construction_mutex ; 
 int /*<<< orphan*/  key_revoke (struct key*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct key*,void const*,size_t) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __key_instantiate_and_link(struct key *key,
				      const void *data,
				      size_t datalen,
				      struct key *keyring,
				      struct key *authkey,
				      unsigned long *_prealloc)
{
	int ret, awaken;

	key_check(key);
	key_check(keyring);

	awaken = 0;
	ret = -EBUSY;

	mutex_lock(&key_construction_mutex);

	/* can't instantiate twice */
	if (!test_bit(KEY_FLAG_INSTANTIATED, &key->flags)) {
		/* instantiate the key */
		ret = key->type->instantiate(key, data, datalen);

		if (ret == 0) {
			/* mark the key as being instantiated */
			atomic_inc(&key->user->nikeys);
			set_bit(KEY_FLAG_INSTANTIATED, &key->flags);

			if (test_and_clear_bit(KEY_FLAG_USER_CONSTRUCT, &key->flags))
				awaken = 1;

			/* and link it into the destination keyring */
			if (keyring)
				__key_link(keyring, key, _prealloc);

			/* disable the authorisation key */
			if (authkey)
				key_revoke(authkey);
		}
	}

	mutex_unlock(&key_construction_mutex);

	/* wake up anyone waiting for a key to be constructed */
	if (awaken)
		wake_up_bit(&key->flags, KEY_FLAG_USER_CONSTRUCT);

	return ret;
}