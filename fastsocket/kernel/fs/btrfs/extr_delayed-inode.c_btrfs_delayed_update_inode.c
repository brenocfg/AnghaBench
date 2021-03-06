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
struct inode {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {TYPE_2__* fs_info; } ;
struct btrfs_delayed_node {int inode_dirty; int /*<<< orphan*/  mutex; int /*<<< orphan*/  count; int /*<<< orphan*/  inode_item; } ;
struct TYPE_4__ {TYPE_1__* delayed_root; } ;
struct TYPE_3__ {int /*<<< orphan*/  items; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct btrfs_delayed_node*) ; 
 int PTR_ERR (struct btrfs_delayed_node*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int btrfs_delayed_inode_reserve_metadata (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*,struct btrfs_delayed_node*) ; 
 struct btrfs_delayed_node* btrfs_get_or_create_delayed_node (struct inode*) ; 
 int /*<<< orphan*/  btrfs_release_delayed_node (struct btrfs_delayed_node*) ; 
 int /*<<< orphan*/  fill_stack_inode_item (struct btrfs_trans_handle*,int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int btrfs_delayed_update_inode(struct btrfs_trans_handle *trans,
			       struct btrfs_root *root, struct inode *inode)
{
	struct btrfs_delayed_node *delayed_node;
	int ret = 0;

	delayed_node = btrfs_get_or_create_delayed_node(inode);
	if (IS_ERR(delayed_node))
		return PTR_ERR(delayed_node);

	mutex_lock(&delayed_node->mutex);
	if (delayed_node->inode_dirty) {
		fill_stack_inode_item(trans, &delayed_node->inode_item, inode);
		goto release_node;
	}

	ret = btrfs_delayed_inode_reserve_metadata(trans, root, inode,
						   delayed_node);
	if (ret)
		goto release_node;

	fill_stack_inode_item(trans, &delayed_node->inode_item, inode);
	delayed_node->inode_dirty = 1;
	delayed_node->count++;
	atomic_inc(&root->fs_info->delayed_root->items);
release_node:
	mutex_unlock(&delayed_node->mutex);
	btrfs_release_delayed_node(delayed_node);
	return ret;
}