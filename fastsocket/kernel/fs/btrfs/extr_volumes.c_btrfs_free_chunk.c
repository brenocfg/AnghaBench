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
typedef  void* u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_key {int /*<<< orphan*/  type; void* offset; void* objectid; } ;
struct TYPE_2__ {struct btrfs_root* chunk_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_CHUNK_ITEM_KEY ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int btrfs_del_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_error (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int btrfs_search_slot (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int,int) ; 

__attribute__((used)) static int btrfs_free_chunk(struct btrfs_trans_handle *trans,
			    struct btrfs_root *root,
			    u64 chunk_tree, u64 chunk_objectid,
			    u64 chunk_offset)
{
	int ret;
	struct btrfs_path *path;
	struct btrfs_key key;

	root = root->fs_info->chunk_root;
	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	key.objectid = chunk_objectid;
	key.offset = chunk_offset;
	key.type = BTRFS_CHUNK_ITEM_KEY;

	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	if (ret < 0)
		goto out;
	else if (ret > 0) { /* Logic error or corruption */
		btrfs_error(root->fs_info, -ENOENT,
			    "Failed lookup while freeing chunk.");
		ret = -ENOENT;
		goto out;
	}

	ret = btrfs_del_item(trans, root, path);
	if (ret < 0)
		btrfs_error(root->fs_info, ret,
			    "Failed to delete chunk item.");
out:
	btrfs_free_path(path);
	return ret;
}