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
struct key {scalar_t__ uid; int perm; int gid; TYPE_1__* user; } ;
struct cred {scalar_t__ fsuid; int fsgid; int /*<<< orphan*/  group_info; TYPE_2__* user; } ;
typedef  int /*<<< orphan*/  key_ref_t ;
typedef  int key_perm_t ;
struct TYPE_4__ {scalar_t__ user_ns; } ;
struct TYPE_3__ {scalar_t__ user_ns; } ;

/* Variables and functions */
 int EACCES ; 
 int KEY_ALL ; 
 int KEY_GRP_ALL ; 
 int groups_search (int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_key_possessed (int /*<<< orphan*/  const) ; 
 struct key* key_ref_to_ptr (int /*<<< orphan*/  const) ; 
 int security_key_permission (int /*<<< orphan*/  const,struct cred const*,int) ; 

int key_task_permission(const key_ref_t key_ref, const struct cred *cred,
			key_perm_t perm)
{
	struct key *key;
	key_perm_t kperm;
	int ret;

	key = key_ref_to_ptr(key_ref);

	if (key->user->user_ns != cred->user->user_ns)
		goto use_other_perms;

	/* use the second 8-bits of permissions for keys the caller owns */
	if (key->uid == cred->fsuid) {
		kperm = key->perm >> 16;
		goto use_these_perms;
	}

	/* use the third 8-bits of permissions for keys the caller has a group
	 * membership in common with */
	if (key->gid != -1 && key->perm & KEY_GRP_ALL) {
		if (key->gid == cred->fsgid) {
			kperm = key->perm >> 8;
			goto use_these_perms;
		}

		ret = groups_search(cred->group_info, key->gid);
		if (ret) {
			kperm = key->perm >> 8;
			goto use_these_perms;
		}
	}

use_other_perms:

	/* otherwise use the least-significant 8-bits */
	kperm = key->perm;

use_these_perms:

	/* use the top 8-bits of permissions for keys the caller possesses
	 * - possessor permissions are additive with other permissions
	 */
	if (is_key_possessed(key_ref))
		kperm |= key->perm >> 24;

	kperm = kperm & perm & KEY_ALL;

	if (kperm != perm)
		return -EACCES;

	/* let LSM be the final arbiter */
	return security_key_permission(key_ref, cred, perm);
}