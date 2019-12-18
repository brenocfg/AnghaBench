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
struct key_type {scalar_t__ update; scalar_t__ read; struct key_type* type; int /*<<< orphan*/  instantiate; int /*<<< orphan*/  match; } ;
struct key {scalar_t__ update; scalar_t__ read; struct key* type; int /*<<< orphan*/  instantiate; int /*<<< orphan*/  match; } ;
struct cred {int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; } ;
typedef  struct key_type* key_ref_t ;
typedef  int key_perm_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOTDIR ; 
 struct key_type* ERR_CAST (struct key_type*) ; 
 struct key_type* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct key_type*) ; 
 int KEY_PERM_UNDEF ; 
 int KEY_POS_LINK ; 
 int KEY_POS_READ ; 
 int KEY_POS_SEARCH ; 
 int KEY_POS_SETATTR ; 
 int KEY_POS_VIEW ; 
 int KEY_USR_LINK ; 
 int KEY_USR_READ ; 
 int KEY_USR_SEARCH ; 
 int KEY_USR_SETATTR ; 
 int KEY_USR_VIEW ; 
 int KEY_USR_WRITE ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int __key_instantiate_and_link (struct key_type*,void const*,size_t,struct key_type*,int /*<<< orphan*/ *,unsigned long*) ; 
 int __key_link_begin (struct key_type*,struct key_type*,char const*,unsigned long*) ; 
 int /*<<< orphan*/  __key_link_end (struct key_type*,struct key_type*,unsigned long) ; 
 struct key_type* __key_update (struct key_type*,void const*,size_t) ; 
 struct key_type* __keyring_search_one (struct key_type*,struct key_type*,char const*,int /*<<< orphan*/ ) ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  is_key_possessed (struct key_type*) ; 
 struct key_type* key_alloc (struct key_type*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*,int,unsigned long) ; 
 int /*<<< orphan*/  key_check (struct key_type*) ; 
 int key_permission (struct key_type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_put (struct key_type*) ; 
 struct key_type* key_ref_to_ptr (struct key_type*) ; 
 struct key_type key_type_keyring ; 
 struct key_type* key_type_lookup (char const*) ; 
 int /*<<< orphan*/  key_type_put (struct key_type*) ; 
 struct key_type* make_key_ref (struct key_type*,int /*<<< orphan*/ ) ; 

key_ref_t key_create_or_update(key_ref_t keyring_ref,
			       const char *type,
			       const char *description,
			       const void *payload,
			       size_t plen,
			       key_perm_t perm,
			       unsigned long flags)
{
	unsigned long prealloc;
	const struct cred *cred = current_cred();
	struct key_type *ktype;
	struct key *keyring, *key = NULL;
	key_ref_t key_ref;
	int ret;

	/* look up the key type to see if it's one of the registered kernel
	 * types */
	ktype = key_type_lookup(type);
	if (IS_ERR(ktype)) {
		key_ref = ERR_PTR(-ENODEV);
		goto error;
	}

	key_ref = ERR_PTR(-EINVAL);
	if (!ktype->match || !ktype->instantiate)
		goto error_2;

	keyring = key_ref_to_ptr(keyring_ref);

	key_check(keyring);

	key_ref = ERR_PTR(-ENOTDIR);
	if (keyring->type != &key_type_keyring)
		goto error_2;

	ret = __key_link_begin(keyring, ktype, description, &prealloc);
	if (ret < 0)
		goto error_2;

	/* if we're going to allocate a new key, we're going to have
	 * to modify the keyring */
	ret = key_permission(keyring_ref, KEY_WRITE);
	if (ret < 0) {
		key_ref = ERR_PTR(ret);
		goto error_3;
	}

	/* if it's possible to update this type of key, search for an existing
	 * key of the same type and description in the destination keyring and
	 * update that instead if possible
	 */
	if (ktype->update) {
		key_ref = __keyring_search_one(keyring_ref, ktype, description,
					       0);
		if (!IS_ERR(key_ref))
			goto found_matching_key;
	}

	/* if the client doesn't provide, decide on the permissions we want */
	if (perm == KEY_PERM_UNDEF) {
		perm = KEY_POS_VIEW | KEY_POS_SEARCH | KEY_POS_LINK | KEY_POS_SETATTR;
		perm |= KEY_USR_VIEW | KEY_USR_SEARCH | KEY_USR_LINK | KEY_USR_SETATTR;

		if (ktype->read)
			perm |= KEY_POS_READ | KEY_USR_READ;

		if (ktype == &key_type_keyring || ktype->update)
			perm |= KEY_USR_WRITE;
	}

	/* allocate a new key */
	key = key_alloc(ktype, description, cred->fsuid, cred->fsgid, cred,
			perm, flags);
	if (IS_ERR(key)) {
		key_ref = ERR_CAST(key);
		goto error_3;
	}

	/* instantiate it and link it into the target keyring */
	ret = __key_instantiate_and_link(key, payload, plen, keyring, NULL,
					 &prealloc);
	if (ret < 0) {
		key_put(key);
		key_ref = ERR_PTR(ret);
		goto error_3;
	}

	key_ref = make_key_ref(key, is_key_possessed(keyring_ref));

 error_3:
	__key_link_end(keyring, ktype, prealloc);
 error_2:
	key_type_put(ktype);
 error:
	return key_ref;

 found_matching_key:
	/* we found a matching key, so we're going to try to update it
	 * - we can drop the locks first as we have the key pinned
	 */
	__key_link_end(keyring, ktype, prealloc);
	key_type_put(ktype);

	key_ref = __key_update(key_ref, payload, plen);
	goto error;
}