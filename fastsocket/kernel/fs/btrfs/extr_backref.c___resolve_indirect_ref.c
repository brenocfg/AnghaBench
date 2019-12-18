#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ulist {int dummy; } ;
struct extent_buffer {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  node; } ;
struct btrfs_path {int search_commit_root; int lowest_level; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ offset; int /*<<< orphan*/  type; scalar_t__ objectid; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_3__ {scalar_t__ offset; int /*<<< orphan*/  type; scalar_t__ objectid; } ;
struct __prelim_ref {int level; int /*<<< orphan*/  wanted_disk_byte; TYPE_1__ key_for_search; int /*<<< orphan*/  count; scalar_t__ root_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ROOT_ITEM_KEY ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btrfs_root*) ; 
 int PTR_ERR (struct btrfs_root*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int add_all_parents (struct btrfs_root*,struct btrfs_path*,struct ulist*,int,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__ const*) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int btrfs_header_level (int /*<<< orphan*/ ) ; 
 struct btrfs_root* btrfs_read_fs_root_no_name (struct btrfs_fs_info*,struct btrfs_key*) ; 
 int btrfs_search_old_slot (struct btrfs_root*,TYPE_1__*,struct btrfs_path*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long,int,int /*<<< orphan*/ ,int,unsigned long long,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int __resolve_indirect_ref(struct btrfs_fs_info *fs_info,
					int search_commit_root,
					u64 time_seq,
					struct __prelim_ref *ref,
					struct ulist *parents,
					const u64 *extent_item_pos)
{
	struct btrfs_path *path;
	struct btrfs_root *root;
	struct btrfs_key root_key;
	struct extent_buffer *eb;
	int ret = 0;
	int root_level;
	int level = ref->level;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;
	path->search_commit_root = !!search_commit_root;

	root_key.objectid = ref->root_id;
	root_key.type = BTRFS_ROOT_ITEM_KEY;
	root_key.offset = (u64)-1;
	root = btrfs_read_fs_root_no_name(fs_info, &root_key);
	if (IS_ERR(root)) {
		ret = PTR_ERR(root);
		goto out;
	}

	rcu_read_lock();
	root_level = btrfs_header_level(root->node);
	rcu_read_unlock();

	if (root_level + 1 == level)
		goto out;

	path->lowest_level = level;
	ret = btrfs_search_old_slot(root, &ref->key_for_search, path, time_seq);
	pr_debug("search slot in root %llu (level %d, ref count %d) returned "
		 "%d for key (%llu %u %llu)\n",
		 (unsigned long long)ref->root_id, level, ref->count, ret,
		 (unsigned long long)ref->key_for_search.objectid,
		 ref->key_for_search.type,
		 (unsigned long long)ref->key_for_search.offset);
	if (ret < 0)
		goto out;

	eb = path->nodes[level];
	while (!eb) {
		if (!level) {
			WARN_ON(1);
			ret = 1;
			goto out;
		}
		level--;
		eb = path->nodes[level];
	}

	ret = add_all_parents(root, path, parents, level, &ref->key_for_search,
				time_seq, ref->wanted_disk_byte,
				extent_item_pos);
out:
	btrfs_free_path(path);
	return ret;
}