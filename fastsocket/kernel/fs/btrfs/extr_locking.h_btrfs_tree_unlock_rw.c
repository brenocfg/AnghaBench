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
struct extent_buffer {int dummy; } ;

/* Variables and functions */
 int BTRFS_READ_LOCK ; 
 int BTRFS_READ_LOCK_BLOCKING ; 
 int BTRFS_WRITE_LOCK ; 
 int BTRFS_WRITE_LOCK_BLOCKING ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  btrfs_tree_read_unlock (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_read_unlock_blocking (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_unlock (struct extent_buffer*) ; 

__attribute__((used)) static inline void btrfs_tree_unlock_rw(struct extent_buffer *eb, int rw)
{
	if (rw == BTRFS_WRITE_LOCK || rw == BTRFS_WRITE_LOCK_BLOCKING)
		btrfs_tree_unlock(eb);
	else if (rw == BTRFS_READ_LOCK_BLOCKING)
		btrfs_tree_read_unlock_blocking(eb);
	else if (rw == BTRFS_READ_LOCK)
		btrfs_tree_read_unlock(eb);
	else
		BUG();
}