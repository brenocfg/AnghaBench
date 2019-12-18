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
struct extent_buffer {scalar_t__ lock_owner; int lock_nested; int /*<<< orphan*/  spinning_readers; int /*<<< orphan*/  read_locks; int /*<<< orphan*/  lock; int /*<<< orphan*/  blocking_writers; int /*<<< orphan*/  write_lock_wq; } ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void btrfs_tree_read_lock(struct extent_buffer *eb)
{
again:
	read_lock(&eb->lock);
	if (atomic_read(&eb->blocking_writers) &&
	    current->pid == eb->lock_owner) {
		/*
		 * This extent is already write-locked by our thread. We allow
		 * an additional read lock to be added because it's for the same
		 * thread. btrfs_find_all_roots() depends on this as it may be
		 * called on a partly (write-)locked tree.
		 */
		BUG_ON(eb->lock_nested);
		eb->lock_nested = 1;
		read_unlock(&eb->lock);
		return;
	}
	read_unlock(&eb->lock);
	wait_event(eb->write_lock_wq, atomic_read(&eb->blocking_writers) == 0);
	read_lock(&eb->lock);
	if (atomic_read(&eb->blocking_writers)) {
		read_unlock(&eb->lock);
		goto again;
	}
	atomic_inc(&eb->read_locks);
	atomic_inc(&eb->spinning_readers);
}