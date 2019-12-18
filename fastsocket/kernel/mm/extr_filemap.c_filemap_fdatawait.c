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
struct address_space {int /*<<< orphan*/  host; } ;
typedef  int loff_t ;

/* Variables and functions */
 int PAGE_CACHE_SHIFT ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 int wait_on_page_writeback_range (struct address_space*,int /*<<< orphan*/ ,int) ; 

int filemap_fdatawait(struct address_space *mapping)
{
	loff_t i_size = i_size_read(mapping->host);

	if (i_size == 0)
		return 0;

	return wait_on_page_writeback_range(mapping, 0,
				(i_size - 1) >> PAGE_CACHE_SHIFT);
}