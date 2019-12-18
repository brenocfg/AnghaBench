#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
typedef  void* u32 ;
struct TYPE_5__ {int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_instances; int /*<<< orphan*/  s_list; scalar_t__ s_dev; int /*<<< orphan*/ * s_root; } ;
struct TYPE_6__ {void* objectid; } ;
struct btrfs_root {TYPE_2__ anon_super; TYPE_3__ root_key; scalar_t__ defrag_running; int /*<<< orphan*/  kobj_unregister; int /*<<< orphan*/  defrag_trans_start; TYPE_3__ root_kobj; TYPE_3__ defrag_progress; TYPE_3__ root_item; int /*<<< orphan*/  dirty_log_pages; scalar_t__ last_log_commit; scalar_t__ log_transid; scalar_t__ log_batch; int /*<<< orphan*/  orphan_inodes; int /*<<< orphan*/  log_writers; int /*<<< orphan*/ * log_commit; int /*<<< orphan*/ * log_commit_wait; int /*<<< orphan*/  log_writer_wait; int /*<<< orphan*/  log_mutex; int /*<<< orphan*/  objectid_mutex; int /*<<< orphan*/  accounting_lock; int /*<<< orphan*/  inode_lock; int /*<<< orphan*/  orphan_lock; int /*<<< orphan*/  root_list; int /*<<< orphan*/  dirty_list; int /*<<< orphan*/ * orphan_block_rsv; int /*<<< orphan*/ * block_rsv; int /*<<< orphan*/  delayed_nodes_tree; int /*<<< orphan*/  inode_tree; int /*<<< orphan*/ * name; scalar_t__ highest_objectid; scalar_t__ last_trans; void* objectid; scalar_t__ orphan_cleanup_state; scalar_t__ orphan_item_inserted; scalar_t__ in_radix; scalar_t__ track_dirty; scalar_t__ ref_cows; void* stripesize; void* leafsize; void* nodesize; void* sectorsize; int /*<<< orphan*/ * commit_root; int /*<<< orphan*/ * node; } ;
struct btrfs_fs_info {int /*<<< orphan*/  generation; TYPE_1__* btree_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_io_tree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __setup_root(u32 nodesize, u32 leafsize, u32 sectorsize,
			 u32 stripesize, struct btrfs_root *root,
			 struct btrfs_fs_info *fs_info,
			 u64 objectid)
{
	root->node = NULL;
	root->commit_root = NULL;
	root->sectorsize = sectorsize;
	root->nodesize = nodesize;
	root->leafsize = leafsize;
	root->stripesize = stripesize;
	root->ref_cows = 0;
	root->track_dirty = 0;
	root->in_radix = 0;
	root->orphan_item_inserted = 0;
	root->orphan_cleanup_state = 0;

	root->objectid = objectid;
	root->last_trans = 0;
	root->highest_objectid = 0;
	root->name = NULL;
	root->inode_tree = RB_ROOT;
	INIT_RADIX_TREE(&root->delayed_nodes_tree, GFP_ATOMIC);
	root->block_rsv = NULL;
	root->orphan_block_rsv = NULL;

	INIT_LIST_HEAD(&root->dirty_list);
	INIT_LIST_HEAD(&root->root_list);
	spin_lock_init(&root->orphan_lock);
	spin_lock_init(&root->inode_lock);
	spin_lock_init(&root->accounting_lock);
	mutex_init(&root->objectid_mutex);
	mutex_init(&root->log_mutex);
	init_waitqueue_head(&root->log_writer_wait);
	init_waitqueue_head(&root->log_commit_wait[0]);
	init_waitqueue_head(&root->log_commit_wait[1]);
	atomic_set(&root->log_commit[0], 0);
	atomic_set(&root->log_commit[1], 0);
	atomic_set(&root->log_writers, 0);
	atomic_set(&root->orphan_inodes, 0);
	root->log_batch = 0;
	root->log_transid = 0;
	root->last_log_commit = 0;
	extent_io_tree_init(&root->dirty_log_pages,
			     fs_info->btree_inode->i_mapping);

	memset(&root->root_key, 0, sizeof(root->root_key));
	memset(&root->root_item, 0, sizeof(root->root_item));
	memset(&root->defrag_progress, 0, sizeof(root->defrag_progress));
	memset(&root->root_kobj, 0, sizeof(root->root_kobj));
	root->defrag_trans_start = fs_info->generation;
	init_completion(&root->kobj_unregister);
	root->defrag_running = 0;
	root->root_key.objectid = objectid;
	root->anon_super.s_root = NULL;
	root->anon_super.s_dev = 0;
	INIT_LIST_HEAD(&root->anon_super.s_list);
	INIT_LIST_HEAD(&root->anon_super.s_instances);
	init_rwsem(&root->anon_super.s_umount);
}