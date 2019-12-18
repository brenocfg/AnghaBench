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
struct buffer_head {struct buffer_head* b_this_page; } ;

/* Variables and functions */
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 

int nilfs_page_buffers_clean(struct page *page)
{
	struct buffer_head *bh, *head;

	bh = head = page_buffers(page);
	do {
		if (buffer_dirty(bh))
			return 0;
		bh = bh->b_this_page;
	} while (bh != head);
	return 1;
}