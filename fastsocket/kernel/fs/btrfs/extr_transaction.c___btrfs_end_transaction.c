#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num_heads_ready; } ;
struct btrfs_transaction {int blocked; int /*<<< orphan*/  writer_wait; int /*<<< orphan*/  num_writers; int /*<<< orphan*/  in_commit; TYPE_1__ delayed_refs; } ;
struct btrfs_trans_handle {unsigned long delayed_ref_updates; scalar_t__ aborted; scalar_t__ use_count; struct btrfs_transaction* transaction; int /*<<< orphan*/ * block_rsv; int /*<<< orphan*/ * orig_rsv; } ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int fs_state; struct btrfs_transaction* running_transaction; int /*<<< orphan*/  transaction_kthread; int /*<<< orphan*/  open_ioctl_trans; int /*<<< orphan*/  sb; } ;
struct TYPE_4__ {struct btrfs_trans_handle* journal_info; } ;

/* Variables and functions */
 int BTRFS_SUPER_FLAG_ERROR ; 
 int EIO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int btrfs_commit_transaction (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_run_delayed_iputs (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_run_delayed_refs (struct btrfs_trans_handle*,struct btrfs_root*,unsigned long) ; 
 int /*<<< orphan*/  btrfs_trans_handle_cachep ; 
 int /*<<< orphan*/  btrfs_trans_release_metadata (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  memset (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_transaction (struct btrfs_transaction*) ; 
 int /*<<< orphan*/  sb_end_intwrite (int /*<<< orphan*/ ) ; 
 scalar_t__ should_end_transaction (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __btrfs_end_transaction(struct btrfs_trans_handle *trans,
			  struct btrfs_root *root, int throttle, int lock)
{
	struct btrfs_transaction *cur_trans = trans->transaction;
	struct btrfs_fs_info *info = root->fs_info;
	int count = 0;
	int err = 0;

	if (--trans->use_count) {
		trans->block_rsv = trans->orig_rsv;
		return 0;
	}

	btrfs_trans_release_metadata(trans, root);
	trans->block_rsv = NULL;
	while (count < 2) {
		unsigned long cur = trans->delayed_ref_updates;
		trans->delayed_ref_updates = 0;
		if (cur &&
		    trans->transaction->delayed_refs.num_heads_ready > 64) {
			trans->delayed_ref_updates = 0;
			btrfs_run_delayed_refs(trans, root, cur);
		} else {
			break;
		}
		count++;
	}

	sb_end_intwrite(root->fs_info->sb);

	if (lock && !atomic_read(&root->fs_info->open_ioctl_trans) &&
	    should_end_transaction(trans, root)) {
		trans->transaction->blocked = 1;
		smp_wmb();
	}

	if (lock && cur_trans->blocked && !cur_trans->in_commit) {
		if (throttle) {
			/*
			 * We may race with somebody else here so end up having
			 * to call end_transaction on ourselves again, so inc
			 * our use_count.
			 */
			trans->use_count++;
			return btrfs_commit_transaction(trans, root);
		} else {
			wake_up_process(info->transaction_kthread);
		}
	}

	WARN_ON(cur_trans != info->running_transaction);
	WARN_ON(atomic_read(&cur_trans->num_writers) < 1);
	atomic_dec(&cur_trans->num_writers);

	smp_mb();
	if (waitqueue_active(&cur_trans->writer_wait))
		wake_up(&cur_trans->writer_wait);
	put_transaction(cur_trans);

	if (current->journal_info == trans)
		current->journal_info = NULL;

	if (throttle)
		btrfs_run_delayed_iputs(root);

	if (trans->aborted ||
	    root->fs_info->fs_state & BTRFS_SUPER_FLAG_ERROR) {
		err = -EIO;
	}

	memset(trans, 0, sizeof(*trans));
	kmem_cache_free(btrfs_trans_handle_cachep, trans);
	return err;
}