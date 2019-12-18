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
typedef  scalar_t__ u64 ;
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {scalar_t__ cached; TYPE_1__ root_key; int /*<<< orphan*/  cache_lock; int /*<<< orphan*/  fs_info; struct btrfs_free_space_ctl* free_ino_ctl; } ;
struct btrfs_free_space_ctl {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_CACHE_FINISHED ; 
 scalar_t__ BTRFS_CACHE_NO ; 
 scalar_t__ BTRFS_CACHE_STARTED ; 
 scalar_t__ BTRFS_LAST_FREE_OBJECTID ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INODE_MAP_CACHE ; 
 int /*<<< orphan*/  IS_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  __btrfs_add_free_space (struct btrfs_free_space_ctl*,scalar_t__,scalar_t__) ; 
 int btrfs_find_free_objectid (struct btrfs_root*,scalar_t__*) ; 
 int /*<<< orphan*/  btrfs_test_opt (struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caching_kthread ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct btrfs_root*,char*,int /*<<< orphan*/ ) ; 
 int load_free_ino_cache (int /*<<< orphan*/ ,struct btrfs_root*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void start_caching(struct btrfs_root *root)
{
	struct btrfs_free_space_ctl *ctl = root->free_ino_ctl;
	struct task_struct *tsk;
	int ret;
	u64 objectid;

	if (!btrfs_test_opt(root, INODE_MAP_CACHE))
		return;

	spin_lock(&root->cache_lock);
	if (root->cached != BTRFS_CACHE_NO) {
		spin_unlock(&root->cache_lock);
		return;
	}

	root->cached = BTRFS_CACHE_STARTED;
	spin_unlock(&root->cache_lock);

	ret = load_free_ino_cache(root->fs_info, root);
	if (ret == 1) {
		spin_lock(&root->cache_lock);
		root->cached = BTRFS_CACHE_FINISHED;
		spin_unlock(&root->cache_lock);
		return;
	}

	/*
	 * It can be quite time-consuming to fill the cache by searching
	 * through the extent tree, and this can keep ino allocation path
	 * waiting. Therefore at start we quickly find out the highest
	 * inode number and we know we can use inode numbers which fall in
	 * [highest_ino + 1, BTRFS_LAST_FREE_OBJECTID].
	 */
	ret = btrfs_find_free_objectid(root, &objectid);
	if (!ret && objectid <= BTRFS_LAST_FREE_OBJECTID) {
		__btrfs_add_free_space(ctl, objectid,
				       BTRFS_LAST_FREE_OBJECTID - objectid + 1);
	}

	tsk = kthread_run(caching_kthread, root, "btrfs-ino-cache-%llu\n",
			  root->root_key.objectid);
	BUG_ON(IS_ERR(tsk)); /* -ENOMEM */
}