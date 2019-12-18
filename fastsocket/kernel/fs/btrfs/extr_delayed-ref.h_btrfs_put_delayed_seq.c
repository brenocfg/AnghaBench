#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct seq_list {int /*<<< orphan*/  list; } ;
struct btrfs_delayed_ref_root {int /*<<< orphan*/  lock; int /*<<< orphan*/  seq_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
btrfs_put_delayed_seq(struct btrfs_delayed_ref_root *delayed_refs,
		      struct seq_list *elem)
{
	spin_lock(&delayed_refs->lock);
	list_del(&elem->list);
	wake_up(&delayed_refs->seq_wait);
	spin_unlock(&delayed_refs->lock);
}