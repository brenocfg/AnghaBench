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
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int log_transid; int /*<<< orphan*/  root_item; int /*<<< orphan*/  root_key; TYPE_1__* fs_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  log_root_tree; } ;

/* Variables and functions */
 int btrfs_insert_root (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int btrfs_update_root (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int update_log_root(struct btrfs_trans_handle *trans,
			   struct btrfs_root *log)
{
	int ret;

	if (log->log_transid == 1) {
		/* insert root item on the first sync */
		ret = btrfs_insert_root(trans, log->fs_info->log_root_tree,
				&log->root_key, &log->root_item);
	} else {
		ret = btrfs_update_root(trans, log->fs_info->log_root_tree,
				&log->root_key, &log->root_item);
	}
	return ret;
}