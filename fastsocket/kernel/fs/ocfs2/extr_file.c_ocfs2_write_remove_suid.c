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
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int __ocfs2_write_remove_suid (struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_read_inode_block (struct inode*,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_write_remove_suid(struct inode *inode)
{
	int ret;
	struct buffer_head *bh = NULL;

	ret = ocfs2_read_inode_block(inode, &bh);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

	ret =  __ocfs2_write_remove_suid(inode, bh);
out:
	brelse(bh);
	return ret;
}