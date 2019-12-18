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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_super {int /*<<< orphan*/  slot_num; } ;
struct ocfs2_dir_lookup_result {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  OCFS2_ORPHAN_NAMELEN ; 
 int /*<<< orphan*/  ORPHAN_DIR_SYSTEM_INODE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ocfs2_blkno_stringify (int /*<<< orphan*/ ,char*) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_prepare_dir_for_insert (struct ocfs2_super*,struct inode*,struct buffer_head*,char*,int /*<<< orphan*/ ,struct ocfs2_dir_lookup_result*) ; 

__attribute__((used)) static int ocfs2_prepare_orphan_dir(struct ocfs2_super *osb,
				    struct inode **ret_orphan_dir,
				    u64 blkno,
				    char *name,
				    struct ocfs2_dir_lookup_result *lookup)
{
	struct inode *orphan_dir_inode;
	struct buffer_head *orphan_dir_bh = NULL;
	int status = 0;

	status = ocfs2_blkno_stringify(blkno, name);
	if (status < 0) {
		mlog_errno(status);
		return status;
	}

	orphan_dir_inode = ocfs2_get_system_file_inode(osb,
						       ORPHAN_DIR_SYSTEM_INODE,
						       osb->slot_num);
	if (!orphan_dir_inode) {
		status = -ENOENT;
		mlog_errno(status);
		return status;
	}

	mutex_lock(&orphan_dir_inode->i_mutex);

	status = ocfs2_inode_lock(orphan_dir_inode, &orphan_dir_bh, 1);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	status = ocfs2_prepare_dir_for_insert(osb, orphan_dir_inode,
					      orphan_dir_bh, name,
					      OCFS2_ORPHAN_NAMELEN, lookup);
	if (status < 0) {
		ocfs2_inode_unlock(orphan_dir_inode, 1);

		mlog_errno(status);
		goto leave;
	}

	*ret_orphan_dir = orphan_dir_inode;

leave:
	if (status) {
		mutex_unlock(&orphan_dir_inode->i_mutex);
		iput(orphan_dir_inode);
	}

	brelse(orphan_dir_bh);

	mlog_exit(status);
	return status;
}