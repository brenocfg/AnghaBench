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
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {scalar_t__ s_clustersize_bits; } ;

/* Variables and functions */
 unsigned int OCFS2_EXT_UNWRITTEN ; 
 TYPE_1__* OCFS2_SB (struct super_block*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_clusters_for_bytes (struct super_block*,scalar_t__) ; 
 int ocfs2_get_clusters (struct inode*,scalar_t__,scalar_t__*,scalar_t__*,unsigned int*) ; 

__attribute__((used)) static int ocfs2_check_range_for_holes(struct inode *inode, loff_t pos,
				       size_t count)
{
	int ret = 0;
	unsigned int extent_flags;
	u32 cpos, clusters, extent_len, phys_cpos;
	struct super_block *sb = inode->i_sb;

	cpos = pos >> OCFS2_SB(sb)->s_clustersize_bits;
	clusters = ocfs2_clusters_for_bytes(sb, pos + count) - cpos;

	while (clusters) {
		ret = ocfs2_get_clusters(inode, cpos, &phys_cpos, &extent_len,
					 &extent_flags);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}

		if (phys_cpos == 0 || (extent_flags & OCFS2_EXT_UNWRITTEN)) {
			ret = 1;
			break;
		}

		if (extent_len > clusters)
			extent_len = clusters;

		clusters -= extent_len;
		cpos += extent_len;
	}
out:
	return ret;
}