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
struct extent_buffer {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  fs_info; } ;
struct btrfs_path {scalar_t__* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ type; scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ BTRFS_ORPHAN_ITEM_KEY ; 
 scalar_t__ BTRFS_ORPHAN_OBJECTID ; 
 scalar_t__ BTRFS_ROOT_ITEM_KEY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IS_ERR (struct btrfs_root*) ; 
 int PTR_ERR (struct btrfs_root*) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int btrfs_find_dead_roots (struct btrfs_root*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 scalar_t__ btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,scalar_t__) ; 
 int btrfs_next_leaf (struct btrfs_root*,struct btrfs_path*) ; 
 struct btrfs_root* btrfs_read_fs_root_no_name (int /*<<< orphan*/ ,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int btrfs_find_orphan_roots(struct btrfs_root *tree_root)
{
	struct extent_buffer *leaf;
	struct btrfs_path *path;
	struct btrfs_key key;
	struct btrfs_key root_key;
	struct btrfs_root *root;
	int err = 0;
	int ret;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	key.objectid = BTRFS_ORPHAN_OBJECTID;
	key.type = BTRFS_ORPHAN_ITEM_KEY;
	key.offset = 0;

	root_key.type = BTRFS_ROOT_ITEM_KEY;
	root_key.offset = (u64)-1;

	while (1) {
		ret = btrfs_search_slot(NULL, tree_root, &key, path, 0, 0);
		if (ret < 0) {
			err = ret;
			break;
		}

		leaf = path->nodes[0];
		if (path->slots[0] >= btrfs_header_nritems(leaf)) {
			ret = btrfs_next_leaf(tree_root, path);
			if (ret < 0)
				err = ret;
			if (ret != 0)
				break;
			leaf = path->nodes[0];
		}

		btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
		btrfs_release_path(path);

		if (key.objectid != BTRFS_ORPHAN_OBJECTID ||
		    key.type != BTRFS_ORPHAN_ITEM_KEY)
			break;

		root_key.objectid = key.offset;
		key.offset++;

		root = btrfs_read_fs_root_no_name(tree_root->fs_info,
						  &root_key);
		if (!IS_ERR(root))
			continue;

		ret = PTR_ERR(root);
		if (ret != -ENOENT) {
			err = ret;
			break;
		}

		ret = btrfs_find_dead_roots(tree_root, root_key.objectid);
		if (ret) {
			err = ret;
			break;
		}
	}

	btrfs_free_path(path);
	return err;
}