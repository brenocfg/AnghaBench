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
typedef  scalar_t__ u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_fs_info {int mount_opt; int /*<<< orphan*/  caching_workers; int /*<<< orphan*/  extent_commit_sem; int /*<<< orphan*/  caching_block_groups; int /*<<< orphan*/  extent_root; } ;
struct TYPE_4__ {int /*<<< orphan*/  func; } ;
struct btrfs_caching_control {TYPE_2__ work; int /*<<< orphan*/  list; int /*<<< orphan*/  count; int /*<<< orphan*/  wait; int /*<<< orphan*/  progress; struct btrfs_block_group_cache* block_group; int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_block_group_cache {scalar_t__ cached; int /*<<< orphan*/  lock; struct btrfs_caching_control* caching_ctl; scalar_t__ last_byte_to_unpin; TYPE_1__ key; struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 scalar_t__ BTRFS_CACHE_FAST ; 
 scalar_t__ BTRFS_CACHE_FINISHED ; 
 scalar_t__ BTRFS_CACHE_NO ; 
 void* BTRFS_CACHE_STARTED ; 
 int BTRFS_MOUNT_SPACE_CACHE ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  WARN_ON (struct btrfs_caching_control*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  btrfs_get_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_queue_worker (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  caching_thread ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_excluded_extents (int /*<<< orphan*/ ,struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct btrfs_caching_control*) ; 
 struct btrfs_caching_control* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int load_free_space_cache (struct btrfs_fs_info*,struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_caching_control (struct btrfs_caching_control*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cache_block_group(struct btrfs_block_group_cache *cache,
			     struct btrfs_trans_handle *trans,
			     struct btrfs_root *root,
			     int load_cache_only)
{
	DEFINE_WAIT(wait);
	struct btrfs_fs_info *fs_info = cache->fs_info;
	struct btrfs_caching_control *caching_ctl;
	int ret = 0;

	caching_ctl = kzalloc(sizeof(*caching_ctl), GFP_NOFS);
	if (!caching_ctl)
		return -ENOMEM;

	INIT_LIST_HEAD(&caching_ctl->list);
	mutex_init(&caching_ctl->mutex);
	init_waitqueue_head(&caching_ctl->wait);
	caching_ctl->block_group = cache;
	caching_ctl->progress = cache->key.objectid;
	atomic_set(&caching_ctl->count, 1);
	caching_ctl->work.func = caching_thread;

	spin_lock(&cache->lock);
	/*
	 * This should be a rare occasion, but this could happen I think in the
	 * case where one thread starts to load the space cache info, and then
	 * some other thread starts a transaction commit which tries to do an
	 * allocation while the other thread is still loading the space cache
	 * info.  The previous loop should have kept us from choosing this block
	 * group, but if we've moved to the state where we will wait on caching
	 * block groups we need to first check if we're doing a fast load here,
	 * so we can wait for it to finish, otherwise we could end up allocating
	 * from a block group who's cache gets evicted for one reason or
	 * another.
	 */
	while (cache->cached == BTRFS_CACHE_FAST) {
		struct btrfs_caching_control *ctl;

		ctl = cache->caching_ctl;
		atomic_inc(&ctl->count);
		prepare_to_wait(&ctl->wait, &wait, TASK_UNINTERRUPTIBLE);
		spin_unlock(&cache->lock);

		schedule();

		finish_wait(&ctl->wait, &wait);
		put_caching_control(ctl);
		spin_lock(&cache->lock);
	}

	if (cache->cached != BTRFS_CACHE_NO) {
		spin_unlock(&cache->lock);
		kfree(caching_ctl);
		return 0;
	}
	WARN_ON(cache->caching_ctl);
	cache->caching_ctl = caching_ctl;
	cache->cached = BTRFS_CACHE_FAST;
	spin_unlock(&cache->lock);

	/*
	 * We can't do the read from on-disk cache during a commit since we need
	 * to have the normal tree locking.  Also if we are currently trying to
	 * allocate blocks for the tree root we can't do the fast caching since
	 * we likely hold important locks.
	 */
	if (fs_info->mount_opt & BTRFS_MOUNT_SPACE_CACHE) {
		ret = load_free_space_cache(fs_info, cache);

		spin_lock(&cache->lock);
		if (ret == 1) {
			cache->caching_ctl = NULL;
			cache->cached = BTRFS_CACHE_FINISHED;
			cache->last_byte_to_unpin = (u64)-1;
		} else {
			if (load_cache_only) {
				cache->caching_ctl = NULL;
				cache->cached = BTRFS_CACHE_NO;
			} else {
				cache->cached = BTRFS_CACHE_STARTED;
			}
		}
		spin_unlock(&cache->lock);
		wake_up(&caching_ctl->wait);
		if (ret == 1) {
			put_caching_control(caching_ctl);
			free_excluded_extents(fs_info->extent_root, cache);
			return 0;
		}
	} else {
		/*
		 * We are not going to do the fast caching, set cached to the
		 * appropriate value and wakeup any waiters.
		 */
		spin_lock(&cache->lock);
		if (load_cache_only) {
			cache->caching_ctl = NULL;
			cache->cached = BTRFS_CACHE_NO;
		} else {
			cache->cached = BTRFS_CACHE_STARTED;
		}
		spin_unlock(&cache->lock);
		wake_up(&caching_ctl->wait);
	}

	if (load_cache_only) {
		put_caching_control(caching_ctl);
		return 0;
	}

	down_write(&fs_info->extent_commit_sem);
	atomic_inc(&caching_ctl->count);
	list_add_tail(&caching_ctl->list, &fs_info->caching_block_groups);
	up_write(&fs_info->extent_commit_sem);

	btrfs_get_block_group(cache);

	btrfs_queue_worker(&fs_info->caching_workers, &caching_ctl->work);

	return ret;
}