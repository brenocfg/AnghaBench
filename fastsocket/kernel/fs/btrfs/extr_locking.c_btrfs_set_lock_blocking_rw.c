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
struct extent_buffer {scalar_t__ lock_owner; int /*<<< orphan*/  lock; int /*<<< orphan*/  spinning_readers; int /*<<< orphan*/  blocking_readers; int /*<<< orphan*/  blocking_writers; int /*<<< orphan*/  spinning_writers; scalar_t__ lock_nested; } ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int BTRFS_READ_LOCK ; 
 int BTRFS_WRITE_LOCK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_assert_tree_locked (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_assert_tree_read_locked (struct extent_buffer*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void btrfs_set_lock_blocking_rw(struct extent_buffer *eb, int rw)
{
	if (eb->lock_nested) {
		read_lock(&eb->lock);
		if (eb->lock_nested && current->pid == eb->lock_owner) {
			read_unlock(&eb->lock);
			return;
		}
		read_unlock(&eb->lock);
	}
	if (rw == BTRFS_WRITE_LOCK) {
		if (atomic_read(&eb->blocking_writers) == 0) {
			WARN_ON(atomic_read(&eb->spinning_writers) != 1);
			atomic_dec(&eb->spinning_writers);
			btrfs_assert_tree_locked(eb);
			atomic_inc(&eb->blocking_writers);
			write_unlock(&eb->lock);
		}
	} else if (rw == BTRFS_READ_LOCK) {
		btrfs_assert_tree_read_locked(eb);
		atomic_inc(&eb->blocking_readers);
		WARN_ON(atomic_read(&eb->spinning_readers) == 0);
		atomic_dec(&eb->spinning_readers);
		read_unlock(&eb->lock);
	}
	return;
}