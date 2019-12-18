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
struct key_user {int dummy; } ;
struct key_type {int dummy; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int ENOMEM ; 
 struct key* ERR_PTR (int) ; 
 int construct_alloc_key (struct key_type*,char const*,struct key*,unsigned long,struct key_user*,struct key**) ; 
 int /*<<< orphan*/  construct_get_dest_keyring (struct key**) ; 
 int construct_key (struct key*,char const*,size_t,void*,struct key*) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  kdebug (char*) ; 
 int /*<<< orphan*/  kenter (char*) ; 
 int /*<<< orphan*/  key_negate_and_link (struct key*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_negative_timeout ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int key_serial (struct key*) ; 
 struct key_user* key_user_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_user_put (struct key_user*) ; 
 int /*<<< orphan*/  kleave (char*,int) ; 

__attribute__((used)) static struct key *construct_key_and_link(struct key_type *type,
					  const char *description,
					  const char *callout_info,
					  size_t callout_len,
					  void *aux,
					  struct key *dest_keyring,
					  unsigned long flags)
{
	struct key_user *user;
	struct key *key;
	int ret;

	kenter("");

	user = key_user_lookup(current_fsuid(), current_user_ns());
	if (!user)
		return ERR_PTR(-ENOMEM);

	construct_get_dest_keyring(&dest_keyring);

	ret = construct_alloc_key(type, description, dest_keyring, flags, user,
				  &key);
	key_user_put(user);

	if (ret == 0) {
		ret = construct_key(key, callout_info, callout_len, aux,
				    dest_keyring);
		if (ret < 0) {
			kdebug("cons failed");
			goto construction_failed;
		}
	} else if (ret == -EINPROGRESS) {
		ret = 0;
	} else {
		goto couldnt_alloc_key;
	}

	key_put(dest_keyring);
	kleave(" = key %d", key_serial(key));
	return key;

construction_failed:
	key_negate_and_link(key, key_negative_timeout, NULL, NULL);
	key_put(key);
couldnt_alloc_key:
	key_put(dest_keyring);
	kleave(" = %d", ret);
	return ERR_PTR(ret);
}