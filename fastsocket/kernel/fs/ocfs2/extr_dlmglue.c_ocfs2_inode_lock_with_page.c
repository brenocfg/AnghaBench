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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int AOP_TRUNCATED_PAGE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  OCFS2_LOCK_NONBLOCK ; 
 scalar_t__ ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int ocfs2_inode_lock_full (struct inode*,struct buffer_head**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int ocfs2_inode_lock_with_page(struct inode *inode,
			      struct buffer_head **ret_bh,
			      int ex,
			      struct page *page)
{
	int ret;

	ret = ocfs2_inode_lock_full(inode, ret_bh, ex, OCFS2_LOCK_NONBLOCK);
	if (ret == -EAGAIN) {
		unlock_page(page);
		if (ocfs2_inode_lock(inode, ret_bh, ex) == 0)
			ocfs2_inode_unlock(inode, ex);
		ret = AOP_TRUNCATED_PAGE;
	}

	return ret;
}