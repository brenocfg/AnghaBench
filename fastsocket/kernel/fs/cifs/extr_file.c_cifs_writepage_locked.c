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
struct writeback_control {scalar_t__ sync_mode; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int GetXid () ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 scalar_t__ WB_SYNC_ALL ; 
 int /*<<< orphan*/  cFYI (int,char*) ; 
 int cifs_partialpagewrite (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 int /*<<< orphan*/  page_cache_get (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 

__attribute__((used)) static int
cifs_writepage_locked(struct page *page, struct writeback_control *wbc)
{
	int rc;
	int xid;

	xid = GetXid();
/* BB add check for wbc flags */
	page_cache_get(page);
	if (!PageUptodate(page))
		cFYI(1, "ppw - page not up to date");

	/*
	 * Set the "writeback" flag, and clear "dirty" in the radix tree.
	 *
	 * A writepage() implementation always needs to do either this,
	 * or re-dirty the page with "redirty_page_for_writepage()" in
	 * the case of a failure.
	 *
	 * Just unlocking the page will cause the radix tree tag-bits
	 * to fail to update with the state of the page correctly.
	 */
	set_page_writeback(page);
retry_write:
	rc = cifs_partialpagewrite(page, 0, PAGE_CACHE_SIZE);
	if (rc == -EAGAIN && wbc->sync_mode == WB_SYNC_ALL)
		goto retry_write;
	else if (rc == -EAGAIN)
		redirty_page_for_writepage(wbc, page);
	else if (rc != 0)
		SetPageError(page);
	else
		SetPageUptodate(page);
	end_page_writeback(page);
	page_cache_release(page);
	FreeXid(xid);
	return rc;
}