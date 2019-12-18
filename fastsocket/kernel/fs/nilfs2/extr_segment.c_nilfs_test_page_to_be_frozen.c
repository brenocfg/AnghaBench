#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {struct address_space* mapping; } ;
struct address_space {TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int PageChecked (struct page*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ page_mapped (struct page*) ; 

__attribute__((used)) static int nilfs_test_page_to_be_frozen(struct page *page)
{
	struct address_space *mapping = page->mapping;

	if (!mapping || !mapping->host || S_ISDIR(mapping->host->i_mode))
		return 0;

	if (page_mapped(page)) {
		ClearPageChecked(page);
		return 1;
	}
	return PageChecked(page);
}