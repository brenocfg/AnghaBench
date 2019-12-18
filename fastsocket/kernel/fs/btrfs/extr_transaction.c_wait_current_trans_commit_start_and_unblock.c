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
struct btrfs_transaction {int /*<<< orphan*/  blocked; scalar_t__ in_commit; scalar_t__ commit_done; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  transaction_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wait_current_trans_commit_start_and_unblock(struct btrfs_root *root,
					 struct btrfs_transaction *trans)
{
	wait_event(root->fs_info->transaction_wait,
		   trans->commit_done || (trans->in_commit && !trans->blocked));
}