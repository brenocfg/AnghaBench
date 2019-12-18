#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_6__ {int h_buffer_credits; } ;
typedef  TYPE_1__ handle_t ;
struct TYPE_7__ {scalar_t__ s_clustersize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_5__* OCFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ OCFS2_XATTR_BUCKET_SIZE ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_blocks_per_xattr_bucket (int /*<<< orphan*/ ) ; 
 int ocfs2_divide_xattr_bucket (struct inode*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ocfs2_extend_trans (TYPE_1__*,int) ; 

__attribute__((used)) static int ocfs2_divide_xattr_cluster(struct inode *inode,
				      handle_t *handle,
				      u64 prev_blk,
				      u64 new_blk,
				      u32 *first_hash)
{
	u16 blk_per_bucket = ocfs2_blocks_per_xattr_bucket(inode->i_sb);
	int ret, credits = 2 * blk_per_bucket + handle->h_buffer_credits;

	BUG_ON(OCFS2_XATTR_BUCKET_SIZE < OCFS2_SB(inode->i_sb)->s_clustersize);

	ret = ocfs2_extend_trans(handle, credits);
	if (ret) {
		mlog_errno(ret);
		return ret;
	}

	/* Move half of the xattr in start_blk to the next bucket. */
	return  ocfs2_divide_xattr_bucket(inode, handle, prev_blk,
					  new_blk, first_hash, 1);
}