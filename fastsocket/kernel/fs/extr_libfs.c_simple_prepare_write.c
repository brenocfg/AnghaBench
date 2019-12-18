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
struct file {int dummy; } ;

/* Variables and functions */
 unsigned int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  zero_user_segments (struct page*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 

int simple_prepare_write(struct file *file, struct page *page,
			unsigned from, unsigned to)
{
	if (!PageUptodate(page)) {
		if (to - from != PAGE_CACHE_SIZE)
			zero_user_segments(page,
				0, from,
				to, PAGE_CACHE_SIZE);
	}
	return 0;
}