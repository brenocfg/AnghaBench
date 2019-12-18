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
struct key {scalar_t__ uid; int perm; int /*<<< orphan*/  sem; } ;
typedef  int /*<<< orphan*/  key_serial_t ;
typedef  int /*<<< orphan*/  key_ref_t ;
typedef  int key_perm_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 long EACCES ; 
 long EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int KEY_GRP_ALL ; 
 int KEY_LOOKUP_CREATE ; 
 int KEY_LOOKUP_PARTIAL ; 
 int KEY_OTH_ALL ; 
 int KEY_POS_ALL ; 
 int /*<<< orphan*/  KEY_SETATTR ; 
 int KEY_USR_ALL ; 
 long PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 scalar_t__ current_fsuid () ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 struct key* key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_user_key (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

long keyctl_setperm_key(key_serial_t id, key_perm_t perm)
{
	struct key *key;
	key_ref_t key_ref;
	long ret;

	ret = -EINVAL;
	if (perm & ~(KEY_POS_ALL | KEY_USR_ALL | KEY_GRP_ALL | KEY_OTH_ALL))
		goto error;

	key_ref = lookup_user_key(id, KEY_LOOKUP_CREATE | KEY_LOOKUP_PARTIAL,
				  KEY_SETATTR);
	if (IS_ERR(key_ref)) {
		ret = PTR_ERR(key_ref);
		goto error;
	}

	key = key_ref_to_ptr(key_ref);

	/* make the changes with the locks held to prevent chown/chmod races */
	ret = -EACCES;
	down_write(&key->sem);

	/* if we're not the sysadmin, we can only change a key that we own */
	if (capable(CAP_SYS_ADMIN) || key->uid == current_fsuid()) {
		key->perm = perm;
		ret = 0;
	}

	up_write(&key->sem);
	key_put(key);
error:
	return ret;
}