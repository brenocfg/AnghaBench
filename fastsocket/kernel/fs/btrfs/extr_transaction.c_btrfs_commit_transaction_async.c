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
struct btrfs_transaction {int /*<<< orphan*/  use_count; } ;
struct btrfs_trans_handle {struct btrfs_transaction* transaction; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_async_commit {int /*<<< orphan*/  work; int /*<<< orphan*/  newtrans; struct btrfs_root* root; } ;
struct TYPE_2__ {struct btrfs_trans_handle* journal_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_join_transaction (struct btrfs_root*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  do_async_commit ; 
 int /*<<< orphan*/  kfree (struct btrfs_async_commit*) ; 
 struct btrfs_async_commit* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_transaction (struct btrfs_transaction*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_current_trans_commit_start (struct btrfs_root*,struct btrfs_transaction*) ; 
 int /*<<< orphan*/  wait_current_trans_commit_start_and_unblock (struct btrfs_root*,struct btrfs_transaction*) ; 

int btrfs_commit_transaction_async(struct btrfs_trans_handle *trans,
				   struct btrfs_root *root,
				   int wait_for_unblock)
{
	struct btrfs_async_commit *ac;
	struct btrfs_transaction *cur_trans;

	ac = kmalloc(sizeof(*ac), GFP_NOFS);
	if (!ac)
		return -ENOMEM;

	INIT_DELAYED_WORK(&ac->work, do_async_commit);
	ac->root = root;
	ac->newtrans = btrfs_join_transaction(root);
	if (IS_ERR(ac->newtrans)) {
		int err = PTR_ERR(ac->newtrans);
		kfree(ac);
		return err;
	}

	/* take transaction reference */
	cur_trans = trans->transaction;
	atomic_inc(&cur_trans->use_count);

	btrfs_end_transaction(trans, root);
	schedule_delayed_work(&ac->work, 0);

	/* wait for transaction to start and unblock */
	if (wait_for_unblock)
		wait_current_trans_commit_start_and_unblock(root, cur_trans);
	else
		wait_current_trans_commit_start(root, cur_trans);

	if (current->journal_info == trans)
		current->journal_info = NULL;

	put_transaction(cur_trans);
	return 0;
}