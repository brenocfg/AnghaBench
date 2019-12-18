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
struct address_space {scalar_t__ nrpages; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EIO ; 
 int PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 int __filemap_fdatawrite_range (struct address_space*,int,int,int /*<<< orphan*/ ) ; 
 int wait_on_page_writeback_range (struct address_space*,int,int) ; 

int filemap_write_and_wait_range(struct address_space *mapping,
				 loff_t lstart, loff_t lend)
{
	int err = 0;

	if (mapping->nrpages) {
		err = __filemap_fdatawrite_range(mapping, lstart, lend,
						 WB_SYNC_ALL);
		/* See comment of filemap_write_and_wait() */
		if (err != -EIO) {
			int err2 = wait_on_page_writeback_range(mapping,
						lstart >> PAGE_CACHE_SHIFT,
						lend >> PAGE_CACHE_SHIFT);
			if (!err)
				err = err2;
		}
	}
	return err;
}