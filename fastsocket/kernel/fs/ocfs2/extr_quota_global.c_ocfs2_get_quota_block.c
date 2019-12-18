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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_alloc_sem; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_extent_map_get_blocks (struct inode*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct buffer_head* sb_getblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_get_quota_block(struct inode *inode, int block,
				 struct buffer_head **bh)
{
	u64 pblock, pcount;
	int err;

	down_read(&OCFS2_I(inode)->ip_alloc_sem);
	err = ocfs2_extent_map_get_blocks(inode, block, &pblock, &pcount, NULL);
	up_read(&OCFS2_I(inode)->ip_alloc_sem);
	if (err) {
		mlog_errno(err);
		return err;
	}
	*bh = sb_getblk(inode->i_sb, pblock);
	if (!*bh) {
		err = -EIO;
		mlog_errno(err);
	}
	return err;
}