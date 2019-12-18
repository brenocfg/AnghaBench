#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {TYPE_3__* fs_info; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_key {scalar_t__ type; int /*<<< orphan*/  offset; int /*<<< orphan*/  objectid; } ;
struct btrfs_free_cluster {int /*<<< orphan*/  refill_lock; } ;
struct TYPE_7__ {int offset; int /*<<< orphan*/  objectid; } ;
struct btrfs_block_group_cache {int flags; scalar_t__ cached; TYPE_2__ key; TYPE_1__* space_info; int /*<<< orphan*/  list; int /*<<< orphan*/  cache_node; int /*<<< orphan*/  lock; int /*<<< orphan*/ * inode; scalar_t__ iref; int /*<<< orphan*/  ro; } ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_8__ {int /*<<< orphan*/  block_group_cache_lock; int /*<<< orphan*/  block_group_cache_tree; struct btrfs_free_cluster meta_alloc_cluster; struct btrfs_free_cluster data_alloc_cluster; struct btrfs_root* extent_root; struct btrfs_root* tree_root; } ;
struct TYPE_6__ {int total_bytes; int bytes_readonly; int disk_total; int /*<<< orphan*/  lock; int /*<<< orphan*/  groups_sem; int /*<<< orphan*/ * block_groups; } ;

/* Variables and functions */
 int BTRFS_BLOCK_GROUP_DUP ; 
 int BTRFS_BLOCK_GROUP_RAID1 ; 
 int BTRFS_BLOCK_GROUP_RAID10 ; 
 scalar_t__ BTRFS_CACHE_STARTED ; 
 int /*<<< orphan*/  BTRFS_FREE_SPACE_OBJECTID ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  btrfs_add_delayed_iput (struct inode*) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_clear_space_info_full (TYPE_3__*) ; 
 int btrfs_del_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 struct btrfs_block_group_cache* btrfs_lookup_block_group (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int btrfs_orphan_add (struct btrfs_trans_handle*,struct inode*) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_remove_free_space_cache (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_return_cluster_to_free_space (struct btrfs_block_group_cache*,struct btrfs_free_cluster*) ; 
 int btrfs_search_slot (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int,int) ; 
 int /*<<< orphan*/  clear_avail_alloc_bits (TYPE_3__*,int) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_excluded_extents (struct btrfs_root*,struct btrfs_block_group_cache*) ; 
 int get_block_group_index (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct inode* lookup_free_space_inode (struct btrfs_root*,struct btrfs_block_group_cache*,struct btrfs_path*) ; 
 int /*<<< orphan*/  memcpy (struct btrfs_key*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_block_group_cache_done (struct btrfs_block_group_cache*) ; 

int btrfs_remove_block_group(struct btrfs_trans_handle *trans,
			     struct btrfs_root *root, u64 group_start)
{
	struct btrfs_path *path;
	struct btrfs_block_group_cache *block_group;
	struct btrfs_free_cluster *cluster;
	struct btrfs_root *tree_root = root->fs_info->tree_root;
	struct btrfs_key key;
	struct inode *inode;
	int ret;
	int index;
	int factor;

	root = root->fs_info->extent_root;

	block_group = btrfs_lookup_block_group(root->fs_info, group_start);
	BUG_ON(!block_group);
	BUG_ON(!block_group->ro);

	/*
	 * Free the reserved super bytes from this block group before
	 * remove it.
	 */
	free_excluded_extents(root, block_group);

	memcpy(&key, &block_group->key, sizeof(key));
	index = get_block_group_index(block_group);
	if (block_group->flags & (BTRFS_BLOCK_GROUP_DUP |
				  BTRFS_BLOCK_GROUP_RAID1 |
				  BTRFS_BLOCK_GROUP_RAID10))
		factor = 2;
	else
		factor = 1;

	/* make sure this block group isn't part of an allocation cluster */
	cluster = &root->fs_info->data_alloc_cluster;
	spin_lock(&cluster->refill_lock);
	btrfs_return_cluster_to_free_space(block_group, cluster);
	spin_unlock(&cluster->refill_lock);

	/*
	 * make sure this block group isn't part of a metadata
	 * allocation cluster
	 */
	cluster = &root->fs_info->meta_alloc_cluster;
	spin_lock(&cluster->refill_lock);
	btrfs_return_cluster_to_free_space(block_group, cluster);
	spin_unlock(&cluster->refill_lock);

	path = btrfs_alloc_path();
	if (!path) {
		ret = -ENOMEM;
		goto out;
	}

	inode = lookup_free_space_inode(tree_root, block_group, path);
	if (!IS_ERR(inode)) {
		ret = btrfs_orphan_add(trans, inode);
		if (ret) {
			btrfs_add_delayed_iput(inode);
			goto out;
		}
		clear_nlink(inode);
		/* One for the block groups ref */
		spin_lock(&block_group->lock);
		if (block_group->iref) {
			block_group->iref = 0;
			block_group->inode = NULL;
			spin_unlock(&block_group->lock);
			iput(inode);
		} else {
			spin_unlock(&block_group->lock);
		}
		/* One for our lookup ref */
		btrfs_add_delayed_iput(inode);
	}

	key.objectid = BTRFS_FREE_SPACE_OBJECTID;
	key.offset = block_group->key.objectid;
	key.type = 0;

	ret = btrfs_search_slot(trans, tree_root, &key, path, -1, 1);
	if (ret < 0)
		goto out;
	if (ret > 0)
		btrfs_release_path(path);
	if (ret == 0) {
		ret = btrfs_del_item(trans, tree_root, path);
		if (ret)
			goto out;
		btrfs_release_path(path);
	}

	spin_lock(&root->fs_info->block_group_cache_lock);
	rb_erase(&block_group->cache_node,
		 &root->fs_info->block_group_cache_tree);
	spin_unlock(&root->fs_info->block_group_cache_lock);

	down_write(&block_group->space_info->groups_sem);
	/*
	 * we must use list_del_init so people can check to see if they
	 * are still on the list after taking the semaphore
	 */
	list_del_init(&block_group->list);
	if (list_empty(&block_group->space_info->block_groups[index]))
		clear_avail_alloc_bits(root->fs_info, block_group->flags);
	up_write(&block_group->space_info->groups_sem);

	if (block_group->cached == BTRFS_CACHE_STARTED)
		wait_block_group_cache_done(block_group);

	btrfs_remove_free_space_cache(block_group);

	spin_lock(&block_group->space_info->lock);
	block_group->space_info->total_bytes -= block_group->key.offset;
	block_group->space_info->bytes_readonly -= block_group->key.offset;
	block_group->space_info->disk_total -= block_group->key.offset * factor;
	spin_unlock(&block_group->space_info->lock);

	memcpy(&key, &block_group->key, sizeof(key));

	btrfs_clear_space_info_full(root->fs_info);

	btrfs_put_block_group(block_group);
	btrfs_put_block_group(block_group);

	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	if (ret > 0)
		ret = -EIO;
	if (ret < 0)
		goto out;

	ret = btrfs_del_item(trans, root, path);
out:
	btrfs_free_path(path);
	return ret;
}