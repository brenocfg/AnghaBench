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
struct extent_buffer {int /*<<< orphan*/  spinning_readers; int /*<<< orphan*/  read_locks; int /*<<< orphan*/  lock; int /*<<< orphan*/  blocking_writers; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

int btrfs_try_tree_read_lock(struct extent_buffer *eb)
{
	if (atomic_read(&eb->blocking_writers))
		return 0;

	read_lock(&eb->lock);
	if (atomic_read(&eb->blocking_writers)) {
		read_unlock(&eb->lock);
		return 0;
	}
	atomic_inc(&eb->read_locks);
	atomic_inc(&eb->spinning_readers);
	return 1;
}