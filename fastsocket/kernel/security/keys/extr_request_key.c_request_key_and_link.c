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
struct key_type {int /*<<< orphan*/  match; int /*<<< orphan*/  name; } ;
struct key {int dummy; } ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  key_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOKEY ; 
 struct key* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct key* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  construct_get_dest_keyring (struct key**) ; 
 struct key* construct_key_and_link (struct key_type*,char const*,void const*,size_t,void*,struct key*,unsigned long) ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ,char const*,void const*,size_t,void*,struct key*,unsigned long) ; 
 int /*<<< orphan*/  key_link (struct key*,struct key*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 struct key* key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kleave (char*,struct key*) ; 
 int /*<<< orphan*/  search_process_keyrings (struct key_type*,char const*,int /*<<< orphan*/ ,struct cred const*) ; 

struct key *request_key_and_link(struct key_type *type,
				 const char *description,
				 const void *callout_info,
				 size_t callout_len,
				 void *aux,
				 struct key *dest_keyring,
				 unsigned long flags)
{
	const struct cred *cred = current_cred();
	struct key *key;
	key_ref_t key_ref;

	kenter("%s,%s,%p,%zu,%p,%p,%lx",
	       type->name, description, callout_info, callout_len, aux,
	       dest_keyring, flags);

	/* search all the process keyrings for a key */
	key_ref = search_process_keyrings(type, description, type->match, cred);

	if (!IS_ERR(key_ref)) {
		key = key_ref_to_ptr(key_ref);
		if (dest_keyring) {
			construct_get_dest_keyring(&dest_keyring);
			key_link(dest_keyring, key);
			key_put(dest_keyring);
		}
	} else if (PTR_ERR(key_ref) != -EAGAIN) {
		key = ERR_CAST(key_ref);
	} else  {
		/* the search failed, but the keyrings were searchable, so we
		 * should consult userspace if we can */
		key = ERR_PTR(-ENOKEY);
		if (!callout_info)
			goto error;

		key = construct_key_and_link(type, description, callout_info,
					     callout_len, aux, dest_keyring,
					     flags);
	}

error:
	kleave(" = %p", key);
	return key;
}