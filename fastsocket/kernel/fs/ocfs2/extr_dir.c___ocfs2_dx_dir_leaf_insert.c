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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_dx_leaf {int /*<<< orphan*/  dl_list; } ;
struct ocfs2_dx_hinfo {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_dx_entry_list_insert (int /*<<< orphan*/ *,struct ocfs2_dx_hinfo*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_dl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 

__attribute__((used)) static int __ocfs2_dx_dir_leaf_insert(struct inode *dir, handle_t *handle,
				      struct ocfs2_dx_hinfo *hinfo,
				      u64 dirent_blk,
				      struct buffer_head *dx_leaf_bh)
{
	int ret;
	struct ocfs2_dx_leaf *dx_leaf;

	ret = ocfs2_journal_access_dl(handle, INODE_CACHE(dir), dx_leaf_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	dx_leaf = (struct ocfs2_dx_leaf *)dx_leaf_bh->b_data;
	ocfs2_dx_entry_list_insert(&dx_leaf->dl_list, hinfo, dirent_blk);
	ocfs2_journal_dirty(handle, dx_leaf_bh);

out:
	return ret;
}