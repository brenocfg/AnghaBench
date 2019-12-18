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
struct hstate {int dummy; } ;

/* Variables and functions */
 int MAX_ORDER_NR_PAGES ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  copy_gigantic_page (struct page*,struct page*) ; 
 int /*<<< orphan*/  copy_highpage (struct page*,struct page*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 struct hstate* page_hstate (struct page*) ; 
 int pages_per_huge_page (struct hstate*) ; 
 scalar_t__ unlikely (int) ; 

void copy_huge_page(struct page *dst, struct page *src)
{
	int i;
	struct hstate *h = page_hstate(src);

	if (unlikely(pages_per_huge_page(h) > MAX_ORDER_NR_PAGES)) {
		copy_gigantic_page(dst, src);
		return;
	}

	might_sleep();
	for (i = 0; i < pages_per_huge_page(h); i++) {
		cond_resched();
		copy_highpage(dst + i, src + i);
	}
}