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
struct btrfs_root {int dummy; } ;
struct btrfs_path {int* slots; int lowest_level; struct extent_buffer** nodes; scalar_t__* locks; int /*<<< orphan*/  keep_locks; } ;
struct btrfs_key {int dummy; } ;

/* Variables and functions */
 int BTRFS_MAX_LEVEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ btrfs_buffer_uptodate (struct extent_buffer*,scalar_t__,int) ; 
 struct extent_buffer* btrfs_find_tree_block (struct btrfs_root*,scalar_t__,int /*<<< orphan*/ ) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 int /*<<< orphan*/  btrfs_level_size (struct btrfs_root*,int) ; 
 scalar_t__ btrfs_node_blockptr (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_node_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 scalar_t__ btrfs_node_ptr_generation (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 

int btrfs_find_next_key(struct btrfs_root *root, struct btrfs_path *path,
			struct btrfs_key *key, int level,
			int cache_only, u64 min_trans)
{
	int slot;
	struct extent_buffer *c;

	WARN_ON(!path->keep_locks);
	while (level < BTRFS_MAX_LEVEL) {
		if (!path->nodes[level])
			return 1;

		slot = path->slots[level] + 1;
		c = path->nodes[level];
next:
		if (slot >= btrfs_header_nritems(c)) {
			int ret;
			int orig_lowest;
			struct btrfs_key cur_key;
			if (level + 1 >= BTRFS_MAX_LEVEL ||
			    !path->nodes[level + 1])
				return 1;

			if (path->locks[level + 1]) {
				level++;
				continue;
			}

			slot = btrfs_header_nritems(c) - 1;
			if (level == 0)
				btrfs_item_key_to_cpu(c, &cur_key, slot);
			else
				btrfs_node_key_to_cpu(c, &cur_key, slot);

			orig_lowest = path->lowest_level;
			btrfs_release_path(path);
			path->lowest_level = level;
			ret = btrfs_search_slot(NULL, root, &cur_key, path,
						0, 0);
			path->lowest_level = orig_lowest;
			if (ret < 0)
				return ret;

			c = path->nodes[level];
			slot = path->slots[level];
			if (ret == 0)
				slot++;
			goto next;
		}

		if (level == 0)
			btrfs_item_key_to_cpu(c, key, slot);
		else {
			u64 blockptr = btrfs_node_blockptr(c, slot);
			u64 gen = btrfs_node_ptr_generation(c, slot);

			if (cache_only) {
				struct extent_buffer *cur;
				cur = btrfs_find_tree_block(root, blockptr,
					    btrfs_level_size(root, level - 1));
				if (!cur ||
				    btrfs_buffer_uptodate(cur, gen, 1) <= 0) {
					slot++;
					if (cur)
						free_extent_buffer(cur);
					goto next;
				}
				free_extent_buffer(cur);
			}
			if (gen < min_trans) {
				slot++;
				goto next;
			}
			btrfs_node_key_to_cpu(c, key, slot);
		}
		return 0;
	}
	return 1;
}