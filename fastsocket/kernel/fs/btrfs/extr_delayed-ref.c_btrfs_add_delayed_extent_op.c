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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_trans_handle {TYPE_1__* transaction; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_delayed_ref_root {int /*<<< orphan*/  lock; int /*<<< orphan*/  seq_wait; } ;
struct btrfs_delayed_ref_head {int /*<<< orphan*/  node; struct btrfs_delayed_extent_op* extent_op; } ;
struct btrfs_delayed_extent_op {int /*<<< orphan*/  is_data; } ;
struct TYPE_2__ {struct btrfs_delayed_ref_root delayed_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_UPDATE_DELAYED_HEAD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  add_delayed_ref_head (struct btrfs_fs_info*,struct btrfs_trans_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btrfs_delayed_ref_head* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int btrfs_add_delayed_extent_op(struct btrfs_fs_info *fs_info,
				struct btrfs_trans_handle *trans,
				u64 bytenr, u64 num_bytes,
				struct btrfs_delayed_extent_op *extent_op)
{
	struct btrfs_delayed_ref_head *head_ref;
	struct btrfs_delayed_ref_root *delayed_refs;

	head_ref = kmalloc(sizeof(*head_ref), GFP_NOFS);
	if (!head_ref)
		return -ENOMEM;

	head_ref->extent_op = extent_op;

	delayed_refs = &trans->transaction->delayed_refs;
	spin_lock(&delayed_refs->lock);

	add_delayed_ref_head(fs_info, trans, &head_ref->node, bytenr,
				   num_bytes, BTRFS_UPDATE_DELAYED_HEAD,
				   extent_op->is_data);

	if (waitqueue_active(&delayed_refs->seq_wait))
		wake_up(&delayed_refs->seq_wait);
	spin_unlock(&delayed_refs->lock);
	return 0;
}