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
typedef  scalar_t__ uid_t ;
struct key_user {int qnkeys; size_t qnbytes; int /*<<< orphan*/  lock; int /*<<< orphan*/  nkeys; } ;
struct key_type {size_t def_datalen; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
struct key {size_t quotalen; size_t datalen; int flags; int /*<<< orphan*/  description; int /*<<< orphan*/  magic; int /*<<< orphan*/  type_data; int /*<<< orphan*/ * security; TYPE_2__ payload; scalar_t__ expiry; int /*<<< orphan*/  perm; int /*<<< orphan*/  gid; scalar_t__ uid; struct key_user* user; struct key_type* type; int /*<<< orphan*/  sem; int /*<<< orphan*/  usage; } ;
struct cred {TYPE_1__* user; } ;
typedef  int /*<<< orphan*/  key_perm_t ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_3__ {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int EDQUOT ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct key* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long KEY_ALLOC_NOT_IN_QUOTA ; 
 unsigned long KEY_ALLOC_QUOTA_OVERRUN ; 
 int /*<<< orphan*/  KEY_DEBUG_MAGIC ; 
 int KEY_FLAG_IN_QUOTA ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_alloc_serial (struct key*) ; 
 int /*<<< orphan*/  key_jar ; 
 unsigned int key_quota_maxbytes ; 
 unsigned int key_quota_maxkeys ; 
 unsigned int key_quota_root_maxbytes ; 
 unsigned int key_quota_root_maxkeys ; 
 struct key_user* key_user_lookup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_user_put (struct key_user*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct key* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct key*) ; 
 int /*<<< orphan*/  kmemdup (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int security_key_alloc (struct key*,struct cred const*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

struct key *key_alloc(struct key_type *type, const char *desc,
		      uid_t uid, gid_t gid, const struct cred *cred,
		      key_perm_t perm, unsigned long flags)
{
	struct key_user *user = NULL;
	struct key *key;
	size_t desclen, quotalen;
	int ret;

	key = ERR_PTR(-EINVAL);
	if (!desc || !*desc)
		goto error;

	desclen = strlen(desc) + 1;
	quotalen = desclen + type->def_datalen;

	/* get hold of the key tracking for this user */
	user = key_user_lookup(uid, cred->user->user_ns);
	if (!user)
		goto no_memory_1;

	/* check that the user's quota permits allocation of another key and
	 * its description */
	if (!(flags & KEY_ALLOC_NOT_IN_QUOTA)) {
		unsigned maxkeys = (uid == 0) ?
			key_quota_root_maxkeys : key_quota_maxkeys;
		unsigned maxbytes = (uid == 0) ?
			key_quota_root_maxbytes : key_quota_maxbytes;

		spin_lock(&user->lock);
		if (!(flags & KEY_ALLOC_QUOTA_OVERRUN)) {
			if (user->qnkeys + 1 >= maxkeys ||
			    user->qnbytes + quotalen >= maxbytes ||
			    user->qnbytes + quotalen < user->qnbytes)
				goto no_quota;
		}

		user->qnkeys++;
		user->qnbytes += quotalen;
		spin_unlock(&user->lock);
	}

	/* allocate and initialise the key and its description */
	key = kmem_cache_alloc(key_jar, GFP_KERNEL);
	if (!key)
		goto no_memory_2;

	if (desc) {
		key->description = kmemdup(desc, desclen, GFP_KERNEL);
		if (!key->description)
			goto no_memory_3;
	}

	atomic_set(&key->usage, 1);
	init_rwsem(&key->sem);
	key->type = type;
	key->user = user;
	key->quotalen = quotalen;
	key->datalen = type->def_datalen;
	key->uid = uid;
	key->gid = gid;
	key->perm = perm;
	key->flags = 0;
	key->expiry = 0;
	key->payload.data = NULL;
	key->security = NULL;

	if (!(flags & KEY_ALLOC_NOT_IN_QUOTA))
		key->flags |= 1 << KEY_FLAG_IN_QUOTA;

	memset(&key->type_data, 0, sizeof(key->type_data));

#ifdef KEY_DEBUGGING
	key->magic = KEY_DEBUG_MAGIC;
#endif

	/* let the security module know about the key */
	ret = security_key_alloc(key, cred, flags);
	if (ret < 0)
		goto security_error;

	/* publish the key by giving it a serial number */
	atomic_inc(&user->nkeys);
	key_alloc_serial(key);

error:
	return key;

security_error:
	kfree(key->description);
	kmem_cache_free(key_jar, key);
	if (!(flags & KEY_ALLOC_NOT_IN_QUOTA)) {
		spin_lock(&user->lock);
		user->qnkeys--;
		user->qnbytes -= quotalen;
		spin_unlock(&user->lock);
	}
	key_user_put(user);
	key = ERR_PTR(ret);
	goto error;

no_memory_3:
	kmem_cache_free(key_jar, key);
no_memory_2:
	if (!(flags & KEY_ALLOC_NOT_IN_QUOTA)) {
		spin_lock(&user->lock);
		user->qnkeys--;
		user->qnbytes -= quotalen;
		spin_unlock(&user->lock);
	}
	key_user_put(user);
no_memory_1:
	key = ERR_PTR(-ENOMEM);
	goto error;

no_quota:
	spin_unlock(&user->lock);
	key_user_put(user);
	key = ERR_PTR(-EDQUOT);
	goto error;
}