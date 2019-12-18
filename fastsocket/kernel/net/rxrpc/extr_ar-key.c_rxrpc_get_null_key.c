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
struct key {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 struct key* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_ALLOC_NOT_IN_QUOTA ; 
 int /*<<< orphan*/  KEY_POS_SEARCH ; 
 struct cred* current_cred () ; 
 struct key* key_alloc (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int key_instantiate_and_link (struct key*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_revoke (struct key*) ; 
 int /*<<< orphan*/  key_type_rxrpc ; 

struct key *rxrpc_get_null_key(const char *keyname)
{
	const struct cred *cred = current_cred();
	struct key *key;
	int ret;

	key = key_alloc(&key_type_rxrpc, keyname, 0, 0, cred,
			KEY_POS_SEARCH, KEY_ALLOC_NOT_IN_QUOTA);
	if (IS_ERR(key))
		return key;

	ret = key_instantiate_and_link(key, NULL, 0, NULL, NULL);
	if (ret < 0) {
		key_revoke(key);
		key_put(key);
		return ERR_PTR(ret);
	}

	return key;
}