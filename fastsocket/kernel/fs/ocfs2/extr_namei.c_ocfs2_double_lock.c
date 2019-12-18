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
struct ocfs2_inode_info {scalar_t__ ip_blkno; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OI_LS_RENAME1 ; 
 int /*<<< orphan*/  OI_LS_RENAME2 ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlog_entry (char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_inode_lock_nested (struct inode*,struct buffer_head**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 

__attribute__((used)) static int ocfs2_double_lock(struct ocfs2_super *osb,
			     struct buffer_head **bh1,
			     struct inode *inode1,
			     struct buffer_head **bh2,
			     struct inode *inode2)
{
	int status;
	struct ocfs2_inode_info *oi1 = OCFS2_I(inode1);
	struct ocfs2_inode_info *oi2 = OCFS2_I(inode2);
	struct buffer_head **tmpbh;
	struct inode *tmpinode;

	mlog_entry("(inode1 = %llu, inode2 = %llu)\n",
		   (unsigned long long)oi1->ip_blkno,
		   (unsigned long long)oi2->ip_blkno);

	if (*bh1)
		*bh1 = NULL;
	if (*bh2)
		*bh2 = NULL;

	/* we always want to lock the one with the lower lockid first. */
	if (oi1->ip_blkno != oi2->ip_blkno) {
		if (oi1->ip_blkno < oi2->ip_blkno) {
			/* switch id1 and id2 around */
			mlog(0, "switching them around...\n");
			tmpbh = bh2;
			bh2 = bh1;
			bh1 = tmpbh;

			tmpinode = inode2;
			inode2 = inode1;
			inode1 = tmpinode;
		}
		/* lock id2 */
		status = ocfs2_inode_lock_nested(inode2, bh2, 1,
						 OI_LS_RENAME1);
		if (status < 0) {
			if (status != -ENOENT)
				mlog_errno(status);
			goto bail;
		}
	}

	/* lock id1 */
	status = ocfs2_inode_lock_nested(inode1, bh1, 1, OI_LS_RENAME2);
	if (status < 0) {
		/*
		 * An error return must mean that no cluster locks
		 * were held on function exit.
		 */
		if (oi1->ip_blkno != oi2->ip_blkno)
			ocfs2_inode_unlock(inode2, 1);

		if (status != -ENOENT)
			mlog_errno(status);
	}

bail:
	mlog_exit(status);
	return status;
}