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
struct btrfs_caching_control {int /*<<< orphan*/  count; } ;
struct btrfs_block_group_cache {scalar_t__ cached; int /*<<< orphan*/  lock; struct btrfs_caching_control* caching_ctl; } ;

/* Variables and functions */
 scalar_t__ BTRFS_CACHE_STARTED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct btrfs_caching_control *
get_caching_control(struct btrfs_block_group_cache *cache)
{
	struct btrfs_caching_control *ctl;

	spin_lock(&cache->lock);
	if (cache->cached != BTRFS_CACHE_STARTED) {
		spin_unlock(&cache->lock);
		return NULL;
	}

	/* We're loading it the fast way, so we don't have a caching_ctl. */
	if (!cache->caching_ctl) {
		spin_unlock(&cache->lock);
		return NULL;
	}

	ctl = cache->caching_ctl;
	atomic_inc(&ctl->count);
	spin_unlock(&cache->lock);
	return ctl;
}