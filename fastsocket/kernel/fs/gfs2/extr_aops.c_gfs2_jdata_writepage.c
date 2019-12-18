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
struct writeback_control {scalar_t__ sync_mode; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct gfs2_sbd {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ PageChecked (struct page*) ; 
 scalar_t__ RES_DINODE ; 
 scalar_t__ WB_SYNC_ALL ; 
 int __gfs2_jdata_writepage (struct page*,struct writeback_control*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int gfs2_writepage_common (struct page*,struct writeback_control*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int gfs2_jdata_writepage(struct page *page, struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	int ret;
	int done_trans = 0;

	if (PageChecked(page)) {
		if (wbc->sync_mode != WB_SYNC_ALL)
			goto out_ignore;
		ret = gfs2_trans_begin(sdp, RES_DINODE + 1, 0);
		if (ret)
			goto out_ignore;
		done_trans = 1;
	}
	ret = gfs2_writepage_common(page, wbc);
	if (ret > 0)
		ret = __gfs2_jdata_writepage(page, wbc);
	if (done_trans)
		gfs2_trans_end(sdp);
	return ret;

out_ignore:
	redirty_page_for_writepage(wbc, page);
	unlock_page(page);
	return 0;
}