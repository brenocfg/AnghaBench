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
struct btrfs_transaction {int /*<<< orphan*/  list; } ;
struct btrfs_trans_handle {int use_count; struct btrfs_transaction* transaction; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct TYPE_4__ {struct btrfs_trans_handle* journal_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  trans_lock; scalar_t__ trans_no_join; struct btrfs_transaction* running_transaction; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,struct btrfs_root*,int) ; 
 int /*<<< orphan*/  btrfs_cleanup_one_transaction (struct btrfs_transaction*,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_scrub_continue (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_trans_handle_cachep ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_transaction (struct btrfs_transaction*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_transaction_commit (struct btrfs_root*) ; 

__attribute__((used)) static void cleanup_transaction(struct btrfs_trans_handle *trans,
				struct btrfs_root *root, int err)
{
	struct btrfs_transaction *cur_trans = trans->transaction;

	WARN_ON(trans->use_count > 1);

	btrfs_abort_transaction(trans, root, err);

	spin_lock(&root->fs_info->trans_lock);
	list_del_init(&cur_trans->list);
	if (cur_trans == root->fs_info->running_transaction) {
		root->fs_info->running_transaction = NULL;
		root->fs_info->trans_no_join = 0;
	}
	spin_unlock(&root->fs_info->trans_lock);

	btrfs_cleanup_one_transaction(trans->transaction, root);

	put_transaction(cur_trans);
	put_transaction(cur_trans);

	trace_btrfs_transaction_commit(root);

	btrfs_scrub_continue(root);

	if (current->journal_info == trans)
		current->journal_info = NULL;

	kmem_cache_free(btrfs_trans_handle_cachep, trans);
}