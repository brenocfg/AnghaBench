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
struct btrfs_delayed_tree_ref {int /*<<< orphan*/  node; } ;
struct btrfs_delayed_ref_root {int /*<<< orphan*/  lock; int /*<<< orphan*/  seq_wait; } ;
struct btrfs_delayed_ref_head {int /*<<< orphan*/  node; struct btrfs_delayed_extent_op* extent_op; } ;
struct btrfs_delayed_extent_op {scalar_t__ is_data; } ;
struct TYPE_2__ {struct btrfs_delayed_ref_root delayed_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  add_delayed_ref_head (struct btrfs_fs_info*,struct btrfs_trans_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_delayed_tree_ref (struct btrfs_fs_info*,struct btrfs_trans_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  is_fstree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct btrfs_delayed_tree_ref*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int btrfs_add_delayed_tree_ref(struct btrfs_fs_info *fs_info,
			       struct btrfs_trans_handle *trans,
			       u64 bytenr, u64 num_bytes, u64 parent,
			       u64 ref_root,  int level, int action,
			       struct btrfs_delayed_extent_op *extent_op,
			       int for_cow)
{
	struct btrfs_delayed_tree_ref *ref;
	struct btrfs_delayed_ref_head *head_ref;
	struct btrfs_delayed_ref_root *delayed_refs;

	BUG_ON(extent_op && extent_op->is_data);
	ref = kmalloc(sizeof(*ref), GFP_NOFS);
	if (!ref)
		return -ENOMEM;

	head_ref = kmalloc(sizeof(*head_ref), GFP_NOFS);
	if (!head_ref) {
		kfree(ref);
		return -ENOMEM;
	}

	head_ref->extent_op = extent_op;

	delayed_refs = &trans->transaction->delayed_refs;
	spin_lock(&delayed_refs->lock);

	/*
	 * insert both the head node and the new ref without dropping
	 * the spin lock
	 */
	add_delayed_ref_head(fs_info, trans, &head_ref->node, bytenr,
				   num_bytes, action, 0);

	add_delayed_tree_ref(fs_info, trans, &ref->node, bytenr,
				   num_bytes, parent, ref_root, level, action,
				   for_cow);
	if (!is_fstree(ref_root) &&
	    waitqueue_active(&delayed_refs->seq_wait))
		wake_up(&delayed_refs->seq_wait);
	spin_unlock(&delayed_refs->lock);

	return 0;
}