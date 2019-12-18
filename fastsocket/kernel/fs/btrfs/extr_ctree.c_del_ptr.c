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
typedef  int u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {struct extent_buffer* node; int /*<<< orphan*/  fs_info; } ;
struct btrfs_path {struct extent_buffer** nodes; } ;
struct btrfs_key_ptr {int dummy; } ;
struct btrfs_disk_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MOD_LOG_KEY_REMOVE ; 
 int btrfs_header_level (struct extent_buffer*) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_mark_buffer_dirty (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_node_key (struct extent_buffer*,struct btrfs_disk_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_node_key_ptr_offset (int) ; 
 int /*<<< orphan*/  btrfs_set_header_level (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_header_nritems (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  fixup_low_keys (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,struct btrfs_disk_key*,int) ; 
 int /*<<< orphan*/  memmove_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tree_mod_log_eb_move (int /*<<< orphan*/ ,struct extent_buffer*,int,int,int) ; 
 int tree_mod_log_insert_key (int /*<<< orphan*/ ,struct extent_buffer*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void del_ptr(struct btrfs_trans_handle *trans, struct btrfs_root *root,
		    struct btrfs_path *path, int level, int slot,
		    int tree_mod_log)
{
	struct extent_buffer *parent = path->nodes[level];
	u32 nritems;
	int ret;

	nritems = btrfs_header_nritems(parent);
	if (slot != nritems - 1) {
		if (tree_mod_log && level)
			tree_mod_log_eb_move(root->fs_info, parent, slot,
					     slot + 1, nritems - slot - 1);
		memmove_extent_buffer(parent,
			      btrfs_node_key_ptr_offset(slot),
			      btrfs_node_key_ptr_offset(slot + 1),
			      sizeof(struct btrfs_key_ptr) *
			      (nritems - slot - 1));
	} else if (tree_mod_log && level) {
		ret = tree_mod_log_insert_key(root->fs_info, parent, slot,
					      MOD_LOG_KEY_REMOVE);
		BUG_ON(ret < 0);
	}

	nritems--;
	btrfs_set_header_nritems(parent, nritems);
	if (nritems == 0 && parent == root->node) {
		BUG_ON(btrfs_header_level(root->node) != 1);
		/* just turn the root into a leaf and break */
		btrfs_set_header_level(root->node, 0);
	} else if (slot == 0) {
		struct btrfs_disk_key disk_key;

		btrfs_node_key(parent, &disk_key, 0);
		fixup_low_keys(trans, root, path, &disk_key, level + 1);
	}
	btrfs_mark_buffer_dirty(parent);
}