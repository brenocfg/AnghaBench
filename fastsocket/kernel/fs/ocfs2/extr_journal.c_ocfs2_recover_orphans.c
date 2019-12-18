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
struct ocfs2_super {int dummy; } ;
struct ocfs2_inode_info {int ip_flags; int /*<<< orphan*/  ip_lock; struct inode* ip_next_orphan; scalar_t__ ip_blkno; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INODE_DELETED ; 
 int OCFS2_INODE_MAYBE_ORPHANED ; 
 int OCFS2_INODE_SKIP_DELETE ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clear_recovering_orphan_dir (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_mark_recovering_orphan_dir (struct ocfs2_super*,int) ; 
 int ocfs2_queue_orphans (struct ocfs2_super*,int,struct inode**) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_recover_orphans(struct ocfs2_super *osb,
				 int slot)
{
	int ret = 0;
	struct inode *inode = NULL;
	struct inode *iter;
	struct ocfs2_inode_info *oi;

	mlog(0, "Recover inodes from orphan dir in slot %d\n", slot);

	ocfs2_mark_recovering_orphan_dir(osb, slot);
	ret = ocfs2_queue_orphans(osb, slot, &inode);
	ocfs2_clear_recovering_orphan_dir(osb, slot);

	/* Error here should be noted, but we want to continue with as
	 * many queued inodes as we've got. */
	if (ret)
		mlog_errno(ret);

	while (inode) {
		oi = OCFS2_I(inode);
		mlog(0, "iput orphan %llu\n", (unsigned long long)oi->ip_blkno);

		iter = oi->ip_next_orphan;

		spin_lock(&oi->ip_lock);
		/* The remote delete code may have set these on the
		 * assumption that the other node would wipe them
		 * successfully.  If they are still in the node's
		 * orphan dir, we need to reset that state. */
		oi->ip_flags &= ~(OCFS2_INODE_DELETED|OCFS2_INODE_SKIP_DELETE);

		/* Set the proper information to get us going into
		 * ocfs2_delete_inode. */
		oi->ip_flags |= OCFS2_INODE_MAYBE_ORPHANED;
		spin_unlock(&oi->ip_lock);

		iput(inode);

		inode = iter;
	}

	return ret;
}