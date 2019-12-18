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
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 int /*<<< orphan*/  NR_WRITEBACK ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 scalar_t__ TestClearPageWriteback (struct page*) ; 
 int /*<<< orphan*/  __set_page_dirty_nobuffers (struct page*) ; 
 scalar_t__ buffer_nilfs_allocated (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_zone_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 int /*<<< orphan*/  nilfs_page_buffers_clean (struct page*) ; 
 int /*<<< orphan*/  page_buffers (struct page*) ; 

__attribute__((used)) static void __nilfs_end_page_io(struct page *page, int err)
{
	if (!err) {
		if (!nilfs_page_buffers_clean(page))
			__set_page_dirty_nobuffers(page);
		ClearPageError(page);
	} else {
		__set_page_dirty_nobuffers(page);
		SetPageError(page);
	}

	if (buffer_nilfs_allocated(page_buffers(page))) {
		if (TestClearPageWriteback(page))
			dec_zone_page_state(page, NR_WRITEBACK);
	} else
		end_page_writeback(page);
}