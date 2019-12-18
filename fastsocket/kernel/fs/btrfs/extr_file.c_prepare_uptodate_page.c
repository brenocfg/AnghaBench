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
typedef  int u64 ;
struct page {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int btrfs_readpage (int /*<<< orphan*/ *,struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int prepare_uptodate_page(struct page *page, u64 pos,
				 bool force_uptodate)
{
	int ret = 0;

	if (((pos & (PAGE_CACHE_SIZE - 1)) || force_uptodate) &&
	    !PageUptodate(page)) {
		ret = btrfs_readpage(NULL, page);
		if (ret)
			return ret;
		lock_page(page);
		if (!PageUptodate(page)) {
			unlock_page(page);
			return -EIO;
		}
	}
	return 0;
}