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
struct rb_node {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct btrfs_ordered_inode_tree {int /*<<< orphan*/  tree; int /*<<< orphan*/  lock; int /*<<< orphan*/ * last; } ;
struct btrfs_ordered_extent {int /*<<< orphan*/  wait; int /*<<< orphan*/  root_extent_list; int /*<<< orphan*/  flags; struct rb_node rb_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  ordered_operations; struct btrfs_ordered_inode_tree ordered_tree; struct btrfs_root* root; } ;
struct TYPE_3__ {int /*<<< orphan*/  ordered_extent_lock; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_ORDERED_COMPLETE ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mapping_tagged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (struct rb_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_ordered_extent_remove (struct inode*,struct btrfs_ordered_extent*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void btrfs_remove_ordered_extent(struct inode *inode,
				 struct btrfs_ordered_extent *entry)
{
	struct btrfs_ordered_inode_tree *tree;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct rb_node *node;

	tree = &BTRFS_I(inode)->ordered_tree;
	spin_lock_irq(&tree->lock);
	node = &entry->rb_node;
	rb_erase(node, &tree->tree);
	tree->last = NULL;
	set_bit(BTRFS_ORDERED_COMPLETE, &entry->flags);
	spin_unlock_irq(&tree->lock);

	spin_lock(&root->fs_info->ordered_extent_lock);
	list_del_init(&entry->root_extent_list);

	trace_btrfs_ordered_extent_remove(inode, entry);

	/*
	 * we have no more ordered extents for this inode and
	 * no dirty pages.  We can safely remove it from the
	 * list of ordered extents
	 */
	if (RB_EMPTY_ROOT(&tree->tree) &&
	    !mapping_tagged(inode->i_mapping, PAGECACHE_TAG_DIRTY)) {
		list_del_init(&BTRFS_I(inode)->ordered_operations);
	}
	spin_unlock(&root->fs_info->ordered_extent_lock);
	wake_up(&entry->wait);
}