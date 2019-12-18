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
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  copy_highpage (struct page*,struct page*) ; 
 struct page* mem_map_next (struct page*,struct page*,int) ; 
 struct hstate* page_hstate (struct page*) ; 
 int pages_per_huge_page (struct hstate*) ; 

__attribute__((used)) static void copy_gigantic_page(struct page *dst, struct page *src)
{
	int i;
	struct hstate *h = page_hstate(src);
	struct page *dst_base = dst;
	struct page *src_base = src;

	for (i = 0; i < pages_per_huge_page(h); ) {
		cond_resched();
		copy_highpage(dst, src);

		i++;
		dst = mem_map_next(dst, dst_base, i);
		src = mem_map_next(src, src_base, i);
	}
}