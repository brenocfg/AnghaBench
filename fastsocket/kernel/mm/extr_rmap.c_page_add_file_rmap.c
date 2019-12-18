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
struct page {int /*<<< orphan*/  _mapcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_FILE_MAPPED ; 
 int /*<<< orphan*/  __inc_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mem_cgroup_update_file_mapped (struct page*,int) ; 

void page_add_file_rmap(struct page *page)
{
	if (atomic_inc_and_test(&page->_mapcount)) {
		__inc_zone_page_state(page, NR_FILE_MAPPED);
		mem_cgroup_update_file_mapped(page, 1);
	}
}