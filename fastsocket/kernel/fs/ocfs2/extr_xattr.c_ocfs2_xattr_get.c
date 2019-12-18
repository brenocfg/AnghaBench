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
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 int ocfs2_xattr_get_nolock (struct inode*,struct buffer_head*,int,char const*,void*,size_t) ; 

__attribute__((used)) static int ocfs2_xattr_get(struct inode *inode,
			   int name_index,
			   const char *name,
			   void *buffer,
			   size_t buffer_size)
{
	int ret;
	struct buffer_head *di_bh = NULL;

	ret = ocfs2_inode_lock(inode, &di_bh, 0);
	if (ret < 0) {
		mlog_errno(ret);
		return ret;
	}
	ret = ocfs2_xattr_get_nolock(inode, di_bh, name_index,
				     name, buffer, buffer_size);

	ocfs2_inode_unlock(inode, 0);

	brelse(di_bh);

	return ret;
}