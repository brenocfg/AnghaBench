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
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 

__attribute__((used)) static inline struct buffer_head *
nilfs_page_get_nth_block(struct page *page, unsigned int count)
{
	struct buffer_head *bh = page_buffers(page);

	while (count-- > 0)
		bh = bh->b_this_page;
	get_bh(bh);
	return bh;
}