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
struct page {scalar_t__ index; } ;
struct address_space {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 int PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 scalar_t__ page_mapped (struct page*) ; 
 int truncate_complete_page (struct address_space*,struct page*) ; 
 int /*<<< orphan*/  unmap_mapping_range (struct address_space*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int truncate_inode_page(struct address_space *mapping, struct page *page)
{
	if (page_mapped(page)) {
		unmap_mapping_range(mapping,
				   (loff_t)page->index << PAGE_CACHE_SHIFT,
				   PAGE_CACHE_SIZE, 0);
	}
	return truncate_complete_page(mapping, page);
}