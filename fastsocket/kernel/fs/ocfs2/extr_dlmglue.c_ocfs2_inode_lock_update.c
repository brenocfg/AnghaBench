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
struct ocfs2_lock_res {int dummy; } ;
struct ocfs2_inode_info {int ip_flags; scalar_t__ ip_blkno; int /*<<< orphan*/  ip_lock; struct ocfs2_lock_res ip_inode_lockres; } ;
struct ocfs2_dinode {int i_generation; int i_flags; int /*<<< orphan*/  i_dtime; } ;
struct inode {scalar_t__ i_generation; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INODE_DELETED ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCFS2_VALID_FL ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 unsigned long long le32_to_cpu (int) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,unsigned long long,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_complete_lock_res_refresh (struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  ocfs2_extent_map_trunc (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_meta_lvb_is_trustable (struct inode*,struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_purge (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_mount_local (struct ocfs2_super*) ; 
 int ocfs2_read_inode_block (struct inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_refresh_inode (struct inode*,struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  ocfs2_refresh_inode_from_lvb (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_should_refresh_lock_res (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_track_lock_refresh (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_inode_lock_update(struct inode *inode,
				  struct buffer_head **bh)
{
	int status = 0;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_lock_res *lockres = &oi->ip_inode_lockres;
	struct ocfs2_dinode *fe;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	mlog_entry_void();

	if (ocfs2_mount_local(osb))
		goto bail;

	spin_lock(&oi->ip_lock);
	if (oi->ip_flags & OCFS2_INODE_DELETED) {
		mlog(0, "Orphaned inode %llu was deleted while we "
		     "were waiting on a lock. ip_flags = 0x%x\n",
		     (unsigned long long)oi->ip_blkno, oi->ip_flags);
		spin_unlock(&oi->ip_lock);
		status = -ENOENT;
		goto bail;
	}
	spin_unlock(&oi->ip_lock);

	if (!ocfs2_should_refresh_lock_res(lockres))
		goto bail;

	/* This will discard any caching information we might have had
	 * for the inode metadata. */
	ocfs2_metadata_cache_purge(INODE_CACHE(inode));

	ocfs2_extent_map_trunc(inode, 0);

	if (ocfs2_meta_lvb_is_trustable(inode, lockres)) {
		mlog(0, "Trusting LVB on inode %llu\n",
		     (unsigned long long)oi->ip_blkno);
		ocfs2_refresh_inode_from_lvb(inode);
	} else {
		/* Boo, we have to go to disk. */
		/* read bh, cast, ocfs2_refresh_inode */
		status = ocfs2_read_inode_block(inode, bh);
		if (status < 0) {
			mlog_errno(status);
			goto bail_refresh;
		}
		fe = (struct ocfs2_dinode *) (*bh)->b_data;

		/* This is a good chance to make sure we're not
		 * locking an invalid object.  ocfs2_read_inode_block()
		 * already checked that the inode block is sane.
		 *
		 * We bug on a stale inode here because we checked
		 * above whether it was wiped from disk. The wiping
		 * node provides a guarantee that we receive that
		 * message and can mark the inode before dropping any
		 * locks associated with it. */
		mlog_bug_on_msg(inode->i_generation !=
				le32_to_cpu(fe->i_generation),
				"Invalid dinode %llu disk generation: %u "
				"inode->i_generation: %u\n",
				(unsigned long long)oi->ip_blkno,
				le32_to_cpu(fe->i_generation),
				inode->i_generation);
		mlog_bug_on_msg(le64_to_cpu(fe->i_dtime) ||
				!(fe->i_flags & cpu_to_le32(OCFS2_VALID_FL)),
				"Stale dinode %llu dtime: %llu flags: 0x%x\n",
				(unsigned long long)oi->ip_blkno,
				(unsigned long long)le64_to_cpu(fe->i_dtime),
				le32_to_cpu(fe->i_flags));

		ocfs2_refresh_inode(inode, fe);
		ocfs2_track_lock_refresh(lockres);
	}

	status = 0;
bail_refresh:
	ocfs2_complete_lock_res_refresh(lockres, status);
bail:
	mlog_exit(status);
	return status;
}