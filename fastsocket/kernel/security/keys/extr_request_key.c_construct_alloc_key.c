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
struct key_user {int /*<<< orphan*/  cons_lock; } ;
struct key_type {int /*<<< orphan*/  match; int /*<<< orphan*/  name; } ;
struct key {int /*<<< orphan*/  flags; } ;
struct cred {int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; } ;
typedef  struct key* key_ref_t ;

/* Variables and functions */
 int EINPROGRESS ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_FLAG_USER_CONSTRUCT ; 
 int /*<<< orphan*/  KEY_POS_ALL ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  __key_link (struct key*,struct key*,unsigned long*) ; 
 int __key_link_begin (struct key*,struct key_type*,char const*,unsigned long*) ; 
 int __key_link_check_live_key (struct key*,struct key*) ; 
 int /*<<< orphan*/  __key_link_end (struct key*,struct key_type*,unsigned long) ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ,char const*) ; 
 struct key* key_alloc (struct key_type*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  key_construction_mutex ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 struct key* key_ref_to_ptr (struct key*) ; 
 int key_serial (struct key*) ; 
 int /*<<< orphan*/  kleave (char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct key* search_process_keyrings (struct key_type*,char const*,int /*<<< orphan*/ ,struct cred const*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int construct_alloc_key(struct key_type *type,
			       const char *description,
			       struct key *dest_keyring,
			       unsigned long flags,
			       struct key_user *user,
			       struct key **_key)
{
	const struct cred *cred = current_cred();
	unsigned long prealloc;
	struct key *key;
	key_ref_t key_ref;
	int ret;

	kenter("%s,%s,,,", type->name, description);

	*_key = NULL;
	mutex_lock(&user->cons_lock);

	key = key_alloc(type, description, cred->fsuid, cred->fsgid, cred,
			KEY_POS_ALL, flags);
	if (IS_ERR(key))
		goto alloc_failed;

	set_bit(KEY_FLAG_USER_CONSTRUCT, &key->flags);

	if (dest_keyring) {
		ret = __key_link_begin(dest_keyring, type, description,
				       &prealloc);
		if (ret < 0)
			goto link_prealloc_failed;
	}

	/* attach the key to the destination keyring under lock, but we do need
	 * to do another check just in case someone beat us to it whilst we
	 * waited for locks */
	mutex_lock(&key_construction_mutex);

	key_ref = search_process_keyrings(type, description, type->match, cred);
	if (!IS_ERR(key_ref))
		goto key_already_present;

	if (dest_keyring)
		__key_link(dest_keyring, key, &prealloc);

	mutex_unlock(&key_construction_mutex);
	if (dest_keyring)
		__key_link_end(dest_keyring, type, prealloc);
	mutex_unlock(&user->cons_lock);
	*_key = key;
	kleave(" = 0 [%d]", key_serial(key));
	return 0;

key_already_present:
	key_put(key);
	mutex_unlock(&key_construction_mutex);
	key = key_ref_to_ptr(key_ref);
	if (dest_keyring) {
		ret = __key_link_check_live_key(dest_keyring, key);
		if (ret == 0)
			__key_link(dest_keyring, key, &prealloc);
		__key_link_end(dest_keyring, type, prealloc);
		if (ret < 0)
			goto link_check_failed;
	}
	mutex_unlock(&user->cons_lock);
	*_key = key;
	kleave(" = -EINPROGRESS [%d]", key_serial(key));
	return -EINPROGRESS;

link_check_failed:
	mutex_unlock(&user->cons_lock);
	key_put(key);
	kleave(" = %d [linkcheck]", ret);
	return ret;

link_prealloc_failed:
	mutex_unlock(&user->cons_lock);
	kleave(" = %d [prelink]", ret);
	return ret;

alloc_failed:
	mutex_unlock(&user->cons_lock);
	kleave(" = %ld", PTR_ERR(key));
	return PTR_ERR(key);
}