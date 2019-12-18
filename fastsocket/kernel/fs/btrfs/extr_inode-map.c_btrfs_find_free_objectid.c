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
typedef  scalar_t__ u64 ;
struct btrfs_root {scalar_t__ highest_objectid; int /*<<< orphan*/  objectid_mutex; } ;

/* Variables and functions */
 scalar_t__ BTRFS_FIRST_FREE_OBJECTID ; 
 scalar_t__ BTRFS_LAST_FREE_OBJECTID ; 
 int ENOSPC ; 
 int btrfs_find_highest_objectid (struct btrfs_root*,scalar_t__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int btrfs_find_free_objectid(struct btrfs_root *root, u64 *objectid)
{
	int ret;
	mutex_lock(&root->objectid_mutex);

	if (unlikely(root->highest_objectid < BTRFS_FIRST_FREE_OBJECTID)) {
		ret = btrfs_find_highest_objectid(root,
						  &root->highest_objectid);
		if (ret)
			goto out;
	}

	if (unlikely(root->highest_objectid >= BTRFS_LAST_FREE_OBJECTID)) {
		ret = -ENOSPC;
		goto out;
	}

	*objectid = ++root->highest_objectid;
	ret = 0;
out:
	mutex_unlock(&root->objectid_mutex);
	return ret;
}