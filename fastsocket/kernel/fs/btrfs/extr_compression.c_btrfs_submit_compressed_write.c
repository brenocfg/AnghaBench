#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
struct page {int /*<<< orphan*/ * mapping; } ;
struct inode {int /*<<< orphan*/ * i_mapping; } ;
struct extent_io_tree {TYPE_2__* ops; } ;
struct compressed_bio {unsigned long start; unsigned long len; unsigned long compressed_len; unsigned long nr_pages; int /*<<< orphan*/  pending_bios; int /*<<< orphan*/ * orig_bio; struct page** compressed_pages; scalar_t__ mirror_num; struct inode* inode; scalar_t__ errors; } ;
struct btrfs_root {TYPE_3__* fs_info; } ;
struct block_device {int dummy; } ;
struct bio {void* bi_end_io; struct compressed_bio* bi_private; scalar_t__ bi_size; } ;
struct TYPE_8__ {int flags; struct btrfs_root* root; struct extent_io_tree io_tree; } ;
struct TYPE_7__ {TYPE_1__* fs_devices; } ;
struct TYPE_6__ {int (* merge_bio_hook ) (struct page*,int /*<<< orphan*/ ,unsigned long,struct bio*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {struct block_device* latest_bdev; } ;

/* Variables and functions */
 TYPE_4__* BTRFS_I (struct inode*) ; 
 int BTRFS_INODE_NODATASUM ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 unsigned long PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (unsigned long) ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long bio_add_page (struct bio*,struct page*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_get (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int btrfs_bio_wq_end_io (TYPE_3__*,struct bio*,int /*<<< orphan*/ ) ; 
 int btrfs_csum_one_bio (struct btrfs_root*,struct inode*,struct bio*,unsigned long,int) ; 
 int btrfs_map_bio (struct btrfs_root*,int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ,int) ; 
 struct bio* compressed_bio_alloc (struct block_device*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compressed_bio_size (struct btrfs_root*,unsigned long) ; 
 int /*<<< orphan*/  cond_resched () ; 
 void* end_compressed_bio_write ; 
 int /*<<< orphan*/  kfree (struct compressed_bio*) ; 
 struct compressed_bio* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,unsigned long,unsigned long,int) ; 
 int stub1 (struct page*,int /*<<< orphan*/ ,unsigned long,struct bio*,int /*<<< orphan*/ ) ; 

int btrfs_submit_compressed_write(struct inode *inode, u64 start,
				 unsigned long len, u64 disk_start,
				 unsigned long compressed_len,
				 struct page **compressed_pages,
				 unsigned long nr_pages)
{
	struct bio *bio = NULL;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct compressed_bio *cb;
	unsigned long bytes_left;
	struct extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	int pg_index = 0;
	struct page *page;
	u64 first_byte = disk_start;
	struct block_device *bdev;
	int ret;
	int skip_sum = BTRFS_I(inode)->flags & BTRFS_INODE_NODATASUM;

	WARN_ON(start & ((u64)PAGE_CACHE_SIZE - 1));
	cb = kmalloc(compressed_bio_size(root, compressed_len), GFP_NOFS);
	if (!cb)
		return -ENOMEM;
	atomic_set(&cb->pending_bios, 0);
	cb->errors = 0;
	cb->inode = inode;
	cb->start = start;
	cb->len = len;
	cb->mirror_num = 0;
	cb->compressed_pages = compressed_pages;
	cb->compressed_len = compressed_len;
	cb->orig_bio = NULL;
	cb->nr_pages = nr_pages;

	bdev = BTRFS_I(inode)->root->fs_info->fs_devices->latest_bdev;

	bio = compressed_bio_alloc(bdev, first_byte, GFP_NOFS);
	if(!bio) {
		kfree(cb);
		return -ENOMEM;
	}
	bio->bi_private = cb;
	bio->bi_end_io = end_compressed_bio_write;
	atomic_inc(&cb->pending_bios);

	/* create and submit bios for the compressed pages */
	bytes_left = compressed_len;
	for (pg_index = 0; pg_index < cb->nr_pages; pg_index++) {
		page = compressed_pages[pg_index];
		page->mapping = inode->i_mapping;
		if (bio->bi_size)
			ret = io_tree->ops->merge_bio_hook(page, 0,
							   PAGE_CACHE_SIZE,
							   bio, 0);
		else
			ret = 0;

		page->mapping = NULL;
		if (ret || bio_add_page(bio, page, PAGE_CACHE_SIZE, 0) <
		    PAGE_CACHE_SIZE) {
			bio_get(bio);

			/*
			 * inc the count before we submit the bio so
			 * we know the end IO handler won't happen before
			 * we inc the count.  Otherwise, the cb might get
			 * freed before we're done setting it up
			 */
			atomic_inc(&cb->pending_bios);
			ret = btrfs_bio_wq_end_io(root->fs_info, bio, 0);
			BUG_ON(ret); /* -ENOMEM */

			if (!skip_sum) {
				ret = btrfs_csum_one_bio(root, inode, bio,
							 start, 1);
				BUG_ON(ret); /* -ENOMEM */
			}

			ret = btrfs_map_bio(root, WRITE, bio, 0, 1);
			BUG_ON(ret); /* -ENOMEM */

			bio_put(bio);

			bio = compressed_bio_alloc(bdev, first_byte, GFP_NOFS);
			BUG_ON(!bio);
			bio->bi_private = cb;
			bio->bi_end_io = end_compressed_bio_write;
			bio_add_page(bio, page, PAGE_CACHE_SIZE, 0);
		}
		if (bytes_left < PAGE_CACHE_SIZE) {
			printk("bytes left %lu compress len %lu nr %lu\n",
			       bytes_left, cb->compressed_len, cb->nr_pages);
		}
		bytes_left -= PAGE_CACHE_SIZE;
		first_byte += PAGE_CACHE_SIZE;
		cond_resched();
	}
	bio_get(bio);

	ret = btrfs_bio_wq_end_io(root->fs_info, bio, 0);
	BUG_ON(ret); /* -ENOMEM */

	if (!skip_sum) {
		ret = btrfs_csum_one_bio(root, inode, bio, start, 1);
		BUG_ON(ret); /* -ENOMEM */
	}

	ret = btrfs_map_bio(root, WRITE, bio, 0, 1);
	BUG_ON(ret); /* -ENOMEM */

	bio_put(bio);
	return 0;
}