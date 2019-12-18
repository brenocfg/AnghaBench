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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 int EFAULT ; 
 int /*<<< orphan*/  EXOFS_DBGMSG (char*) ; 
 scalar_t__ PageError (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  clear_highpage (struct page*) ; 

__attribute__((used)) static int update_read_page(struct page *page, int ret)
{
	if (ret == 0) {
		/* Everything is OK */
		SetPageUptodate(page);
		if (PageError(page))
			ClearPageError(page);
	} else if (ret == -EFAULT) {
		/* In this case we were trying to read something that wasn't on
		 * disk yet - return a page full of zeroes.  This should be OK,
		 * because the object should be empty (if there was a write
		 * before this read, the read would be waiting with the page
		 * locked */
		clear_highpage(page);

		SetPageUptodate(page);
		if (PageError(page))
			ClearPageError(page);
		ret = 0; /* recovered error */
		EXOFS_DBGMSG("recovered read error\n");
	} else /* Error */
		SetPageError(page);

	return ret;
}