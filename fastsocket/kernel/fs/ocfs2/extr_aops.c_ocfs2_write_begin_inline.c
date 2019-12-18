#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct ocfs2_write_ctxt {int w_num_pages; int /*<<< orphan*/ * w_handle; TYPE_1__* w_di_bh; struct page* w_target_page; struct page** w_pages; } ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_dinode {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_5__ {int ip_dyn_features; } ;
struct TYPE_4__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 int /*<<< orphan*/  OCFS2_INODE_UPDATE_CREDITS ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 struct page* find_or_create_page (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ocfs2_read_inline_data (struct inode*,struct page*,TYPE_1__*) ; 
 int /*<<< orphan*/  ocfs2_set_inode_data_inline (struct inode*,struct ocfs2_dinode*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_write_begin_inline(struct address_space *mapping,
				    struct inode *inode,
				    struct ocfs2_write_ctxt *wc)
{
	int ret;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct page *page;
	handle_t *handle;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)wc->w_di_bh->b_data;

	page = find_or_create_page(mapping, 0, GFP_NOFS);
	if (!page) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}
	/*
	 * If we don't set w_num_pages then this page won't get unlocked
	 * and freed on cleanup of the write context.
	 */
	wc->w_pages[0] = wc->w_target_page = page;
	wc->w_num_pages = 1;

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), wc->w_di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		ocfs2_commit_trans(osb, handle);

		mlog_errno(ret);
		goto out;
	}

	if (!(OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL))
		ocfs2_set_inode_data_inline(inode, di);

	if (!PageUptodate(page)) {
		ret = ocfs2_read_inline_data(inode, page, wc->w_di_bh);
		if (ret) {
			ocfs2_commit_trans(osb, handle);

			goto out;
		}
	}

	wc->w_handle = handle;
out:
	return ret;
}