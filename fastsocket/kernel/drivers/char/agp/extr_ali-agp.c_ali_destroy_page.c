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
 int AGP_PAGE_DESTROY_UNMAP ; 
 int /*<<< orphan*/  agp_generic_destroy_page (struct page*,int) ; 
 int /*<<< orphan*/  global_cache_flush () ; 

__attribute__((used)) static void ali_destroy_page(struct page *page, int flags)
{
	if (page) {
		if (flags & AGP_PAGE_DESTROY_UNMAP) {
			global_cache_flush();	/* is this really needed?  --hch */
			agp_generic_destroy_page(page, flags);
		} else
			agp_generic_destroy_page(page, flags);
	}
}