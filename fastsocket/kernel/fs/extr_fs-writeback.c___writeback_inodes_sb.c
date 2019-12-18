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
struct writeback_control {int /*<<< orphan*/  older_than_this; int /*<<< orphan*/  for_kupdate; } ;
struct super_block {int /*<<< orphan*/  s_umount; } ;
struct bdi_writeback {int /*<<< orphan*/  b_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  inode_lock ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_io (struct bdi_writeback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeback_sb_inodes (struct super_block*,struct bdi_writeback*,struct writeback_control*,int) ; 

__attribute__((used)) static void __writeback_inodes_sb(struct super_block *sb,
		struct bdi_writeback *wb, struct writeback_control *wbc)
{
	WARN_ON(!rwsem_is_locked(&sb->s_umount));

	spin_lock(&inode_lock);
	if (!wbc->for_kupdate || list_empty(&wb->b_io))
		queue_io(wb, wbc->older_than_this);
	writeback_sb_inodes(sb, wb, wbc, true);
	spin_unlock(&inode_lock);
}