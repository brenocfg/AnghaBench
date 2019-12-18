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
struct ocfs2_inode_info {int ip_flags; scalar_t__ ip_blkno; } ;
struct inode {int /*<<< orphan*/  i_nlink; } ;

/* Variables and functions */
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INODE_MAYBE_ORPHANED ; 
 int /*<<< orphan*/  generic_delete_inode (struct inode*) ; 
 int /*<<< orphan*/  generic_drop_inode (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_exit_void () ; 

void ocfs2_drop_inode(struct inode *inode)
{
	struct ocfs2_inode_info *oi = OCFS2_I(inode);

	mlog_entry_void();

	mlog(0, "Drop inode %llu, nlink = %u, ip_flags = 0x%x\n",
	     (unsigned long long)oi->ip_blkno, inode->i_nlink, oi->ip_flags);

	if (oi->ip_flags & OCFS2_INODE_MAYBE_ORPHANED)
		generic_delete_inode(inode);
	else
		generic_drop_inode(inode);

	mlog_exit_void();
}