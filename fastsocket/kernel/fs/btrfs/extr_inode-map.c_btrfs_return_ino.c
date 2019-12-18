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
struct btrfs_root {scalar_t__ cached; scalar_t__ cache_progress; scalar_t__ highest_objectid; int /*<<< orphan*/  fs_commit_mutex; int /*<<< orphan*/  cache_lock; struct btrfs_free_space_ctl* free_ino_pinned; struct btrfs_free_space_ctl* free_ino_ctl; } ;
struct btrfs_free_space_ctl {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_CACHE_FINISHED ; 
 int /*<<< orphan*/  INODE_MAP_CACHE ; 
 int /*<<< orphan*/  __btrfs_add_free_space (struct btrfs_free_space_ctl*,scalar_t__,int) ; 
 int /*<<< orphan*/  btrfs_test_opt (struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_caching (struct btrfs_root*) ; 

void btrfs_return_ino(struct btrfs_root *root, u64 objectid)
{
	struct btrfs_free_space_ctl *ctl = root->free_ino_ctl;
	struct btrfs_free_space_ctl *pinned = root->free_ino_pinned;

	if (!btrfs_test_opt(root, INODE_MAP_CACHE))
		return;

again:
	if (root->cached == BTRFS_CACHE_FINISHED) {
		__btrfs_add_free_space(ctl, objectid, 1);
	} else {
		/*
		 * If we are in the process of caching free ino chunks,
		 * to avoid adding the same inode number to the free_ino
		 * tree twice due to cross transaction, we'll leave it
		 * in the pinned tree until a transaction is committed
		 * or the caching work is done.
		 */

		mutex_lock(&root->fs_commit_mutex);
		spin_lock(&root->cache_lock);
		if (root->cached == BTRFS_CACHE_FINISHED) {
			spin_unlock(&root->cache_lock);
			mutex_unlock(&root->fs_commit_mutex);
			goto again;
		}
		spin_unlock(&root->cache_lock);

		start_caching(root);

		if (objectid <= root->cache_progress ||
		    objectid > root->highest_objectid)
			__btrfs_add_free_space(ctl, objectid, 1);
		else
			__btrfs_add_free_space(pinned, objectid, 1);

		mutex_unlock(&root->fs_commit_mutex);
	}
}