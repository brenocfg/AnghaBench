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
struct btrfs_space_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  bytes_readonly; } ;
struct btrfs_root {int dummy; } ;
struct TYPE_2__ {scalar_t__ offset; } ;
struct btrfs_block_group_cache {int /*<<< orphan*/  lock; scalar_t__ ro; int /*<<< orphan*/  item; scalar_t__ bytes_super; scalar_t__ pinned; scalar_t__ reserved; TYPE_1__ key; struct btrfs_space_info* space_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ btrfs_block_group_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void btrfs_set_block_group_rw(struct btrfs_root *root,
			      struct btrfs_block_group_cache *cache)
{
	struct btrfs_space_info *sinfo = cache->space_info;
	u64 num_bytes;

	BUG_ON(!cache->ro);

	spin_lock(&sinfo->lock);
	spin_lock(&cache->lock);
	num_bytes = cache->key.offset - cache->reserved - cache->pinned -
		    cache->bytes_super - btrfs_block_group_used(&cache->item);
	sinfo->bytes_readonly -= num_bytes;
	cache->ro = 0;
	spin_unlock(&cache->lock);
	spin_unlock(&sinfo->lock);
}