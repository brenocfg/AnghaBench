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
struct btrfs_trans_handle {TYPE_1__* transaction; } ;
struct btrfs_delayed_ref_root {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  in_tree; int /*<<< orphan*/  refs; } ;
struct btrfs_delayed_ref_head {TYPE_2__ node; int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {struct btrfs_delayed_ref_root delayed_refs; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_put_delayed_ref (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int btrfs_delayed_ref_lock(struct btrfs_trans_handle *trans,
			   struct btrfs_delayed_ref_head *head)
{
	struct btrfs_delayed_ref_root *delayed_refs;

	delayed_refs = &trans->transaction->delayed_refs;
	assert_spin_locked(&delayed_refs->lock);
	if (mutex_trylock(&head->mutex))
		return 0;

	atomic_inc(&head->node.refs);
	spin_unlock(&delayed_refs->lock);

	mutex_lock(&head->mutex);
	spin_lock(&delayed_refs->lock);
	if (!head->node.in_tree) {
		mutex_unlock(&head->mutex);
		btrfs_put_delayed_ref(&head->node);
		return -EAGAIN;
	}
	btrfs_put_delayed_ref(&head->node);
	return 0;
}