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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_free_space_ctl {int dummy; } ;
struct btrfs_free_space {int dummy; } ;
struct btrfs_free_cluster {int /*<<< orphan*/  window_start; } ;
struct btrfs_block_group_cache {struct btrfs_free_space_ctl* free_space_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bitmap_clear_bits (struct btrfs_free_space_ctl*,struct btrfs_free_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int search_bitmap (struct btrfs_free_space_ctl*,struct btrfs_free_space*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 btrfs_alloc_from_bitmap(struct btrfs_block_group_cache *block_group,
				   struct btrfs_free_cluster *cluster,
				   struct btrfs_free_space *entry,
				   u64 bytes, u64 min_start)
{
	struct btrfs_free_space_ctl *ctl = block_group->free_space_ctl;
	int err;
	u64 search_start = cluster->window_start;
	u64 search_bytes = bytes;
	u64 ret = 0;

	search_start = min_start;
	search_bytes = bytes;

	err = search_bitmap(ctl, entry, &search_start, &search_bytes);
	if (err)
		return 0;

	ret = search_start;
	__bitmap_clear_bits(ctl, entry, ret, bytes);

	return ret;
}