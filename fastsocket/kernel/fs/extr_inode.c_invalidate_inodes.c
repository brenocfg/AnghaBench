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
struct super_block {int /*<<< orphan*/  s_inodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispose_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_unmount_inodes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_lock ; 
 int /*<<< orphan*/  inotify_unmount_inodes (int /*<<< orphan*/ *) ; 
 int invalidate_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iprune_sem ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throw_away ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int invalidate_inodes(struct super_block *sb, bool kill_dirty)
{
	int busy;
	LIST_HEAD(throw_away);

	down_write(&iprune_sem);
	spin_lock(&inode_lock);
	inotify_unmount_inodes(&sb->s_inodes);
	fsnotify_unmount_inodes(&sb->s_inodes);
	busy = invalidate_list(&sb->s_inodes, &throw_away, kill_dirty);
	spin_unlock(&inode_lock);

	dispose_list(&throw_away);
	up_write(&iprune_sem);

	return busy;
}