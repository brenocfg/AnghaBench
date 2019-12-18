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
typedef  int /*<<< orphan*/  u64 ;
struct tree_mod_root {int /*<<< orphan*/  level; int /*<<< orphan*/  logical; } ;
struct tree_mod_elem {scalar_t__ op; int /*<<< orphan*/  generation; struct tree_mod_root old_root; } ;
struct extent_buffer {int /*<<< orphan*/  start; } ;
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_1__ root_key; struct extent_buffer* node; int /*<<< orphan*/  nodesize; int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_MIXED_BACKREF_REV ; 
 scalar_t__ MOD_LOG_ROOT_REPLACE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct tree_mod_elem* __tree_mod_log_oldest_root (int /*<<< orphan*/ ,struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __tree_mod_log_rewind (struct extent_buffer*,int /*<<< orphan*/ ,struct tree_mod_elem*) ; 
 struct extent_buffer* alloc_dummy_extent_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct extent_buffer* btrfs_clone_extent_buffer (struct extent_buffer*) ; 
 scalar_t__ btrfs_header_level (struct extent_buffer*) ; 
 struct extent_buffer* btrfs_read_lock_root_node (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_set_header_backref_rev (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_header_bytenr (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_header_generation (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_header_level (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_header_owner (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_tree_read_lock (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_read_unlock (struct extent_buffer*) ; 
 int /*<<< orphan*/  extent_buffer_get (struct extent_buffer*) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 struct tree_mod_elem* tree_mod_log_search (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct extent_buffer *
get_old_root(struct btrfs_root *root, u64 time_seq)
{
	struct tree_mod_elem *tm;
	struct extent_buffer *eb;
	struct tree_mod_root *old_root = NULL;
	u64 old_generation = 0;
	u64 logical;

	eb = btrfs_read_lock_root_node(root);
	tm = __tree_mod_log_oldest_root(root->fs_info, root, time_seq);
	if (!tm)
		return root->node;

	if (tm->op == MOD_LOG_ROOT_REPLACE) {
		old_root = &tm->old_root;
		old_generation = tm->generation;
		logical = old_root->logical;
	} else {
		logical = root->node->start;
	}

	tm = tree_mod_log_search(root->fs_info, logical, time_seq);
	if (old_root)
		eb = alloc_dummy_extent_buffer(logical, root->nodesize);
	else
		eb = btrfs_clone_extent_buffer(root->node);
	btrfs_tree_read_unlock(root->node);
	free_extent_buffer(root->node);
	if (!eb)
		return NULL;
	btrfs_tree_read_lock(eb);
	if (old_root) {
		btrfs_set_header_bytenr(eb, eb->start);
		btrfs_set_header_backref_rev(eb, BTRFS_MIXED_BACKREF_REV);
		btrfs_set_header_owner(eb, root->root_key.objectid);
		btrfs_set_header_level(eb, old_root->level);
		btrfs_set_header_generation(eb, old_generation);
	}
	if (tm)
		__tree_mod_log_rewind(eb, time_seq, tm);
	else
		WARN_ON(btrfs_header_level(eb) != 0);
	extent_buffer_get(eb);

	return eb;
}