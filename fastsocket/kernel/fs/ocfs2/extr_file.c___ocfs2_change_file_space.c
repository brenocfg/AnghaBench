#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {int dummy; } ;
struct ocfs2_space_resv {int l_whence; scalar_t__ l_start; scalar_t__ l_len; } ;
struct inode {int i_flags; int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; TYPE_2__* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct buffer_head {int dummy; } ;
typedef  unsigned long long s64 ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_6__ {int /*<<< orphan*/  ip_alloc_sem; } ;
struct TYPE_5__ {unsigned long long s_maxbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EINVAL ; 
 int EPERM ; 
 int EROFS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_INODE_UPDATE_CREDITS ; 
#define  OCFS2_IOC_RESVSP 131 
#define  OCFS2_IOC_RESVSP64 130 
#define  OCFS2_IOC_UNRESVSP 129 
#define  OCFS2_IOC_UNRESVSP64 128 
 struct ocfs2_super* OCFS2_SB (TYPE_2__*) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int S_APPEND ; 
 int S_IMMUTABLE ; 
 int __ocfs2_write_remove_suid (struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ocfs2_allocate_unwritten_extents (struct inode*,unsigned long long,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 scalar_t__ ocfs2_is_hard_readonly (struct ocfs2_super*) ; 
 scalar_t__ ocfs2_is_soft_readonly (struct ocfs2_super*) ; 
 int ocfs2_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 int ocfs2_remove_inode_range (struct inode*,struct buffer_head*,unsigned long long,scalar_t__) ; 
 int ocfs2_rw_lock (struct inode*,int) ; 
 int /*<<< orphan*/  ocfs2_rw_unlock (struct inode*,int) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 scalar_t__ should_remove_suid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __ocfs2_change_file_space(struct file *file, struct inode *inode,
				     loff_t f_pos, unsigned int cmd,
				     struct ocfs2_space_resv *sr,
				     int change_size)
{
	int ret;
	s64 llen;
	loff_t size;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct buffer_head *di_bh = NULL;
	handle_t *handle;
	unsigned long long max_off = inode->i_sb->s_maxbytes;

	if (ocfs2_is_hard_readonly(osb) || ocfs2_is_soft_readonly(osb))
		return -EROFS;

	mutex_lock(&inode->i_mutex);

	/*
	 * This prevents concurrent writes on other nodes
	 */
	ret = ocfs2_rw_lock(inode, 1);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_inode_lock(inode, &di_bh, 1);
	if (ret) {
		mlog_errno(ret);
		goto out_rw_unlock;
	}

	if (inode->i_flags & (S_IMMUTABLE|S_APPEND)) {
		ret = -EPERM;
		goto out_inode_unlock;
	}

	switch (sr->l_whence) {
	case 0: /*SEEK_SET*/
		break;
	case 1: /*SEEK_CUR*/
		sr->l_start += f_pos;
		break;
	case 2: /*SEEK_END*/
		sr->l_start += i_size_read(inode);
		break;
	default:
		ret = -EINVAL;
		goto out_inode_unlock;
	}
	sr->l_whence = 0;

	llen = sr->l_len > 0 ? sr->l_len - 1 : sr->l_len;

	if (sr->l_start < 0
	    || sr->l_start > max_off
	    || (sr->l_start + llen) < 0
	    || (sr->l_start + llen) > max_off) {
		ret = -EINVAL;
		goto out_inode_unlock;
	}
	size = sr->l_start + sr->l_len;

	if (cmd == OCFS2_IOC_RESVSP || cmd == OCFS2_IOC_RESVSP64) {
		if (sr->l_len <= 0) {
			ret = -EINVAL;
			goto out_inode_unlock;
		}
	}

	if (file && should_remove_suid(file->f_path.dentry)) {
		ret = __ocfs2_write_remove_suid(inode, di_bh);
		if (ret) {
			mlog_errno(ret);
			goto out_inode_unlock;
		}
	}

	down_write(&OCFS2_I(inode)->ip_alloc_sem);
	switch (cmd) {
	case OCFS2_IOC_RESVSP:
	case OCFS2_IOC_RESVSP64:
		/*
		 * This takes unsigned offsets, but the signed ones we
		 * pass have been checked against overflow above.
		 */
		ret = ocfs2_allocate_unwritten_extents(inode, sr->l_start,
						       sr->l_len);
		break;
	case OCFS2_IOC_UNRESVSP:
	case OCFS2_IOC_UNRESVSP64:
		ret = ocfs2_remove_inode_range(inode, di_bh, sr->l_start,
					       sr->l_len);
		break;
	default:
		ret = -EINVAL;
	}
	up_write(&OCFS2_I(inode)->ip_alloc_sem);
	if (ret) {
		mlog_errno(ret);
		goto out_inode_unlock;
	}

	/*
	 * We update c/mtime for these changes
	 */
	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		mlog_errno(ret);
		goto out_inode_unlock;
	}

	if (change_size && i_size_read(inode) < size)
		i_size_write(inode, size);

	inode->i_ctime = inode->i_mtime = CURRENT_TIME;
	ret = ocfs2_mark_inode_dirty(handle, inode, di_bh);
	if (ret < 0)
		mlog_errno(ret);

	ocfs2_commit_trans(osb, handle);

out_inode_unlock:
	brelse(di_bh);
	ocfs2_inode_unlock(inode, 1);
out_rw_unlock:
	ocfs2_rw_unlock(inode, 1);

out:
	mutex_unlock(&inode->i_mutex);
	return ret;
}