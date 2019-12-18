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
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int ip_dyn_features; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_check_range_for_holes (struct inode*,scalar_t__,size_t) ; 
 int ocfs2_check_range_for_refcount (struct inode*,scalar_t__,size_t) ; 
 int ocfs2_inode_lock (struct inode*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_prepare_inode_for_refcount (struct inode*,scalar_t__,size_t,int*) ; 
 int ocfs2_write_remove_suid (struct inode*) ; 
 scalar_t__ should_remove_suid (struct dentry*) ; 

__attribute__((used)) static int ocfs2_prepare_inode_for_write(struct dentry *dentry,
					 loff_t *ppos,
					 size_t count,
					 int appending,
					 int *direct_io)
{
	int ret = 0, meta_level = 0;
	struct inode *inode = dentry->d_inode;
	loff_t saved_pos, end;

	/* 
	 * We start with a read level meta lock and only jump to an ex
	 * if we need to make modifications here.
	 */
	for(;;) {
		ret = ocfs2_inode_lock(inode, NULL, meta_level);
		if (ret < 0) {
			meta_level = -1;
			mlog_errno(ret);
			goto out;
		}

		/* Clear suid / sgid if necessary. We do this here
		 * instead of later in the write path because
		 * remove_suid() calls ->setattr without any hint that
		 * we may have already done our cluster locking. Since
		 * ocfs2_setattr() *must* take cluster locks to
		 * proceeed, this will lead us to recursively lock the
		 * inode. There's also the dinode i_size state which
		 * can be lost via setattr during extending writes (we
		 * set inode->i_size at the end of a write. */
		if (should_remove_suid(dentry)) {
			if (meta_level == 0) {
				ocfs2_inode_unlock(inode, meta_level);
				meta_level = 1;
				continue;
			}

			ret = ocfs2_write_remove_suid(inode);
			if (ret < 0) {
				mlog_errno(ret);
				goto out_unlock;
			}
		}

		/* work on a copy of ppos until we're sure that we won't have
		 * to recalculate it due to relocking. */
		if (appending) {
			saved_pos = i_size_read(inode);
			mlog(0, "O_APPEND: inode->i_size=%llu\n", saved_pos);
		} else {
			saved_pos = *ppos;
		}

		end = saved_pos + count;

		ret = ocfs2_check_range_for_refcount(inode, saved_pos, count);
		if (ret == 1) {
			ocfs2_inode_unlock(inode, meta_level);
			meta_level = -1;

			ret = ocfs2_prepare_inode_for_refcount(inode,
							       saved_pos,
							       count,
							       &meta_level);
		}

		if (ret < 0) {
			mlog_errno(ret);
			goto out_unlock;
		}

		/*
		 * Skip the O_DIRECT checks if we don't need
		 * them.
		 */
		if (!direct_io || !(*direct_io))
			break;

		/*
		 * There's no sane way to do direct writes to an inode
		 * with inline data.
		 */
		if (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) {
			*direct_io = 0;
			break;
		}

		/*
		 * Allowing concurrent direct writes means
		 * i_size changes wouldn't be synchronized, so
		 * one node could wind up truncating another
		 * nodes writes.
		 */
		if (end > i_size_read(inode)) {
			*direct_io = 0;
			break;
		}

		/*
		 * We don't fill holes during direct io, so
		 * check for them here. If any are found, the
		 * caller will have to retake some cluster
		 * locks and initiate the io as buffered.
		 */
		ret = ocfs2_check_range_for_holes(inode, saved_pos, count);
		if (ret == 1) {
			*direct_io = 0;
			ret = 0;
		} else if (ret < 0)
			mlog_errno(ret);
		break;
	}

	if (appending)
		*ppos = saved_pos;

out_unlock:
	if (meta_level >= 0)
		ocfs2_inode_unlock(inode, meta_level);

out:
	return ret;
}