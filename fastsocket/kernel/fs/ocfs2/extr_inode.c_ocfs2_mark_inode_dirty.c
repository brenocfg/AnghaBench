#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_dinode {void* i_mtime_nsec; void* i_mtime; void* i_ctime_nsec; void* i_ctime; void* i_atime_nsec; void* i_atime; void* i_mode; void* i_gid; void* i_uid; void* i_size; void* i_dyn_features; void* i_attr; void* i_clusters; } ;
struct TYPE_8__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_7__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {TYPE_3__ i_mtime; TYPE_2__ i_ctime; TYPE_1__ i_atime; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_nlink; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_dyn_features; int /*<<< orphan*/  ip_attr; int /*<<< orphan*/  ip_clusters; scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 TYPE_4__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog_entry (char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_get_inode_flags (TYPE_4__*) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_set_links_count (struct ocfs2_dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ocfs2_mark_inode_dirty(handle_t *handle,
			   struct inode *inode,
			   struct buffer_head *bh)
{
	int status;
	struct ocfs2_dinode *fe = (struct ocfs2_dinode *) bh->b_data;

	mlog_entry("(inode %llu)\n",
		   (unsigned long long)OCFS2_I(inode)->ip_blkno);

	status = ocfs2_journal_access_di(handle, INODE_CACHE(inode), bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	spin_lock(&OCFS2_I(inode)->ip_lock);
	fe->i_clusters = cpu_to_le32(OCFS2_I(inode)->ip_clusters);
	ocfs2_get_inode_flags(OCFS2_I(inode));
	fe->i_attr = cpu_to_le32(OCFS2_I(inode)->ip_attr);
	fe->i_dyn_features = cpu_to_le16(OCFS2_I(inode)->ip_dyn_features);
	spin_unlock(&OCFS2_I(inode)->ip_lock);

	fe->i_size = cpu_to_le64(i_size_read(inode));
	ocfs2_set_links_count(fe, inode->i_nlink);
	fe->i_uid = cpu_to_le32(inode->i_uid);
	fe->i_gid = cpu_to_le32(inode->i_gid);
	fe->i_mode = cpu_to_le16(inode->i_mode);
	fe->i_atime = cpu_to_le64(inode->i_atime.tv_sec);
	fe->i_atime_nsec = cpu_to_le32(inode->i_atime.tv_nsec);
	fe->i_ctime = cpu_to_le64(inode->i_ctime.tv_sec);
	fe->i_ctime_nsec = cpu_to_le32(inode->i_ctime.tv_nsec);
	fe->i_mtime = cpu_to_le64(inode->i_mtime.tv_sec);
	fe->i_mtime_nsec = cpu_to_le32(inode->i_mtime.tv_nsec);

	status = ocfs2_journal_dirty(handle, bh);
	if (status < 0)
		mlog_errno(status);

	status = 0;
leave:

	mlog_exit(status);
	return status;
}