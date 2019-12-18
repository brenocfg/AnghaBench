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
typedef  unsigned long u64 ;
struct writeback_control {scalar_t__ sync_mode; scalar_t__ for_kupdate; } ;
struct extent_io_tree {int dummy; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct address_space {int /*<<< orphan*/  host; } ;
struct TYPE_4__ {struct btrfs_root* root; struct extent_io_tree io_tree; } ;
struct TYPE_3__ {unsigned long dirty_metadata_bytes; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (int /*<<< orphan*/ ) ; 
 scalar_t__ WB_SYNC_NONE ; 
 int btree_write_cache_pages (struct address_space*,struct writeback_control*) ; 

__attribute__((used)) static int btree_writepages(struct address_space *mapping,
			    struct writeback_control *wbc)
{
	struct extent_io_tree *tree;
	tree = &BTRFS_I(mapping->host)->io_tree;
	if (wbc->sync_mode == WB_SYNC_NONE) {
		struct btrfs_root *root = BTRFS_I(mapping->host)->root;
		u64 num_dirty;
		unsigned long thresh = 32 * 1024 * 1024;

		if (wbc->for_kupdate)
			return 0;

		/* this is a bit racy, but that's ok */
		num_dirty = root->fs_info->dirty_metadata_bytes;
		if (num_dirty < thresh)
			return 0;
	}
	return btree_write_cache_pages(mapping, wbc);
}