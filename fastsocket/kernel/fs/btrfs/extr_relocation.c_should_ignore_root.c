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
struct btrfs_root {TYPE_2__* fs_info; int /*<<< orphan*/  root_item; struct btrfs_root* reloc_root; int /*<<< orphan*/  ref_cows; } ;
struct TYPE_4__ {TYPE_1__* running_transaction; } ;
struct TYPE_3__ {int transid; } ;

/* Variables and functions */
 int btrfs_root_last_snapshot (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int should_ignore_root(struct btrfs_root *root)
{
	struct btrfs_root *reloc_root;

	if (!root->ref_cows)
		return 0;

	reloc_root = root->reloc_root;
	if (!reloc_root)
		return 0;

	if (btrfs_root_last_snapshot(&reloc_root->root_item) ==
	    root->fs_info->running_transaction->transid - 1)
		return 0;
	/*
	 * if there is reloc tree and it was created in previous
	 * transaction backref lookup can find the reloc tree,
	 * so backref node for the fs tree root is useless for
	 * relocation.
	 */
	return 1;
}