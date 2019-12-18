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
typedef  void* u64 ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct extent_map_tree {int /*<<< orphan*/  lock; } ;
struct extent_map {void* len; void* start; int /*<<< orphan*/  bdev; scalar_t__ block_start; void* block_len; } ;
struct TYPE_8__ {TYPE_3__* root; struct extent_map_tree extent_tree; } ;
struct TYPE_7__ {TYPE_2__* fs_info; } ;
struct TYPE_6__ {TYPE_1__* fs_devices; } ;
struct TYPE_5__ {int /*<<< orphan*/  latest_bdev; } ;

/* Variables and functions */
 TYPE_4__* BTRFS_I (struct inode*) ; 
 int EEXIST ; 
 int EIO ; 
 int ENOMEM ; 
 struct extent_map* ERR_PTR (int) ; 
 int add_extent_mapping (struct extent_map_tree*,struct extent_map*) ; 
 struct extent_map* alloc_extent_map () ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 struct extent_map* lookup_extent_mapping (struct extent_map_tree*,void*,void*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct extent_map *btree_get_extent(struct inode *inode,
		struct page *page, size_t pg_offset, u64 start, u64 len,
		int create)
{
	struct extent_map_tree *em_tree = &BTRFS_I(inode)->extent_tree;
	struct extent_map *em;
	int ret;

	read_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, start, len);
	if (em) {
		em->bdev =
			BTRFS_I(inode)->root->fs_info->fs_devices->latest_bdev;
		read_unlock(&em_tree->lock);
		goto out;
	}
	read_unlock(&em_tree->lock);

	em = alloc_extent_map();
	if (!em) {
		em = ERR_PTR(-ENOMEM);
		goto out;
	}
	em->start = 0;
	em->len = (u64)-1;
	em->block_len = (u64)-1;
	em->block_start = 0;
	em->bdev = BTRFS_I(inode)->root->fs_info->fs_devices->latest_bdev;

	write_lock(&em_tree->lock);
	ret = add_extent_mapping(em_tree, em);
	if (ret == -EEXIST) {
		u64 failed_start = em->start;
		u64 failed_len = em->len;

		free_extent_map(em);
		em = lookup_extent_mapping(em_tree, start, len);
		if (em) {
			ret = 0;
		} else {
			em = lookup_extent_mapping(em_tree, failed_start,
						   failed_len);
			ret = -EIO;
		}
	} else if (ret) {
		free_extent_map(em);
		em = NULL;
	}
	write_unlock(&em_tree->lock);

	if (ret)
		em = ERR_PTR(ret);
out:
	return em;
}