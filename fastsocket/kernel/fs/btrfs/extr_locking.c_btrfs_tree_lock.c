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
struct extent_buffer {int /*<<< orphan*/  lock_owner; int /*<<< orphan*/  write_locks; int /*<<< orphan*/  spinning_writers; int /*<<< orphan*/  blocking_writers; int /*<<< orphan*/  write_lock_wq; int /*<<< orphan*/  lock; int /*<<< orphan*/  blocking_readers; int /*<<< orphan*/  read_lock_wq; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void btrfs_tree_lock(struct extent_buffer *eb)
{
again:
	wait_event(eb->read_lock_wq, atomic_read(&eb->blocking_readers) == 0);
	wait_event(eb->write_lock_wq, atomic_read(&eb->blocking_writers) == 0);
	write_lock(&eb->lock);
	if (atomic_read(&eb->blocking_readers)) {
		write_unlock(&eb->lock);
		wait_event(eb->read_lock_wq,
			   atomic_read(&eb->blocking_readers) == 0);
		goto again;
	}
	if (atomic_read(&eb->blocking_writers)) {
		write_unlock(&eb->lock);
		wait_event(eb->write_lock_wq,
			   atomic_read(&eb->blocking_writers) == 0);
		goto again;
	}
	WARN_ON(atomic_read(&eb->spinning_writers));
	atomic_inc(&eb->spinning_writers);
	atomic_inc(&eb->write_locks);
	eb->lock_owner = current->pid;
}