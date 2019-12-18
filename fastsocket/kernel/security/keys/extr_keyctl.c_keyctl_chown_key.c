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
typedef  scalar_t__ uid_t ;
struct key_user {int qnkeys; unsigned int qnbytes; int /*<<< orphan*/  lock; int /*<<< orphan*/  nikeys; int /*<<< orphan*/  nkeys; } ;
struct key {scalar_t__ uid; scalar_t__ gid; unsigned int quotalen; int /*<<< orphan*/  sem; struct key_user* user; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  key_serial_t ;
typedef  int /*<<< orphan*/  key_ref_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 long EACCES ; 
 long EDQUOT ; 
 long ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_FLAG_INSTANTIATED ; 
 int /*<<< orphan*/  KEY_FLAG_IN_QUOTA ; 
 int KEY_LOOKUP_CREATE ; 
 int KEY_LOOKUP_PARTIAL ; 
 int /*<<< orphan*/  KEY_SETATTR ; 
 long PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_group_p (scalar_t__) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 unsigned int key_quota_maxbytes ; 
 unsigned int key_quota_maxkeys ; 
 unsigned int key_quota_root_maxbytes ; 
 unsigned int key_quota_root_maxkeys ; 
 struct key* key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 struct key_user* key_user_lookup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_user_put (struct key_user*) ; 
 int /*<<< orphan*/  lookup_user_key (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

long keyctl_chown_key(key_serial_t id, uid_t uid, gid_t gid)
{
	struct key_user *newowner, *zapowner = NULL;
	struct key *key;
	key_ref_t key_ref;
	long ret;

	ret = 0;
	if (uid == (uid_t) -1 && gid == (gid_t) -1)
		goto error;

	key_ref = lookup_user_key(id, KEY_LOOKUP_CREATE | KEY_LOOKUP_PARTIAL,
				  KEY_SETATTR);
	if (IS_ERR(key_ref)) {
		ret = PTR_ERR(key_ref);
		goto error;
	}

	key = key_ref_to_ptr(key_ref);

	/* make the changes with the locks held to prevent chown/chown races */
	ret = -EACCES;
	down_write(&key->sem);

	if (!capable(CAP_SYS_ADMIN)) {
		/* only the sysadmin can chown a key to some other UID */
		if (uid != (uid_t) -1 && key->uid != uid)
			goto error_put;

		/* only the sysadmin can set the key's GID to a group other
		 * than one of those that the current process subscribes to */
		if (gid != (gid_t) -1 && gid != key->gid && !in_group_p(gid))
			goto error_put;
	}

	/* change the UID */
	if (uid != (uid_t) -1 && uid != key->uid) {
		ret = -ENOMEM;
		newowner = key_user_lookup(uid, current_user_ns());
		if (!newowner)
			goto error_put;

		/* transfer the quota burden to the new user */
		if (test_bit(KEY_FLAG_IN_QUOTA, &key->flags)) {
			unsigned maxkeys = (uid == 0) ?
				key_quota_root_maxkeys : key_quota_maxkeys;
			unsigned maxbytes = (uid == 0) ?
				key_quota_root_maxbytes : key_quota_maxbytes;

			spin_lock(&newowner->lock);
			if (newowner->qnkeys + 1 >= maxkeys ||
			    newowner->qnbytes + key->quotalen >= maxbytes ||
			    newowner->qnbytes + key->quotalen <
			    newowner->qnbytes)
				goto quota_overrun;

			newowner->qnkeys++;
			newowner->qnbytes += key->quotalen;
			spin_unlock(&newowner->lock);

			spin_lock(&key->user->lock);
			key->user->qnkeys--;
			key->user->qnbytes -= key->quotalen;
			spin_unlock(&key->user->lock);
		}

		atomic_dec(&key->user->nkeys);
		atomic_inc(&newowner->nkeys);

		if (test_bit(KEY_FLAG_INSTANTIATED, &key->flags)) {
			atomic_dec(&key->user->nikeys);
			atomic_inc(&newowner->nikeys);
		}

		zapowner = key->user;
		key->user = newowner;
		key->uid = uid;
	}

	/* change the GID */
	if (gid != (gid_t) -1)
		key->gid = gid;

	ret = 0;

error_put:
	up_write(&key->sem);
	key_put(key);
	if (zapowner)
		key_user_put(zapowner);
error:
	return ret;

quota_overrun:
	spin_unlock(&newowner->lock);
	zapowner = newowner;
	ret = -EDQUOT;
	goto error_put;
}