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
struct btrfs_root {TYPE_1__* fs_info; } ;
struct btrfs_delayed_root {int dummy; } ;
struct btrfs_delayed_node {int dummy; } ;
struct TYPE_4__ {scalar_t__ flags; int /*<<< orphan*/  func; } ;
struct btrfs_async_delayed_node {TYPE_2__ work; struct btrfs_delayed_node* delayed_node; struct btrfs_root* root; } ;
struct TYPE_3__ {int /*<<< orphan*/  delayed_workers; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  btrfs_async_run_delayed_node_done ; 
 struct btrfs_delayed_node* btrfs_first_prepared_delayed_node (struct btrfs_delayed_root*) ; 
 int /*<<< orphan*/  btrfs_queue_worker (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  btrfs_release_prepared_delayed_node (struct btrfs_delayed_node*) ; 
 struct btrfs_async_delayed_node* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btrfs_wq_run_delayed_node(struct btrfs_delayed_root *delayed_root,
				     struct btrfs_root *root, int all)
{
	struct btrfs_async_delayed_node *async_node;
	struct btrfs_delayed_node *curr;
	int count = 0;

again:
	curr = btrfs_first_prepared_delayed_node(delayed_root);
	if (!curr)
		return 0;

	async_node = kmalloc(sizeof(*async_node), GFP_NOFS);
	if (!async_node) {
		btrfs_release_prepared_delayed_node(curr);
		return -ENOMEM;
	}

	async_node->root = root;
	async_node->delayed_node = curr;

	async_node->work.func = btrfs_async_run_delayed_node_done;
	async_node->work.flags = 0;

	btrfs_queue_worker(&root->fs_info->delayed_workers, &async_node->work);
	count++;

	if (all || count < 4)
		goto again;

	return 0;
}