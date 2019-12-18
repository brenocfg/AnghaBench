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
struct ocfs2_empty_dir_priv {int /*<<< orphan*/  seen_other; int /*<<< orphan*/  seen_dot_dot; int /*<<< orphan*/  seen_dot; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  priv ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  memset (struct ocfs2_empty_dir_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_dir_foreach (struct inode*,int /*<<< orphan*/ *,struct ocfs2_empty_dir_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_dir_indexed (struct inode*) ; 
 int ocfs2_empty_dir_dx (struct inode*,struct ocfs2_empty_dir_priv*) ; 
 int /*<<< orphan*/  ocfs2_empty_dir_filldir ; 

int ocfs2_empty_dir(struct inode *inode)
{
	int ret;
	loff_t start = 0;
	struct ocfs2_empty_dir_priv priv;

	memset(&priv, 0, sizeof(priv));

	if (ocfs2_dir_indexed(inode)) {
		ret = ocfs2_empty_dir_dx(inode, &priv);
		if (ret)
			mlog_errno(ret);
		/*
		 * We still run ocfs2_dir_foreach to get the checks
		 * for "." and "..".
		 */
	}

	ret = ocfs2_dir_foreach(inode, &start, &priv, ocfs2_empty_dir_filldir);
	if (ret)
		mlog_errno(ret);

	if (!priv.seen_dot || !priv.seen_dot_dot) {
		mlog(ML_ERROR, "bad directory (dir #%llu) - no `.' or `..'\n",
		     (unsigned long long)OCFS2_I(inode)->ip_blkno);
		/*
		 * XXX: Is it really safe to allow an unlink to continue?
		 */
		return 1;
	}

	return !priv.seen_other;
}