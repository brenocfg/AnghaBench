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
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  TRUNCATE_LOG_SYSTEM_INODE ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int) ; 
 int ocfs2_read_inode_block (struct inode*,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_get_truncate_log_info(struct ocfs2_super *osb,
				       int slot_num,
				       struct inode **tl_inode,
				       struct buffer_head **tl_bh)
{
	int status;
	struct inode *inode = NULL;
	struct buffer_head *bh = NULL;

	inode = ocfs2_get_system_file_inode(osb,
					   TRUNCATE_LOG_SYSTEM_INODE,
					   slot_num);
	if (!inode) {
		status = -EINVAL;
		mlog(ML_ERROR, "Could not get load truncate log inode!\n");
		goto bail;
	}

	status = ocfs2_read_inode_block(inode, &bh);
	if (status < 0) {
		iput(inode);
		mlog_errno(status);
		goto bail;
	}

	*tl_inode = inode;
	*tl_bh    = bh;
bail:
	mlog_exit(status);
	return status;
}