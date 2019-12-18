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
typedef  void* u64 ;
struct walk_control {scalar_t__ stage; int pin; int /*<<< orphan*/  process_func; struct btrfs_trans_handle* replay_dest; struct btrfs_trans_handle* trans; } ;
struct btrfs_trans_handle {struct btrfs_trans_handle* log_root; int /*<<< orphan*/  node; int /*<<< orphan*/  commit_root; struct btrfs_fs_info* fs_info; } ;
struct btrfs_root {struct btrfs_root* log_root; int /*<<< orphan*/  node; int /*<<< orphan*/  commit_root; struct btrfs_fs_info* fs_info; } ;
struct btrfs_path {scalar_t__* slots; int /*<<< orphan*/ * nodes; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ offset; int /*<<< orphan*/  type; } ;
struct btrfs_fs_info {int log_root_recovering; int /*<<< orphan*/  tree_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ROOT_ITEM_KEY ; 
 scalar_t__ BTRFS_TREE_LOG_OBJECTID ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 scalar_t__ LOG_WALK_REPLAY_ALL ; 
 scalar_t__ LOG_WALK_REPLAY_INODES ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_commit_transaction (struct btrfs_trans_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_error (struct btrfs_fs_info*,int,char*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (int /*<<< orphan*/ ,struct btrfs_key*,scalar_t__) ; 
 struct btrfs_trans_handle* btrfs_read_fs_root_no_name (struct btrfs_fs_info*,struct btrfs_key*) ; 
 struct btrfs_trans_handle* btrfs_read_fs_root_no_radix (struct btrfs_trans_handle*,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_record_root_in_trans (struct btrfs_trans_handle*,struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,struct btrfs_trans_handle*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_key_type (struct btrfs_key*,int /*<<< orphan*/ ) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fixup_inode_link_counts (struct btrfs_trans_handle*,struct btrfs_trans_handle*,struct btrfs_path*) ; 
 int /*<<< orphan*/  free_extent_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  process_one_buffer ; 
 int /*<<< orphan*/  replay_one_buffer ; 
 int walk_log_tree (struct btrfs_trans_handle*,struct btrfs_trans_handle*,struct walk_control*) ; 

int btrfs_recover_log_trees(struct btrfs_root *log_root_tree)
{
	int ret;
	struct btrfs_path *path;
	struct btrfs_trans_handle *trans;
	struct btrfs_key key;
	struct btrfs_key found_key;
	struct btrfs_key tmp_key;
	struct btrfs_root *log;
	struct btrfs_fs_info *fs_info = log_root_tree->fs_info;
	struct walk_control wc = {
		.process_func = process_one_buffer,
		.stage = 0,
	};

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	fs_info->log_root_recovering = 1;

	trans = btrfs_start_transaction(fs_info->tree_root, 0);
	if (IS_ERR(trans)) {
		ret = PTR_ERR(trans);
		goto error;
	}

	wc.trans = trans;
	wc.pin = 1;

	ret = walk_log_tree(trans, log_root_tree, &wc);
	if (ret) {
		btrfs_error(fs_info, ret, "Failed to pin buffers while "
			    "recovering log root tree.");
		goto error;
	}

again:
	key.objectid = BTRFS_TREE_LOG_OBJECTID;
	key.offset = (u64)-1;
	btrfs_set_key_type(&key, BTRFS_ROOT_ITEM_KEY);

	while (1) {
		ret = btrfs_search_slot(NULL, log_root_tree, &key, path, 0, 0);

		if (ret < 0) {
			btrfs_error(fs_info, ret,
				    "Couldn't find tree log root.");
			goto error;
		}
		if (ret > 0) {
			if (path->slots[0] == 0)
				break;
			path->slots[0]--;
		}
		btrfs_item_key_to_cpu(path->nodes[0], &found_key,
				      path->slots[0]);
		btrfs_release_path(path);
		if (found_key.objectid != BTRFS_TREE_LOG_OBJECTID)
			break;

		log = btrfs_read_fs_root_no_radix(log_root_tree,
						  &found_key);
		if (IS_ERR(log)) {
			ret = PTR_ERR(log);
			btrfs_error(fs_info, ret,
				    "Couldn't read tree log root.");
			goto error;
		}

		tmp_key.objectid = found_key.offset;
		tmp_key.type = BTRFS_ROOT_ITEM_KEY;
		tmp_key.offset = (u64)-1;

		wc.replay_dest = btrfs_read_fs_root_no_name(fs_info, &tmp_key);
		if (IS_ERR(wc.replay_dest)) {
			ret = PTR_ERR(wc.replay_dest);
			btrfs_error(fs_info, ret, "Couldn't read target root "
				    "for tree log recovery.");
			goto error;
		}

		wc.replay_dest->log_root = log;
		btrfs_record_root_in_trans(trans, wc.replay_dest);
		ret = walk_log_tree(trans, log, &wc);
		BUG_ON(ret);

		if (wc.stage == LOG_WALK_REPLAY_ALL) {
			ret = fixup_inode_link_counts(trans, wc.replay_dest,
						      path);
			BUG_ON(ret);
		}

		key.offset = found_key.offset - 1;
		wc.replay_dest->log_root = NULL;
		free_extent_buffer(log->node);
		free_extent_buffer(log->commit_root);
		kfree(log);

		if (found_key.offset == 0)
			break;
	}
	btrfs_release_path(path);

	/* step one is to pin it all, step two is to replay just inodes */
	if (wc.pin) {
		wc.pin = 0;
		wc.process_func = replay_one_buffer;
		wc.stage = LOG_WALK_REPLAY_INODES;
		goto again;
	}
	/* step three is to replay everything */
	if (wc.stage < LOG_WALK_REPLAY_ALL) {
		wc.stage++;
		goto again;
	}

	btrfs_free_path(path);

	free_extent_buffer(log_root_tree->node);
	log_root_tree->log_root = NULL;
	fs_info->log_root_recovering = 0;

	/* step 4: commit the transaction, which also unpins the blocks */
	btrfs_commit_transaction(trans, fs_info->tree_root);

	kfree(log_root_tree);
	return 0;

error:
	btrfs_free_path(path);
	return ret;
}