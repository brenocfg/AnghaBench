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
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_data; } ;
struct TYPE_2__ {int track_uptodate; } ;
struct btrfs_inode {int /*<<< orphan*/  rb_node; int /*<<< orphan*/  ordered_operations; int /*<<< orphan*/  delalloc_inodes; int /*<<< orphan*/  ordered_tree; int /*<<< orphan*/  delalloc_mutex; int /*<<< orphan*/  log_mutex; TYPE_1__ io_failure_tree; TYPE_1__ io_tree; int /*<<< orphan*/  extent_tree; struct inode vfs_inode; int /*<<< orphan*/ * delayed_node; int /*<<< orphan*/  force_compress; scalar_t__ runtime_flags; scalar_t__ reserved_extents; scalar_t__ outstanding_extents; int /*<<< orphan*/  lock; scalar_t__ last_unlink_trans; scalar_t__ index_cnt; scalar_t__ csum_bytes; scalar_t__ flags; scalar_t__ disk_i_size; scalar_t__ delalloc_bytes; scalar_t__ logged_trans; scalar_t__ last_sub_trans; scalar_t__ last_trans; scalar_t__ generation; int /*<<< orphan*/ * space_info; int /*<<< orphan*/ * root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_COMPRESS_NONE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_inode_cachep ; 
 int /*<<< orphan*/  btrfs_ordered_inode_tree_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_io_tree_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_map_tree_init (int /*<<< orphan*/ *) ; 
 struct btrfs_inode* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct inode *btrfs_alloc_inode(struct super_block *sb)
{
	struct btrfs_inode *ei;
	struct inode *inode;

	ei = kmem_cache_alloc(btrfs_inode_cachep, GFP_NOFS);
	if (!ei)
		return NULL;

	ei->root = NULL;
	ei->space_info = NULL;
	ei->generation = 0;
	ei->last_trans = 0;
	ei->last_sub_trans = 0;
	ei->logged_trans = 0;
	ei->delalloc_bytes = 0;
	ei->disk_i_size = 0;
	ei->flags = 0;
	ei->csum_bytes = 0;
	ei->index_cnt = (u64)-1;
	ei->last_unlink_trans = 0;

	spin_lock_init(&ei->lock);
	ei->outstanding_extents = 0;
	ei->reserved_extents = 0;

	ei->runtime_flags = 0;
	ei->force_compress = BTRFS_COMPRESS_NONE;

	ei->delayed_node = NULL;

	inode = &ei->vfs_inode;
	extent_map_tree_init(&ei->extent_tree);
	extent_io_tree_init(&ei->io_tree, &inode->i_data);
	extent_io_tree_init(&ei->io_failure_tree, &inode->i_data);
	ei->io_tree.track_uptodate = 1;
	ei->io_failure_tree.track_uptodate = 1;
	mutex_init(&ei->log_mutex);
	mutex_init(&ei->delalloc_mutex);
	btrfs_ordered_inode_tree_init(&ei->ordered_tree);
	INIT_LIST_HEAD(&ei->delalloc_inodes);
	INIT_LIST_HEAD(&ei->ordered_operations);
	RB_CLEAR_NODE(&ei->rb_node);

	return inode;
}