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
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct user_key_payload {int perm; size_t datalen; int /*<<< orphan*/  data; TYPE_1__ payload; } ;
struct key {int perm; size_t datalen; int /*<<< orphan*/  data; TYPE_1__ payload; } ;
struct cred {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ IS_ERR (struct user_key_payload*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct user_key_payload*) ; 
 int KEY_USR_VIEW ; 
 int KEY_USR_WRITE ; 
 size_t PTR_ERR (struct user_key_payload*) ; 
 int /*<<< orphan*/  id_resolver_cache ; 
 int /*<<< orphan*/  key_put (struct user_key_payload*) ; 
 int /*<<< orphan*/  key_type_id_resolver ; 
 size_t key_validate (struct user_key_payload*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 size_t nfs_idmap_get_desc (char const*,size_t,char const*,int /*<<< orphan*/ ,char**) ; 
 struct cred* override_creds (int /*<<< orphan*/ ) ; 
 struct user_key_payload* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct user_key_payload* request_key (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static ssize_t nfs_idmap_request_key(const char *name, size_t namelen,
		const char *type, void *data, size_t data_size)
{
	const struct cred *saved_cred;
	struct key *rkey;
	char *desc;
	struct user_key_payload *payload;
	ssize_t ret;

	ret = nfs_idmap_get_desc(name, namelen, type, strlen(type), &desc);
	if (ret <= 0)
		goto out;

	saved_cred = override_creds(id_resolver_cache);
	rkey = request_key(&key_type_id_resolver, desc, "");
	revert_creds(saved_cred);
	kfree(desc);
	if (IS_ERR(rkey)) {
		ret = PTR_ERR(rkey);
		goto out;
	}

	rcu_read_lock();
	rkey->perm |= KEY_USR_VIEW|KEY_USR_WRITE;

	ret = key_validate(rkey);
	if (ret < 0)
		goto out_up;

	payload = rcu_dereference(rkey->payload.data);
	if (IS_ERR_OR_NULL(payload)) {
		ret = PTR_ERR(payload);
		goto out_up;
	}

	ret = payload->datalen;
	if (ret > 0 && ret <= data_size)
		memcpy(data, payload->data, ret);
	else
		ret = -EINVAL;

out_up:
	rcu_read_unlock();
	key_put(rkey);
out:
	return ret;
}