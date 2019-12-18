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
struct super_block {int dummy; } ;
struct ocfs2_super {int /*<<< orphan*/  dentry_lock_work; int /*<<< orphan*/  vol_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_OSB_DROP_DENTRY_LOCK_IMMED ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 scalar_t__ VOLUME_DISABLED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dentry_list_lock ; 
 int /*<<< orphan*/  kill_block_super (struct super_block*) ; 
 int /*<<< orphan*/  ocfs2_set_osb_flag (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_kill_sb(struct super_block *sb)
{
	struct ocfs2_super *osb = OCFS2_SB(sb);

	/* Failed mount? */
	if (!osb || atomic_read(&osb->vol_state) == VOLUME_DISABLED)
		goto out;

	/* Prevent further queueing of inode drop events */
	spin_lock(&dentry_list_lock);
	ocfs2_set_osb_flag(osb, OCFS2_OSB_DROP_DENTRY_LOCK_IMMED);
	spin_unlock(&dentry_list_lock);
	/* Wait for work to finish and/or remove it */
	cancel_work_sync(&osb->dentry_lock_work);
out:
	kill_block_super(sb);
}