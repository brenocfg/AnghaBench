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
struct key {int /*<<< orphan*/  flags; } ;
struct cred {int dummy; } ;
typedef  scalar_t__ key_serial_t ;
typedef  int /*<<< orphan*/  key_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EKEYREVOKED ; 
 int /*<<< orphan*/  ENOKEY ; 
 struct key* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct key* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_FLAG_REVOKED ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  key_get_instantiation_authkey_match ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 struct key* key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_type_request_key_auth ; 
 int /*<<< orphan*/  search_process_keyrings (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,struct cred const*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct key *key_get_instantiation_authkey(key_serial_t target_id)
{
	const struct cred *cred = current_cred();
	struct key *authkey;
	key_ref_t authkey_ref;

	authkey_ref = search_process_keyrings(
		&key_type_request_key_auth,
		(void *) (unsigned long) target_id,
		key_get_instantiation_authkey_match,
		cred);

	if (IS_ERR(authkey_ref)) {
		authkey = ERR_CAST(authkey_ref);
		if (authkey == ERR_PTR(-EAGAIN))
			authkey = ERR_PTR(-ENOKEY);
		goto error;
	}

	authkey = key_ref_to_ptr(authkey_ref);
	if (test_bit(KEY_FLAG_REVOKED, &authkey->flags)) {
		key_put(authkey);
		authkey = ERR_PTR(-EKEYREVOKED);
	}

error:
	return authkey;
}