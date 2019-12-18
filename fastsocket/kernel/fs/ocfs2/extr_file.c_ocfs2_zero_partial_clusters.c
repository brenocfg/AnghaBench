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
typedef  unsigned int u64 ;
struct ocfs2_super {unsigned int s_clustersize; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_INODE_UPDATE_CREDITS ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int ocfs2_zero_range_for_truncate (struct inode*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static int ocfs2_zero_partial_clusters(struct inode *inode,
				       u64 start, u64 len)
{
	int ret = 0;
	u64 tmpend, end = start + len;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	unsigned int csize = osb->s_clustersize;
	handle_t *handle;

	/*
	 * The "start" and "end" values are NOT necessarily part of
	 * the range whose allocation is being deleted. Rather, this
	 * is what the user passed in with the request. We must zero
	 * partial clusters here. There's no need to worry about
	 * physical allocation - the zeroing code knows to skip holes.
	 */
	mlog(0, "byte start: %llu, end: %llu\n",
	     (unsigned long long)start, (unsigned long long)end);

	/*
	 * If both edges are on a cluster boundary then there's no
	 * zeroing required as the region is part of the allocation to
	 * be truncated.
	 */
	if ((start & (csize - 1)) == 0 && (end & (csize - 1)) == 0)
		goto out;

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		mlog_errno(ret);
		goto out;
	}

	/*
	 * We want to get the byte offset of the end of the 1st cluster.
	 */
	tmpend = (u64)osb->s_clustersize + (start & ~(osb->s_clustersize - 1));
	if (tmpend > end)
		tmpend = end;

	mlog(0, "1st range: start: %llu, tmpend: %llu\n",
	     (unsigned long long)start, (unsigned long long)tmpend);

	ret = ocfs2_zero_range_for_truncate(inode, handle, start, tmpend);
	if (ret)
		mlog_errno(ret);

	if (tmpend < end) {
		/*
		 * This may make start and end equal, but the zeroing
		 * code will skip any work in that case so there's no
		 * need to catch it up here.
		 */
		start = end & ~(osb->s_clustersize - 1);

		mlog(0, "2nd range: start: %llu, end: %llu\n",
		     (unsigned long long)start, (unsigned long long)end);

		ret = ocfs2_zero_range_for_truncate(inode, handle, start, end);
		if (ret)
			mlog_errno(ret);
	}

	ocfs2_commit_trans(osb, handle);
out:
	return ret;
}