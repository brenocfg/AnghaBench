#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct page {TYPE_2__* mapping; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct btrfs_mapping_tree {int dummy; } ;
struct bio {int bi_size; scalar_t__ bi_sector; } ;
struct TYPE_6__ {struct btrfs_root* root; } ;
struct TYPE_5__ {int /*<<< orphan*/  host; } ;
struct TYPE_4__ {struct btrfs_mapping_tree mapping_tree; } ;

/* Variables and functions */
 TYPE_3__* BTRFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long EXTENT_BIO_COMPRESSED ; 
 int /*<<< orphan*/  READ ; 
 int btrfs_map_block (struct btrfs_mapping_tree*,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int btrfs_merge_bio_hook(struct page *page, unsigned long offset,
			 size_t size, struct bio *bio,
			 unsigned long bio_flags)
{
	struct btrfs_root *root = BTRFS_I(page->mapping->host)->root;
	struct btrfs_mapping_tree *map_tree;
	u64 logical = (u64)bio->bi_sector << 9;
	u64 length = 0;
	u64 map_length;
	int ret;

	if (bio_flags & EXTENT_BIO_COMPRESSED)
		return 0;

	length = bio->bi_size;
	map_tree = &root->fs_info->mapping_tree;
	map_length = length;
	ret = btrfs_map_block(map_tree, READ, logical,
			      &map_length, NULL, 0);
	/* Will always return 0 or 1 with map_multi == NULL */
	BUG_ON(ret < 0);
	if (map_length < length + size)
		return 1;
	return 0;
}