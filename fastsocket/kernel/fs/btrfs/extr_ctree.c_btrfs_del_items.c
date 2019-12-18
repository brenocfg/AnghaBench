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
struct btrfs_root {struct extent_buffer* node; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; } ;
struct btrfs_map_token {int dummy; } ;
struct btrfs_item {int dummy; } ;
struct btrfs_disk_key {int dummy; } ;

/* Variables and functions */
 int BTRFS_LEAF_DATA_SIZE (struct btrfs_root*) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  btrfs_del_leaf (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,struct extent_buffer*) ; 
 scalar_t__ btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_init_map_token (struct btrfs_map_token*) ; 
 int /*<<< orphan*/  btrfs_item_key (struct extent_buffer*,struct btrfs_disk_key*,int /*<<< orphan*/ ) ; 
 struct btrfs_item* btrfs_item_nr (struct extent_buffer*,int) ; 
 scalar_t__ btrfs_item_nr_offset (int) ; 
 int btrfs_item_offset_nr (struct extent_buffer*,int) ; 
 scalar_t__ btrfs_item_size_nr (struct extent_buffer*,int) ; 
 scalar_t__ btrfs_leaf_data (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_mark_buffer_dirty (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_set_header_level (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_header_nritems (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_set_path_blocking (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_set_token_item_offset (struct extent_buffer*,struct btrfs_item*,int,struct btrfs_map_token*) ; 
 int btrfs_token_item_offset (struct extent_buffer*,struct btrfs_item*,struct btrfs_map_token*) ; 
 int /*<<< orphan*/  clean_tree_block (struct btrfs_trans_handle*,struct btrfs_root*,struct extent_buffer*) ; 
 int /*<<< orphan*/  extent_buffer_get (struct extent_buffer*) ; 
 int /*<<< orphan*/  fixup_low_keys (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,struct btrfs_disk_key*,int) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 int leaf_data_end (struct btrfs_root*,struct extent_buffer*) ; 
 int leaf_space_used (struct extent_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove_extent_buffer (struct extent_buffer*,scalar_t__,scalar_t__,int) ; 
 int push_leaf_left (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,int,int,int,int) ; 
 int push_leaf_right (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,int,int,int,int /*<<< orphan*/ ) ; 

int btrfs_del_items(struct btrfs_trans_handle *trans, struct btrfs_root *root,
		    struct btrfs_path *path, int slot, int nr)
{
	struct extent_buffer *leaf;
	struct btrfs_item *item;
	int last_off;
	int dsize = 0;
	int ret = 0;
	int wret;
	int i;
	u32 nritems;
	struct btrfs_map_token token;

	btrfs_init_map_token(&token);

	leaf = path->nodes[0];
	last_off = btrfs_item_offset_nr(leaf, slot + nr - 1);

	for (i = 0; i < nr; i++)
		dsize += btrfs_item_size_nr(leaf, slot + i);

	nritems = btrfs_header_nritems(leaf);

	if (slot + nr != nritems) {
		int data_end = leaf_data_end(root, leaf);

		memmove_extent_buffer(leaf, btrfs_leaf_data(leaf) +
			      data_end + dsize,
			      btrfs_leaf_data(leaf) + data_end,
			      last_off - data_end);

		for (i = slot + nr; i < nritems; i++) {
			u32 ioff;

			item = btrfs_item_nr(leaf, i);
			ioff = btrfs_token_item_offset(leaf, item, &token);
			btrfs_set_token_item_offset(leaf, item,
						    ioff + dsize, &token);
		}

		memmove_extent_buffer(leaf, btrfs_item_nr_offset(slot),
			      btrfs_item_nr_offset(slot + nr),
			      sizeof(struct btrfs_item) *
			      (nritems - slot - nr));
	}
	btrfs_set_header_nritems(leaf, nritems - nr);
	nritems -= nr;

	/* delete the leaf if we've emptied it */
	if (nritems == 0) {
		if (leaf == root->node) {
			btrfs_set_header_level(leaf, 0);
		} else {
			btrfs_set_path_blocking(path);
			clean_tree_block(trans, root, leaf);
			btrfs_del_leaf(trans, root, path, leaf);
		}
	} else {
		int used = leaf_space_used(leaf, 0, nritems);
		if (slot == 0) {
			struct btrfs_disk_key disk_key;

			btrfs_item_key(leaf, &disk_key, 0);
			fixup_low_keys(trans, root, path, &disk_key, 1);
		}

		/* delete the leaf if it is mostly empty */
		if (used < BTRFS_LEAF_DATA_SIZE(root) / 3) {
			/* push_leaf_left fixes the path.
			 * make sure the path still points to our leaf
			 * for possible call to del_ptr below
			 */
			slot = path->slots[1];
			extent_buffer_get(leaf);

			btrfs_set_path_blocking(path);
			wret = push_leaf_left(trans, root, path, 1, 1,
					      1, (u32)-1);
			if (wret < 0 && wret != -ENOSPC)
				ret = wret;

			if (path->nodes[0] == leaf &&
			    btrfs_header_nritems(leaf)) {
				wret = push_leaf_right(trans, root, path, 1,
						       1, 1, 0);
				if (wret < 0 && wret != -ENOSPC)
					ret = wret;
			}

			if (btrfs_header_nritems(leaf) == 0) {
				path->slots[1] = slot;
				btrfs_del_leaf(trans, root, path, leaf);
				free_extent_buffer(leaf);
				ret = 0;
			} else {
				/* if we're still in the path, make sure
				 * we're dirty.  Otherwise, one of the
				 * push_leaf functions must have already
				 * dirtied this buffer
				 */
				if (path->nodes[0] == leaf)
					btrfs_mark_buffer_dirty(leaf);
				free_extent_buffer(leaf);
			}
		} else {
			btrfs_mark_buffer_dirty(leaf);
		}
	}
	return ret;
}