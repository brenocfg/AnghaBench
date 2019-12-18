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
struct ocfs2_super {struct ocfs2_dentry_lock* dentry_lock_list; } ;
struct ocfs2_dentry_lock {int /*<<< orphan*/  dl_inode; struct ocfs2_dentry_lock* dl_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  dentry_list_lock ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_dentry_lock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ocfs2_drop_dl_inodes(struct ocfs2_super *osb, int drop_count)
{
	struct ocfs2_dentry_lock *dl;

	spin_lock(&dentry_list_lock);
	while (osb->dentry_lock_list && (drop_count < 0 || drop_count--)) {
		dl = osb->dentry_lock_list;
		osb->dentry_lock_list = dl->dl_next;
		spin_unlock(&dentry_list_lock);
		iput(dl->dl_inode);
		kfree(dl);
		spin_lock(&dentry_list_lock);
	}
	spin_unlock(&dentry_list_lock);
}