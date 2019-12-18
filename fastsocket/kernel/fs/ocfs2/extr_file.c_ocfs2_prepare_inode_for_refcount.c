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
typedef  size_t u32 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  size_t loff_t ;
struct TYPE_2__ {size_t s_clustersize_bits; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 size_t ocfs2_clusters_for_bytes (int /*<<< orphan*/ ,size_t) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int ocfs2_refcount_cow (struct inode*,struct buffer_head*,size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_prepare_inode_for_refcount(struct inode *inode,
					    loff_t pos, size_t count,
					    int *meta_level)
{
	int ret;
	struct buffer_head *di_bh = NULL;
	u32 cpos = pos >> OCFS2_SB(inode->i_sb)->s_clustersize_bits;
	u32 clusters =
		ocfs2_clusters_for_bytes(inode->i_sb, pos + count) - cpos;

	ret = ocfs2_inode_lock(inode, &di_bh, 1);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	*meta_level = 1;

	ret = ocfs2_refcount_cow(inode, di_bh, cpos, clusters, UINT_MAX);
	if (ret)
		mlog_errno(ret);
out:
	brelse(di_bh);
	return ret;
}