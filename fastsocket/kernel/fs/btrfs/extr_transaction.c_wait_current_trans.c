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
struct btrfs_transaction {scalar_t__ blocked; int /*<<< orphan*/  use_count; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  trans_lock; int /*<<< orphan*/  transaction_wait; struct btrfs_transaction* running_transaction; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_transaction (struct btrfs_transaction*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wait_current_trans(struct btrfs_root *root)
{
	struct btrfs_transaction *cur_trans;

	spin_lock(&root->fs_info->trans_lock);
	cur_trans = root->fs_info->running_transaction;
	if (cur_trans && cur_trans->blocked) {
		atomic_inc(&cur_trans->use_count);
		spin_unlock(&root->fs_info->trans_lock);

		wait_event(root->fs_info->transaction_wait,
			   !cur_trans->blocked);
		put_transaction(cur_trans);
	} else {
		spin_unlock(&root->fs_info->trans_lock);
	}
}