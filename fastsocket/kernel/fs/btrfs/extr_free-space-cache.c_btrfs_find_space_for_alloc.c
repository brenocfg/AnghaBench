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
struct btrfs_free_space_ctl {int /*<<< orphan*/  tree_lock; } ;
struct btrfs_free_space {scalar_t__ bytes; scalar_t__ offset; scalar_t__ bitmap; } ;
struct btrfs_block_group_cache {struct btrfs_free_space_ctl* free_space_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_clear_bits (struct btrfs_free_space_ctl*,struct btrfs_free_space*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_free_space_cachep ; 
 struct btrfs_free_space* find_free_space (struct btrfs_free_space_ctl*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  free_bitmap (struct btrfs_free_space_ctl*,struct btrfs_free_space*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct btrfs_free_space*) ; 
 int /*<<< orphan*/  link_free_space (struct btrfs_free_space_ctl*,struct btrfs_free_space*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink_free_space (struct btrfs_free_space_ctl*,struct btrfs_free_space*) ; 

u64 btrfs_find_space_for_alloc(struct btrfs_block_group_cache *block_group,
			       u64 offset, u64 bytes, u64 empty_size)
{
	struct btrfs_free_space_ctl *ctl = block_group->free_space_ctl;
	struct btrfs_free_space *entry = NULL;
	u64 bytes_search = bytes + empty_size;
	u64 ret = 0;

	spin_lock(&ctl->tree_lock);
	entry = find_free_space(ctl, &offset, &bytes_search);
	if (!entry)
		goto out;

	ret = offset;
	if (entry->bitmap) {
		bitmap_clear_bits(ctl, entry, offset, bytes);
		if (!entry->bytes)
			free_bitmap(ctl, entry);
	} else {
		unlink_free_space(ctl, entry);
		entry->offset += bytes;
		entry->bytes -= bytes;
		if (!entry->bytes)
			kmem_cache_free(btrfs_free_space_cachep, entry);
		else
			link_free_space(ctl, entry);
	}

out:
	spin_unlock(&ctl->tree_lock);

	return ret;
}