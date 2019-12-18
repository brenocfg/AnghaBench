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
struct ocfs2_super {scalar_t__ dc_task; struct inode* root_inode; } ;
struct ocfs2_inode_info {int ip_flags; int /*<<< orphan*/  ip_lock; scalar_t__ ip_blkno; } ;
struct inode {unsigned long long i_ino; int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INODE_SKIP_DELETE ; 
 int OCFS2_INODE_SYSTEM_FILE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_inode_is_valid_to_delete(struct inode *inode)
{
	int ret = 0;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	/* We shouldn't be getting here for the root directory
	 * inode.. */
	if (inode == osb->root_inode) {
		mlog(ML_ERROR, "Skipping delete of root inode.\n");
		goto bail;
	}

	/* If we're coming from downconvert_thread we can't go into our own
	 * voting [hello, deadlock city!], so unforuntately we just
	 * have to skip deleting this guy. That's OK though because
	 * the node who's doing the actual deleting should handle it
	 * anyway. */
	if (current == osb->dc_task) {
		mlog(0, "Skipping delete of %lu because we're currently "
		     "in downconvert\n", inode->i_ino);
		goto bail;
	}

	spin_lock(&oi->ip_lock);
	/* OCFS2 *never* deletes system files. This should technically
	 * never get here as system file inodes should always have a
	 * positive link count. */
	if (oi->ip_flags & OCFS2_INODE_SYSTEM_FILE) {
		mlog(ML_ERROR, "Skipping delete of system file %llu\n",
		     (unsigned long long)oi->ip_blkno);
		goto bail_unlock;
	}

	/* If we have allowd wipe of this inode for another node, it
	 * will be marked here so we can safely skip it. Recovery will
	 * cleanup any inodes we might inadvertantly skip here. */
	if (oi->ip_flags & OCFS2_INODE_SKIP_DELETE) {
		mlog(0, "Skipping delete of %lu because another node "
		     "has done this for us.\n", inode->i_ino);
		goto bail_unlock;
	}

	ret = 1;
bail_unlock:
	spin_unlock(&oi->ip_lock);
bail:
	return ret;
}